#ifndef _ULOG_TOOLCHAIN_H_
#define _ULOG_TOOLCHAIN_H_

#if __clang__
    #include "ulog/internal/llvm.h"
#elif __GNUC__
    #include "ulog/internal/gcc.h"
#else
    #error "toolchain not supported"
#endif

#endif
