#ifndef _ULOG_H_
#define _ULOG_H_

#include <stdint.h>
#include <stddef.h>
#include "ulog/internal/cpp_magic.h"
#include "ulog/internal/ulog_arg.h"
#include "ulog/internal/ulog_hash.h"
#include "ulog/internal/toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ULOG_SECTION_RODATA ".ulog_rodata"
#define __ulog_rodata __section(ULOG_SECTION_RODATA)

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
int ulog_vprintf(const uint32_t tag, ulog_arg_t const* arg_list, size_t size);
void ulog_deinit(void);

#define ARG_LIST_ENTRY(x) (ulog_arg_t){ulog_arg_type_id(x), (ulog_arg_value_t)x}
#define MAP_ARGS(op,sep,...) \
  IF(HAS_ARGS(__VA_ARGS__))(EVAL(MAP_ARGS_INNER(op,sep,__VA_ARGS__)))
#define MAP_ARGS_INNER(op,sep,cur_val_1, ...) \
  op(cur_val_1) \
  IF(HAS_ARGS(__VA_ARGS__))( \
    sep() DEFER2(_MAP_ARGS_INNER)()(op, sep, __VA_ARGS__) \
  )
#define _MAP_ARGS_INNER() MAP_ARGS_INNER

#define ULOG_RAW(_fmt, ...) do { \
    static const char fmt[] __ulog_rodata = _fmt; \
    ULOG_HASH_STR_ASSERT(_fmt); \
    static const uint32_t tag = ULOG_HASH(_fmt); \
    IF(HAS_ARGS(__VA_ARGS__))( \
        ulog_dummy_printf(fmt, __VA_ARGS__); \
        const ulog_arg_t arg_list[] = {MAP_ARGS(ARG_LIST_ENTRY, COMMA, __VA_ARGS__)}; \
        ulog_vprintf(tag, arg_list, sizeof(arg_list) / sizeof(arg_list[0])); \
    ) \
    IF(NOT(HAS_ARGS(__VA_ARGS__)))((void)fmt; ulog_vprintf(tag, NULL, 0);) \
} while (0)

#define ULOG_DBG(_fmt, ...) ULOG_RAW("DBG: " _fmt "\n", ##__VA_ARGS__)
#define ULOG_INF(_fmt, ...) ULOG_RAW("INF: " _fmt "\n", ##__VA_ARGS__)
#define ULOG_WRN(_fmt, ...) ULOG_RAW("WRN: " _fmt "\n", ##__VA_ARGS__)
#define ULOG_ERR(_fmt, ...) ULOG_RAW("ERR: " _fmt "\n", ##__VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
