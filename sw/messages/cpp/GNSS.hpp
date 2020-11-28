#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace GNSS {
    const uint8_t system_id = 2;

    class FixData {
        FixData (int32_t _latitude, int32_t _longitude, uint32_t _time, uint16_t _altitude)
        : latitude(_latitude),
          longitude(_longitude),
          time(_time),
          altitude(_altitude)
        {}
    public:
        static const uint8_t id = 1;
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
        FixQuality (uint16_t _pdop, uint16_t _hdop, uint16_t _vdop, bool _fixed)
        : pdop(_pdop),
          hdop(_hdop),
          vdop(_vdop),
          fixed(_fixed)
        {}
    public:
        static const uint8_t id = 2;
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
        Track (uint16_t _speed, int16_t _true_course)
        : speed(_speed),
          true_course(_true_course)
        {}
    public:
        static const uint8_t id = 3;
        // 
        uint16_t speed;
        // 
        int16_t true_course;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace GNSS
} // end namespace messages
