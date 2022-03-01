#ifndef _ULOG_MESSAGE_HPP_
#define _ULOG_MESSAGE_HPP_

#include "ulog_arg.hpp"
#include "ulog/internal/ulog_msg.h"
#include <cstdint>
#include <cstddef>
#include <vector>

class ulog_message
{
private:
    std::uint32_t _tag;
    std::uint32_t _channel;
    std::vector<ulog_arg> _va_list;
public:

    ulog_message() : _tag{0}, _channel{0}, _va_list{}
    {
    }

    ulog_message(std::uint32_t tag, std::uint32_t channel, std::vector<ulog_arg>& va_list)
    {
        _tag = tag;
        _channel = channel;
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

    std::uint32_t type(void)
    {
        return ULOG_MSG_CH_TYPE_GET(_channel);
    }

    std::uint32_t level(void)
    {
        return ULOG_MSG_CH_LVL_GET(_channel);
    }
};


#endif