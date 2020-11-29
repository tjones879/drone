#include "IMU.hpp"

#include <cstring>

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

    GyroSample::SerialArray GyroSample::serialize()
    {
        GyroSample::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &x, sizeof(int16_t));
        std::memcpy(&output[4], &y, sizeof(int16_t));
        std::memcpy(&output[6], &z, sizeof(int16_t));

        return output;
    }
    AccelSample::SerialArray AccelSample::serialize()
    {
        AccelSample::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &x, sizeof(int16_t));
        std::memcpy(&output[4], &y, sizeof(int16_t));
        std::memcpy(&output[6], &z, sizeof(int16_t));

        return output;
    }
    MagSample::SerialArray MagSample::serialize()
    {
        MagSample::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &x, sizeof(int16_t));
        std::memcpy(&output[4], &y, sizeof(int16_t));
        std::memcpy(&output[6], &z, sizeof(int16_t));

        return output;
    }
    GyroConfig::SerialArray GyroConfig::serialize()
    {
        GyroConfig::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &x_bias, sizeof(int16_t));
        std::memcpy(&output[4], &y_bias, sizeof(int16_t));
        std::memcpy(&output[6], &z_bias, sizeof(int16_t));
        std::memcpy(&output[8], &sample_rate, sizeof(uint16_t));

        return output;
    }
    AccelConfig::SerialArray AccelConfig::serialize()
    {
        AccelConfig::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &sample_rate, sizeof(uint16_t));

        return output;
    }
    MagConfig::SerialArray MagConfig::serialize()
    {
        MagConfig::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &sample_rate, sizeof(uint16_t));

        return output;
    }
} // end namespace IMU
} // end namespace messages
