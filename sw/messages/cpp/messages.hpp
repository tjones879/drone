#pragma once

#include "GNSS.hpp"
#include "IMU.hpp"

namespace messages {
    auto getMessageName(uint8_t systemId, uint8_t messageId) -> const char *
    {
        switch(systemId)
        {
        case GNSS::system_id:
            return GNSS::getMessageName(messageId);
        case IMU::system_id:
            return IMU::getMessageName(messageId);
        default:
            return "UNKNOWN SYSTEM";
        }
    }
} // end namespace messages