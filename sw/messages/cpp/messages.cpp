#include "messages.hpp"

namespace messages {
    const char *getMessageName(uint8_t systemId, uint8_t messageId)
    {
        switch(systemId)
        {
        case GNSS::system_id:
            return GNSS::getMessageName(messageId);
        case IMU::system_id:
            return IMU::getMessageName(messageId);
        case SOFTWARE::system_id:
            return SOFTWARE::getMessageName(messageId);
        default:
            return "UNKNOWN SYSTEM";
        }
    }
} // end namespace messages
