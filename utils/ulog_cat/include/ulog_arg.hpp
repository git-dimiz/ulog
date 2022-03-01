#ifndef _ULOG_ARG_HPP_
#define _ULOG_ARG_HPP_

#include "ulog/internal/ulog_arg.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <unistd.h>

class ulog_arg
{
private:
    ulog_arg_t arg;
    std::string str;
    std::vector<std::uint8_t> buf;
public:
    ulog_arg(ulog_arg_type_id_t id, std::uint8_t const* value, size_t size)
    {
        arg.id = id;
        std::memset(&arg.value, 0, sizeof(arg.value));

        if (ULOG_ARG_TYPE_ID_PTR_STR == id)
        {
            str = std::string((char*)value, size);
        }
        else if(ULOG_ARG_TYPE_ID_BUFFER == id)
        {
            buf.assign((std::uint8_t*)value, ((std::uint8_t*)value) + size);
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
            arg.value.cstr = str.c_str();
        }
        else if (ULOG_ARG_TYPE_ID_BUFFER == arg.id)
        {
            arg.value.ptr_u8 = buf.data();
        }
        return arg.value;
    }

    ssize_t size(void)
    {
        if (ULOG_ARG_TYPE_ID_BUFFER == arg.id
            && 0 != buf.size())
        {
            return buf.size();
        }

        return -1;
    }

    ulog_arg_type_id_t id(void)
    {
        return arg.id;
    }
};

#endif