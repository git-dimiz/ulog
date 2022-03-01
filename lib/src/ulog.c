#include <stdbool.h>

#include "ulog/ulog.h"
#include "ulog_msg.pb.h"
#include "ulog/internal/ulog_encoder.h"

typedef struct
{
    ulog_backend_t const* backend;
    struct {
        uint8_t* data; 
        size_t max_size;
    } encode_buffer;
} ulog_t;

static ulog_t ulog;

int ulog_init(ulog_config_t const* config, ulog_backend_t const* backend, void* backend_arg)
{
    int success = -1;

    if (NULL != backend
        && NULL != backend->init
        && NULL != config)
    {
        ulog.encode_buffer.data = config->buffer;
        ulog.encode_buffer.max_size = config->size;
        ulog.backend = backend;
        success = ulog.backend->init(backend_arg);
    }

    return success;
}

void ulog_deinit(void)
{
    if (NULL != ulog.backend
        && NULL != ulog.backend->deinit)
    {
        ulog.backend->deinit();
        ulog.backend = NULL;
    }
}


int ulog_print(const ulog_msg_ch_t ch, const uint32_t tag, ulog_arg_t const* arg_list, size_t size)
{
    uint8_t* p = NULL;
    size_t s = 0;
 
    ulog_encoder_t encoder;
    int send = 0, to_send = 0;

    if (NULL != ulog.backend
        && NULL != ulog.backend->tx
        && 0 == ulog_encoder_message_start(&encoder, 
                                           ulog.encode_buffer.data,
                                           ulog.encode_buffer.max_size) 
        && 0 == ulog_encoder_message_encode(&encoder, 
                                            &(ulog_msg_payload_t){
                                                .tag = tag,
                                                .ch = ch,
                                                .va_list = {
                                                    .data = arg_list,
                                                    .size = size,
                                                },
                                            })
        && 0 == ulog_encoder_message_end(&encoder, &p, &s))
    {
        to_send = s;
        do
        {
            send = ulog.backend->tx(p + send, to_send - send);
        } while ((to_send - send) > 0);
    }
    else
    {
        send = -1;
    }

    return send;
}