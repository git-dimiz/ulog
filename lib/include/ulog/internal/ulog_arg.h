#ifndef _ULOG_ARG_H_
#define _ULOG_ARG_H_

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

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
    ULOG_ARG_TYPE_ID_BUFFER,
    ULOG_ARG_TYPE_ID_NONE = -1,
} ulog_arg_type_id_t;

#define ULOG_ARG_TYPE_ID_OF(_type) (sizeof(_type) == 8 ? ULOG_ARG_TYPE_ID_U64 \
                                    : sizeof(_type) == 4 ? ULOG_ARG_TYPE_ID_U32 \
                                    : sizeof(_type) == 2 ? ULOG_ARG_TYPE_ID_U16 \
                                    : sizeof(_type) == 1 ? ULOG_ARG_TYPE_ID_U8 \
                                    : ULOG_ARG_TYPE_ID_NONE)

#define ulog_arg_type_id(x) _Generic(x, int : ULOG_ARG_TYPE_ID_OF(int), \
    default : _Generic(x, unsigned char  : ULOG_ARG_TYPE_ID_OF(unsigned char), \
    default : _Generic(x, uint8_t  : ULOG_ARG_TYPE_ID_OF(uint8_t), \
    default : _Generic(x, uint16_t : ULOG_ARG_TYPE_ID_OF(uint16_t), \
    default : _Generic(x, uint32_t : ULOG_ARG_TYPE_ID_OF(uint32_t), \
    default : _Generic(x, uint64_t : ULOG_ARG_TYPE_ID_OF(uint64_t), \
    default : _Generic(x, char     : ULOG_ARG_TYPE_ID_OF(char), \
    default : _Generic(x, int8_t   : ULOG_ARG_TYPE_ID_OF(int8_t), \
    default : _Generic(x, int16_t  : ULOG_ARG_TYPE_ID_OF(int16_t), \
    default : _Generic(x, int32_t  : ULOG_ARG_TYPE_ID_OF(int32_t), \
    default : _Generic(x, int64_t  : ULOG_ARG_TYPE_ID_OF(int64_t), \
    default : _Generic(x, float    : ULOG_ARG_TYPE_ID_OF(float), \
    default : _Generic(x, double   : ULOG_ARG_TYPE_ID_OF(double), \
    default : _Generic(x, uint8_t*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint16_t* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint32_t* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint64_t* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int8_t*   : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int16_t*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int32_t*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int64_t*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, float*    : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, double*   : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint8_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint16_t const* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint32_t const* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, uint64_t const* : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int8_t const*   : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int16_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int32_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, int64_t const*  : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, float const*    : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, double const*   : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, void*           : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, void const*     : ULOG_ARG_TYPE_ID_PTR, \
    default : _Generic(x, char*       : ULOG_ARG_TYPE_ID_PTR_STR, \
    default : _Generic(x, char const* : ULOG_ARG_TYPE_ID_PTR_STR, \
    default : ULOG_ARG_TYPE_ID_NONE)))))))))))))))))))))))))))))))))))))

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
    ssize_t size;
} ulog_arg_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
