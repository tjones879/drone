#include "SOFTWARE.hpp"

namespace messages {

namespace SOFTWARE {
    const char * getMessageName(uint8_t messageId)
    {
        switch(messageId)
        {
        case DebugLog::id:
            return "SOFTWARE::DebugLog";
        default:
            return "UNKNOWN SOFTWARE message";
        }
    }
} // end namespace SOFTWARE
} // end namespace messages
