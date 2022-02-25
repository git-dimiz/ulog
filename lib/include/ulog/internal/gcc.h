#ifndef _ULOG_GCC_H_
#define _ULOG_GCC_H_

#ifndef __printf_like
    #define __printf_like(f, a) __attribute__((format (printf, f, a)))
#endif

#ifndef __section
    #define __section(_name) __attribute__((section(_name)))
#endif

#endif
