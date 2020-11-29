#pragma once

#include "GNSS.hpp"
#include "IMU.hpp"
#include "SOFTWARE.hpp"

namespace messages {
    const char *getMessageName(uint8_t systemId, uint8_t messageId);
} // end namespace messages
