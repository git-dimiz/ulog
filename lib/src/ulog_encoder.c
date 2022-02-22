#include <string.h>
#include <stdint.h>
#include "pb_encode.h"
#include "ulog/ulog_message.pb.h"
#include "ulog_encoder.h"

typedef struct
{
    void* begin;
    void* end;
} itr_t;

static bool ostream_write_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count)
{
    itr_t* itr = (itr_t*)stream->state;
    pb_byte_t* dest = (pb_byte_t*)itr->begin;
    pb_byte_t escape_sequence[] = {0x7D, 0x5E};

    for (size_t i = 0; i < count; i++)
    {
        for (size_t ii = 0; 0x7E == buf[i] && dest != itr->end && ii < sizeof(escape_sequence); ii++)
        {
            *dest = escape_sequence[ii];
            dest++;
        }
        
        if (0x7E != buf[i])
        {
            *dest = buf[i];
            dest++;
        }

        if (dest == itr->end)
        {
            return false;
        }
    }

    itr->begin = dest;
    return true;
}

static bool encode_va_arg(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    ulog_arg_t const* uarg = (ulog_arg_t const*)*arg;
    bool success = false;

    if (true == pb_encode_tag_for_field(stream, field))
    {
        switch (uarg->id)
        {
            case ULOG_ARG_TYPE_ID_U8:
                success = pb_encode_string(stream, (pb_byte_t const*)&uarg->value.u8, sizeof(uint8_t));
                break;
            case ULOG_ARG_TYPE_ID_U16:
                success = pb_encode_string(stream, (pb_byte_t const*)&uarg->value.u16, sizeof(uint16_t));
                break;
            case ULOG_ARG_TYPE_ID_U32:
                success = pb_encode_string(stream, (pb_byte_t const*)&uarg->value.u32, sizeof(uint32_t));
                break;
            case ULOG_ARG_TYPE_ID_U64:
                success = pb_encode_string(stream, (pb_byte_t const*)&uarg->value.u64, sizeof(uint64_t));
                break;
            case ULOG_ARG_TYPE_ID_PTR:
                /* TODO needs test */
                success = pb_encode_string(stream, (pb_byte_t const*)&uarg->value.ptr_v, sizeof(void*));
                break;
            case ULOG_ARG_TYPE_ID_PTR_STR:
                success = pb_encode_string(stream, (pb_byte_t const*)uarg->value.str, strlen(uarg->value.str));
                break;
            case ULOG_ARG_TYPE_ID_NONE:
            default:
                success = false;
                break;
        }
    }

    return success;
}

static bool encode_va_list(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
    ulog_message_payload_t const* payload = (ulog_message_payload_t const*)*arg; 
    bool success = true;

    for (size_t i = 0; i < payload->va_list.size && true == success; i++)
    {
        ulog_pb_va_arg uva_arg = {
            .id = payload->va_list.data[i].id,
            .value = {
                .funcs = {
                    .encode = encode_va_arg,
                },
                .arg = (void*)&payload->va_list.data[i],
            },
        };

        if (false == pb_encode_tag_for_field(stream, field)
            || false == pb_encode_submessage(stream, ulog_pb_va_arg_fields, &uva_arg))
        {
            success = false;
        }
    }
 
    return success;
}


int ulog_encoder_message_start(ulog_encoder_t* encoder, uint8_t* data, size_t size)
{
    int success = -1;

    if (NULL != encoder
        && NULL != data)
    {
        encoder->max_size = size;
        encoder->size = 0;
        encoder->raw_data = data;
        success = 0;
        encoder->raw_data[encoder->size++] = 0x7E;
    }

    return success;
}

int ulog_encoder_message_encode(ulog_encoder_t* encoder, ulog_message_payload_t const* payload)
{
    int success = -1;

    if (NULL != encoder 
        && NULL != payload)
    {
        ulog_pb_message msg = {
            .tag = payload->tag,
            .va_list = {
                .funcs = {
                    .encode = encode_va_list,
                },
                .arg = (void*)payload,
            },
        };

        itr_t itr = {
            .begin = (void*)(encoder->raw_data + encoder->size),
            .end = (void*)(encoder->raw_data + encoder->max_size),
        };

        pb_ostream_t stream = {
            .callback = &ostream_write_callback,
            .state = &itr,
            .max_size = encoder->max_size - encoder->size,
            .bytes_written = 0,
            .errmsg = NULL,
        };

        if (true == pb_encode_delimited(&stream, ulog_pb_message_fields, &msg))
        {
            encoder->size += (uint8_t*)itr.begin - encoder->raw_data;
            success = 0;
        }
    }

    return success;
}

int ulog_encoder_message_end(ulog_encoder_t* encoder, uint8_t** data, size_t* size)
{
    int success = -1;

    if (NULL != encoder
        && NULL != data
        && NULL != size)
    {
        *data = encoder->raw_data;
        *size = encoder->size;
        success = 0;
    }
    
    return success;
}
