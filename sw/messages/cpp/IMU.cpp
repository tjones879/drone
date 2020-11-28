#include "IMU.hpp"

namespace messages {

namespace IMU {
    const char * getMessageName(uint8_t messageId)
    {
        switch(messageId)
        {
        case GyroSample::id:
            return "IMU::GyroSample";
        case AccelSample::id:
            return "IMU::AccelSample";
        case MagSample::id:
            return "IMU::MagSample";
        case GyroConfig::id:
            return "IMU::GyroConfig";
        case AccelConfig::id:
            return "IMU::AccelConfig";
        case MagConfig::id:
            return "IMU::MagConfig";
        default:
            return "UNKNOWN IMU message";
        }
    }
} // end namespace IMU
} // end namespace messages
