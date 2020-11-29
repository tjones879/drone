#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace IMU {
    const uint8_t system_id = 1;

    class GyroSample {
    public:
        static const uint8_t id = 1;
        typedef std::array<uint8_t, 8> SerialArray;

        GyroSample (int16_t _x, int16_t _y, int16_t _z)
        : x(_x),
          y(_y),
          z(_z)
        {}

        SerialArray serialize();

        // 
        int16_t x;
        // 
        int16_t y;
        // 
        int16_t z;
    };

    class AccelSample {
    public:
        static const uint8_t id = 2;
        typedef std::array<uint8_t, 8> SerialArray;

        AccelSample (int16_t _x, int16_t _y, int16_t _z)
        : x(_x),
          y(_y),
          z(_z)
        {}

        SerialArray serialize();

        // 
        int16_t x;
        // 
        int16_t y;
        // 
        int16_t z;
    };

    class MagSample {
    public:
        static const uint8_t id = 3;
        typedef std::array<uint8_t, 8> SerialArray;

        MagSample (int16_t _x, int16_t _y, int16_t _z)
        : x(_x),
          y(_y),
          z(_z)
        {}

        SerialArray serialize();

        // 
        int16_t x;
        // 
        int16_t y;
        // 
        int16_t z;
    };

    class GyroConfig {
    public:
        static const uint8_t id = 4;
        typedef std::array<uint8_t, 10> SerialArray;

        GyroConfig (int16_t _x_bias, int16_t _y_bias, int16_t _z_bias, uint16_t _sample_rate)
        : x_bias(_x_bias),
          y_bias(_y_bias),
          z_bias(_z_bias),
          sample_rate(_sample_rate)
        {}

        SerialArray serialize();

        // 
        int16_t x_bias;
        // 
        int16_t y_bias;
        // 
        int16_t z_bias;
        // sample_scale: - 245DPS - 500DPS - 2000DPS
        uint16_t sample_rate;
    };

    class AccelConfig {
    public:
        static const uint8_t id = 5;
        typedef std::array<uint8_t, 4> SerialArray;

        AccelConfig (uint16_t _sample_rate)
        : sample_rate(_sample_rate)
        {}

        SerialArray serialize();

        // sample_scale: - 2G - 4G - 8G - 16G
        uint16_t sample_rate;
    };

    class MagConfig {
    public:
        static const uint8_t id = 6;
        typedef std::array<uint8_t, 4> SerialArray;

        MagConfig (uint16_t _sample_rate)
        : sample_rate(_sample_rate)
        {}

        SerialArray serialize();

        // sample_scale: - 4G - 8G - 12G - 16G
        uint16_t sample_rate;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace IMU
} // end namespace messages
