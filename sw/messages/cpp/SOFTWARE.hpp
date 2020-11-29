#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace SOFTWARE {
    const uint8_t system_id = 3;

    class MissedDeadline {
    public:
        static const uint8_t id = 1;
        typedef std::array<uint8_t, 22> SerialArray;

        MissedDeadline (std::array<uint8_t, 16> _task_name, uint32_t _ticks_lates)
        : task_name(_task_name),
          ticks_lates(_ticks_lates)
        {}

        SerialArray serialize();

        // The taskname that missed a deadline
        std::array<uint8_t, 16> task_name;
        // The difference betweent the expected wait time and actual wait time.
        uint32_t ticks_lates;
    };

    class DebugLog {
    public:
        static const uint8_t id = 2;
        typedef std::array<uint8_t, 18> SerialArray;

        DebugLog (std::array<uint8_t, 16> _text)
        : text(_text)
        {}

        SerialArray serialize();

        // 
        std::array<uint8_t, 16> text;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace SOFTWARE
} // end namespace messages
