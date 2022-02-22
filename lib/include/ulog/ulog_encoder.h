#ifndef _ULOG_ENCODER_H_
#define _ULOG_ENCODER_H_

#include <stdint.h>
#include <stddef.h>
#include "ulog/ulog_arg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t* raw_data;
    size_t max_size;
    size_t size;
} ulog_encoder_t;

typedef struct 
{
    uint32_t tag;
    struct 
    {
        ulog_arg_t const* data;
        size_t size;
    } va_list;
} ulog_message_payload_t;


int ulog_encoder_message_start(ulog_encoder_t* encoder, uint8_t* data, size_t size);
int ulog_encoder_message_encode(ulog_encoder_t* encoder, ulog_message_payload_t const* payload);
int ulog_encoder_message_end(ulog_encoder_t* encoder, uint8_t** data, size_t* size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif