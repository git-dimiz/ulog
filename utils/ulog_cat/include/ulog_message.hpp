#ifndef _ULOG_MESSAGE_HPP_
#define _ULOG_MESSAGE_HPP_

#include "ulog_arg.hpp"
#include <cstdint>
#include <cstddef>
#include <vector>

class ulog_message
{
private:
    std::uint32_t _tag;
    std::vector<ulog_arg> _va_list;
public:
    ulog_message()
    {
        _tag = 0;
        _va_list = std::vector<ulog_arg>();
    }

    ulog_message(std::uint32_t tag, std::vector<ulog_arg>& va_list)
    {
        _tag = tag;
        _va_list = va_list;
    }

    std::vector<ulog_arg>& va_list(void)
    {
        return _va_list;
    }

    std::uint32_t tag(void)
    {
        return _tag;
    }
};


#endif