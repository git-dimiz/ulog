#ifndef _ULOG_ARG_H_
#define _ULOG_ARG_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ULOG_ARG_TYPE_ID_U8,
    ULOG_ARG_TYPE_ID_U16,
    ULOG_ARG_TYPE_ID_U32,
    ULOG_ARG_TYPE_ID_U64,
    ULOG_ARG_TYPE_ID_PTR,
    ULOG_ARG_TYPE_ID_PTR_STR,
    ULOG_ARG_TYPE_ID_NONE = -1,
} ulog_arg_type_id_t;

#define ulog_arg_type_id(v) _Generic(v, \
    uint8_t     : ULOG_ARG_TYPE_ID_U8, \
    uint16_t    : ULOG_ARG_TYPE_ID_U16, \
    uint32_t    : ULOG_ARG_TYPE_ID_U32, \
    uint64_t    : ULOG_ARG_TYPE_ID_U64, \
    int8_t      : ULOG_ARG_TYPE_ID_U8, \
    int16_t     : ULOG_ARG_TYPE_ID_U16, \
    int32_t     : ULOG_ARG_TYPE_ID_U32, \
    int64_t     : ULOG_ARG_TYPE_ID_U64, \
    float       : ULOG_ARG_TYPE_ID_U32, \
    double      : ULOG_ARG_TYPE_ID_U64, \
    uint8_t*    : ULOG_ARG_TYPE_ID_PTR, \
    uint16_t*   : ULOG_ARG_TYPE_ID_PTR, \
    uint32_t*   : ULOG_ARG_TYPE_ID_PTR, \
    uint64_t*   : ULOG_ARG_TYPE_ID_PTR, \
    int8_t*     : ULOG_ARG_TYPE_ID_PTR, \
    int16_t*    : ULOG_ARG_TYPE_ID_PTR, \
    int32_t*    : ULOG_ARG_TYPE_ID_PTR, \
    int64_t*    : ULOG_ARG_TYPE_ID_PTR, \
    float*      : ULOG_ARG_TYPE_ID_PTR, \
    double*     : ULOG_ARG_TYPE_ID_PTR, \
    uint8_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    uint16_t const* : ULOG_ARG_TYPE_ID_PTR, \
    uint32_t const* : ULOG_ARG_TYPE_ID_PTR, \
    uint64_t const* : ULOG_ARG_TYPE_ID_PTR, \
    int8_t const*   : ULOG_ARG_TYPE_ID_PTR, \
    int16_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    int32_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    int64_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    float const*    : ULOG_ARG_TYPE_ID_PTR, \
    double const*   : ULOG_ARG_TYPE_ID_PTR, \
    void*           : ULOG_ARG_TYPE_ID_PTR, \
    void const*     : ULOG_ARG_TYPE_ID_PTR, \
    char*       : ULOG_ARG_TYPE_ID_PTR_STR, \
    char const* : ULOG_ARG_TYPE_ID_PTR_STR, \
    default     : ULOG_ARG_TYPE_ID_NONE \
)

typedef union ulog_arg_value_u
{
    char c;
    int i;
    short s;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    double f64;
    uint8_t* ptr_u8;
    uint16_t* ptr_u16;
    uint32_t* ptr_u32;
    uint64_t* ptr_u64;
    int8_t* ptr_i8;
    int16_t* ptr_i16;
    int32_t* ptr_i32;
    int64_t* ptr_i64;
    float* ptr_f32;
    double* ptr_f64;
    uint8_t const* cptr_u8;
    uint16_t const* cptr_u16;
    uint32_t const* cptr_u32;
    uint64_t const* cptr_u64;
    int8_t const* cptr_i8;
    int16_t const* cptr_i16;
    int32_t const* cptr_i32;
    int64_t const* cptr_i64;
    float const* cptr_f32;
    double const* cptr_f64;
    void* ptr_v;
    void const* cptr_v;
    char* str;
    char const* cstr;
} ulog_arg_value_t;

typedef struct 
{
    ulog_arg_type_id_t id;
    ulog_arg_value_t value;
} ulog_arg_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif