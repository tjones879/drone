#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace SOFTWARE {
    const uint8_t system_id = 3;

    class DebugLog {
        DebugLog (std::array<uint8_t, 16> _text)
        : text(_text)
        {}
    public:
        static const uint8_t id = 1;
        // 
        std::array<uint8_t, 16> text;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace SOFTWARE
} // end namespace messages
