#ifndef _ULOG_ARG_HPP_
#define _ULOG_ARG_HPP_

#include "ulog/internal/ulog_arg.h"
#include <cstdint>
#include <cstring>
#include <string>

class ulog_arg
{
private:
    ulog_arg_t arg;
    std::string str;
public:
    ulog_arg(ulog_arg_type_id_t id, std::uint8_t const* value, size_t size)
    {
        arg.id = id;
        std::memset(&arg.value, 0, sizeof(arg.value));

        if (ULOG_ARG_TYPE_ID_PTR_STR == id)
        {
            str = std::string((char*)value, size);
        }
        else
        {
            std::memcpy(&arg.value, value, size);
        }
    }

    ulog_arg_value_t value(void)
    {
        if (ULOG_ARG_TYPE_ID_PTR_STR == arg.id)
        {
            char const* ptr = str.c_str();
            std::memcpy(&arg.value, &ptr, sizeof(void*));
        }  
        return arg.value;
    }

    ulog_arg_type_id_t id(void)
    {
        return arg.id;
    }
};

#endif