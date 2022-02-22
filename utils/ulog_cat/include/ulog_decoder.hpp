#ifndef _ULOG_DECODER_HPP_
#define _ULOG_DECODER_HPP_

#include <cstddef>
#include <cstdint>
#include "ulog_message.hpp"
#include <deque>

class ulog_decoder
{
private:
    ulog_message _message;
public:
    ulog_message& message(void);
    int decode(std::deque<std::uint8_t>& data);
    int decode(std::uint8_t* data, std::size_t size);
};

#endif