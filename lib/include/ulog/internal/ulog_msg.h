#ifndef _ULOG_MSG_H_
#define _ULOG_MSG_H_

#include <stdint.h>
#include <stddef.h>
#include "ulog/internal/ulog_arg.h"

#define ULOG_MSG_CH_ENCODE(_type, _lvl) (((_type) << 4) | (_lvl)) 

typedef enum {
    ULOG_MSG_TYPE_NONE,
    ULOG_MSG_TYPE_PRINT,
    ULOG_MSG_TYPE_HEXDUMP,
} ulog_msg_type_t;

typedef enum {
    ULOG_MSG_LVL_NONE,
    ULOG_MSG_LVL_DBG,
    ULOG_MSG_LVL_INF,
    ULOG_MSG_LVL_WRN,
    ULOG_MSG_LVL_ERR,
} ulog_msg_lvl_t;

typedef enum {
    ULOG_MSG_CH_PRINT_DBG = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_PRINT, ULOG_MSG_LVL_DBG),
    ULOG_MSG_CH_PRINT_INF = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_PRINT, ULOG_MSG_LVL_INF),
    ULOG_MSG_CH_PRINT_WRN = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_PRINT, ULOG_MSG_LVL_WRN),
    ULOG_MSG_CH_PRINT_ERR = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_PRINT, ULOG_MSG_LVL_ERR),
    ULOG_MSG_CH_HEXDUMP_DBG = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_HEXDUMP, ULOG_MSG_LVL_DBG),
    ULOG_MSG_CH_HEXDUMP_INF = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_HEXDUMP, ULOG_MSG_LVL_INF),
    ULOG_MSG_CH_HEXDUMP_WRN = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_HEXDUMP, ULOG_MSG_LVL_WRN),
    ULOG_MSG_CH_HEXDUMP_ERR = ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_HEXDUMP, ULOG_MSG_LVL_ERR),
    ULOG_MSG_CH_NONE = -1,
} ulog_msg_ch_t;

typedef struct 
{
    uint32_t tag;
    ulog_msg_ch_t ch;
    struct 
    {
        ulog_arg_t const* data;
        size_t size;
    } va_list;
} ulog_msg_payload_t;

#endif
