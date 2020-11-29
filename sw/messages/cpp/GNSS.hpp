#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace GNSS {
    const uint8_t system_id = 2;

    class FixData {
    public:
        static const uint8_t id = 1;
        typedef std::array<uint8_t, 16> SerialArray;

        FixData (int32_t _latitude, int32_t _longitude, uint32_t _time, uint16_t _altitude)
        : latitude(_latitude),
          longitude(_longitude),
          time(_time),
          altitude(_altitude)
        {}

        SerialArray serialize();

        // 
        int32_t latitude;
        // 
        int32_t longitude;
        // 
        uint32_t time;
        // 
        uint16_t altitude;
    };

    class FixQuality {
    public:
        static const uint8_t id = 2;
        typedef std::array<uint8_t, 9> SerialArray;

        FixQuality (uint16_t _pdop, uint16_t _hdop, uint16_t _vdop, bool _fixed)
        : pdop(_pdop),
          hdop(_hdop),
          vdop(_vdop),
          fixed(_fixed)
        {}

        SerialArray serialize();

        // Position dilution of precision
        uint16_t pdop;
        // Horizontal dilution of precision
        uint16_t hdop;
        // Vertical dilution of precision
        uint16_t vdop;
        // Flag to indicate if a valid satellite lock has been acquired.
        bool fixed;
    };

    class Track {
    public:
        static const uint8_t id = 3;
        typedef std::array<uint8_t, 6> SerialArray;

        Track (uint16_t _speed, int16_t _true_course)
        : speed(_speed),
          true_course(_true_course)
        {}

        SerialArray serialize();

        // 
        uint16_t speed;
        // 
        int16_t true_course;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace GNSS
} // end namespace messages
