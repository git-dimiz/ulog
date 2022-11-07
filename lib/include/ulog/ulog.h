#ifndef _ULOG_H_
#define _ULOG_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "ulog/internal/cpp_magic.h"
#include "ulog/internal/ulog_arg.h"
#include "ulog/internal/ulog_hash.h"
#include "ulog/internal/ulog_msg.h"
#include "ulog/internal/toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ULOG_SECTION_RODATA ".ulog_rodata"
#define __ulog_rodata __used_section(ULOG_SECTION_RODATA)

typedef int (*ulog_backend_handle_init_t)(void* arg);
typedef int (*ulog_backend_handle_tx_t)(uint8_t const* data, size_t size);
typedef void (*ulog_backend_handle_deinit_t)(void);

typedef struct
{
    ulog_backend_handle_init_t init;
    ulog_backend_handle_tx_t tx;
    ulog_backend_handle_deinit_t deinit;
} ulog_backend_t;

typedef struct
{
  uint8_t* buffer;
  size_t size;
} ulog_config_t;

/**
 * @brief printf like function to force the compiler to check the format string
 */
static inline __printf_like(1, 2) void ulog_dummy_printf(char const* fmt, ...) { (void)fmt; }

int ulog_init(ulog_config_t const* config, ulog_backend_t const* backend, void* backend_arg);
int ulog_print(const ulog_msg_ch_t ch, const uint32_t tag, ulog_arg_t const* arg_list, size_t size);

static inline int ulog_hexdump(const ulog_msg_ch_t ch, const uint32_t tag, ulog_arg_t const* arg)
{
    return ulog_print(ch, tag, arg, 1);
}

void ulog_deinit(void);

#define STATIC_ASSERT_ENTRY(x) static_assert(ULOG_ARG_TYPE_ID_NONE != ulog_arg_type_id(x), "invalid arg")
#define ARG_LIST_ENTRY(x) (ulog_arg_t){ulog_arg_type_id(x), { .ptr_v = (void*)x }, -1}
#define MAP_ARGS(op,sep,...) \
  IF(HAS_ARGS(__VA_ARGS__))(EVAL(MAP_ARGS_INNER(op,sep,__VA_ARGS__)))
#define MAP_ARGS_INNER(op,sep,cur_val_1, ...) \
  op(cur_val_1) \
  IF(HAS_ARGS(__VA_ARGS__))( \
    sep() DEFER2(_MAP_ARGS_INNER)()(op, sep, __VA_ARGS__) \
  )
#define _MAP_ARGS_INNER() MAP_ARGS_INNER

#ifndef ULOG_ARGS_ASSERT
    #define ULOG_ARGS_ASSERT(...) MAP_ARGS(STATIC_ASSERT_ENTRY, SEMICOLON, __VA_ARGS__)
#endif

#define ULOG_ARGS_CREATE(...) {MAP_ARGS(ARG_LIST_ENTRY, COMMA, __VA_ARGS__)}

#define ULOG_PRINT(_ch, _fmt, ...) do { \
    ULOG_HASH_STR_ASSERT(_fmt); \
    static const char _ulog_fmt[] __ulog_rodata = _fmt; \
    static const uint32_t _ulog_tag = ULOG_HASH(_fmt); \
    const ulog_msg_ch_t _ulog_ch = _ch; \
    IF(HAS_ARGS(__VA_ARGS__))( \
        ulog_dummy_printf(_fmt, __VA_ARGS__); \
        ULOG_ARGS_ASSERT(__VA_ARGS__); \
        const ulog_arg_t _ulog_arg_list[] = ULOG_ARGS_CREATE(__VA_ARGS__); \
        ulog_print(_ulog_ch, _ulog_tag, _ulog_arg_list, sizeof(_ulog_arg_list) / sizeof(_ulog_arg_list[0])); \
    ) \
    IF(NOT(HAS_ARGS(__VA_ARGS__)))((void)_ulog_fmt; ulog_print(_ulog_ch, _ulog_tag, NULL, 0);) \
} while (0)

#define ULOG_HEXDUMP(_ch, _buffer, _size, _fmt, ...) do { \
    ULOG_PRINT(ULOG_MSG_CH_ENCODE(ULOG_MSG_TYPE_PRINT, ULOG_MSG_CH_LVL_GET(_ch)), _fmt, ##__VA_ARGS__); \
    ulog_hexdump(_ch, 0, &(ulog_arg_t) { ULOG_ARG_TYPE_ID_BUFFER, { .cptr_u8 = (uint8_t const*)_buffer }, _size }); \
} while (0)

#define ULOG_DBG(_fmt, ...) ULOG_PRINT(ULOG_MSG_CH_PRINT_DBG, _fmt "\n", ##__VA_ARGS__)
#define ULOG_INF(_fmt, ...) ULOG_PRINT(ULOG_MSG_CH_PRINT_INF ,_fmt "\n", ##__VA_ARGS__)
#define ULOG_WRN(_fmt, ...) ULOG_PRINT(ULOG_MSG_CH_PRINT_WRN ,_fmt "\n", ##__VA_ARGS__)
#define ULOG_ERR(_fmt, ...) ULOG_PRINT(ULOG_MSG_CH_PRINT_ERR ,_fmt "\n", ##__VA_ARGS__)

#define ULOG_HEXDUMP_DBG(_buffer, _size, _fmt, ...) ULOG_HEXDUMP(ULOG_MSG_CH_HEXDUMP_DBG, _buffer, _size, _fmt "\n", ##__VA_ARGS__)
#define ULOG_HEXDUMP_INF(_buffer, _size, _fmt, ...) ULOG_HEXDUMP(ULOG_MSG_CH_HEXDUMP_INF, _buffer, _size, _fmt "\n", ##__VA_ARGS__)
#define ULOG_HEXDUMP_WRN(_buffer, _size, _fmt, ...) ULOG_HEXDUMP(ULOG_MSG_CH_HEXDUMP_WRN, _buffer, _size, _fmt "\n", ##__VA_ARGS__)
#define ULOG_HEXDUMP_ERR(_buffer, _size, _fmt, ...) ULOG_HEXDUMP(ULOG_MSG_CH_HEXDUMP_ERR, _buffer, _size, _fmt "\n", ##__VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
