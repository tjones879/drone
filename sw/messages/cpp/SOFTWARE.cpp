#include "SOFTWARE.hpp"

#include <cstring>

namespace messages {

namespace SOFTWARE {
    const char * getMessageName(uint8_t messageId)
    {
        switch(messageId)
        {
        case MissedDeadline::id:
            return "SOFTWARE::MissedDeadline";
        case DebugLog::id:
            return "SOFTWARE::DebugLog";
        default:
            return "UNKNOWN SOFTWARE message";
        }
    }

    MissedDeadline::SerialArray MissedDeadline::serialize()
    {
        MissedDeadline::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &task_name, sizeof(std::array<uint8_t, 16>));
        std::memcpy(&output[18], &ticks_lates, sizeof(uint32_t));

        return output;
    }
    DebugLog::SerialArray DebugLog::serialize()
    {
        DebugLog::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &text, sizeof(std::array<uint8_t, 16>));

        return output;
    }
} // end namespace SOFTWARE
} // end namespace messages
