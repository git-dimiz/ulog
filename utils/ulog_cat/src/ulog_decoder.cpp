#include "ulog_decoder.hpp"
#include "ulog_message.hpp"
#include "ulog/internal/ulog_message.pb.h"
#include "pb_decode.h"
#include <stdio.h>
#include <algorithm>

static bool deque_read(pb_istream_t *stream, pb_byte_t *buf, size_t count)
{
    std::deque<std::uint8_t>::iterator* source = (std::deque<std::uint8_t>::iterator*) stream->state;
    pb_byte_t escape_sequence[] = {0x7D, 0x5E};
    
    for (size_t i = 0; i < count; i++)
    {
        if (**source == 0x7E)
        {
            // this should not happen
            // all start of message should
            // have been byte stuffed
            return false;
        }
        else if (**source == escape_sequence[0] 
                    && *(*source + 1) == escape_sequence[1])
        {
            buf[i] = 0x7E;
            *source += sizeof(escape_sequence);
        }
        else
        {
            buf[i] = **source;
            (*source)++;
        }
    }

    return true;
}

static bool decode_va_arg(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::vector<uint8_t>* value = (std::vector<uint8_t>*)*arg;
    value->resize(stream->bytes_left);
    return pb_read(stream, value->data(), stream->bytes_left);
}

static bool decode_va_list(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
    std::vector<ulog_arg>* va_list = (std::vector<ulog_arg>*)*arg; 
    std::vector<uint8_t> value;

    ulog_pb_va_arg uva_arg = {
        .id = 0,
        .value = {
            .funcs = {
                .decode = decode_va_arg,
            },
            .arg = &value,
        },
    };

    if (true == pb_decode(stream, ulog_pb_va_arg_fields, &uva_arg))
    {
        va_list->push_back(std::move(ulog_arg((ulog_arg_type_id_t)uva_arg.id,
                                                                  value.data(),
                                                                  value.size())));
    }

    return true;
}

ulog_message& ulog_decoder::message(void)
{
    return this->_message;
}

int ulog_decoder::decode(std::deque<std::uint8_t>& data)
{
    int success = 0;
    std::deque<std::uint8_t>::iterator start = std::find(std::begin(data), std::end(data), 0x7E);
    if (std::end(data) != start)
    {
        std::vector<ulog_arg> va_list;
        start++;
        pb_istream_t istream = {
            .callback = &deque_read,
            .state = (void*)&start,
            .bytes_left = data.size(),
            .errmsg = NULL,
        };

        ulog_pb_message msg = {
            .tag = 0,
            .va_list = {
                .funcs = {
                    .decode = decode_va_list,
                },
                .arg = &va_list,
            },
        };

        if (true == pb_decode_delimited(&istream, ulog_pb_message_fields, &msg))
        {
            _message = std::move(ulog_message(msg.tag, va_list));
            success = start - std::begin(data); 
        }
        else
        {
            std::deque<std::uint8_t>::iterator start_another_message = std::find(std::find(std::begin(data), std::end(data), 0x7E) + 1, std::end(data), 0x7E);
            if (std::end(data) != start_another_message)
            {
                success = (start_another_message - std::begin(data)) * -1;
            }
        }
    }

    return success;
}

int ulog_decoder::decode(std::uint8_t* data, std::size_t size)
{
    pb_istream_t istream = pb_istream_from_buffer(data, size);

    std::vector<ulog_arg> va_list;

    ulog_pb_message msg = {
        .tag = 0,
        .va_list = {
            .funcs = {
                .decode = decode_va_list,
            },
            .arg = &va_list,
        },
    };

    if (true == pb_decode(&istream, ulog_pb_message_fields, &msg))
    {
        _message = std::move(ulog_message(msg.tag, va_list));
    }

    return 0;
}