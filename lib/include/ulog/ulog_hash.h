#ifndef _ULOG_HASH_H_
#define _ULOG_HASH_H_

#include <stdint.h>

#include "pw_tokenizer_65599_fixed_length_80_hash_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ULOG_HASH(str) PW_TOKENIZER_65599_FIXED_LENGTH_80_HASH(str)

static inline uint32_t ulog_hash(char const* str, size_t len)
{

    uint32_t hash = len;
    const uint32_t seed = 65599;
    uint32_t coefficient = seed;

    for (size_t i = 0; i < len; ++i)
    {
        hash += coefficient * (uint8_t)str[i];
        coefficient *= seed;
    }
    return hash;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
