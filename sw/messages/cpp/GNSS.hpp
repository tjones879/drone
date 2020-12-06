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

    class InvalidSentence {
    public:
        static const uint8_t id = 4;
        typedef std::array<uint8_t, 5> SerialArray;

        InvalidSentence (bool _framing_error, uint8_t _calculated_checksum, uint8_t _reported_checksum)
        : framing_error(_framing_error),
          calculated_checksum(_calculated_checksum),
          reported_checksum(_reported_checksum)
        {}

        SerialArray serialize();

        /**
         * Indicate whether there is a framing error present in the NMEA
         * sentence. If the value of this flag is true, then the calculated
         * and reported checksums should be ignored.
         */
        bool framing_error;
        /**
         * The calculated checksum from the input NMEA sentence. The value
         * of the calculated checksum is only valid when the framing error
         * flag is false.
         */
        uint8_t calculated_checksum;
        /**
         * The checksum provided by the GPS receiver. The value of the
         * reported checksum is only valid when the framing error flag is
         * false.
         */
        uint8_t reported_checksum;
    };


    const char * getMessageName(uint8_t messageId);
} // end namespace GNSS
} // end namespace messages
