#include "GNSS.hpp"

#include <cstring>

namespace messages {

namespace GNSS {
    const char * getMessageName(uint8_t messageId)
    {
        switch(messageId)
        {
        case FixData::id:
            return "GNSS::FixData";
        case FixQuality::id:
            return "GNSS::FixQuality";
        case Track::id:
            return "GNSS::Track";
        case InvalidSentence::id:
            return "GNSS::InvalidSentence";
        default:
            return "UNKNOWN GNSS message";
        }
    }

    FixData::SerialArray FixData::serialize()
    {
        FixData::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &latitude, sizeof(int32_t));
        std::memcpy(&output[6], &longitude, sizeof(int32_t));
        std::memcpy(&output[10], &time, sizeof(uint32_t));
        std::memcpy(&output[14], &altitude, sizeof(uint16_t));

        return output;
    }
    FixQuality::SerialArray FixQuality::serialize()
    {
        FixQuality::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &pdop, sizeof(float));
        std::memcpy(&output[6], &hdop, sizeof(float));
        std::memcpy(&output[10], &vdop, sizeof(float));
        std::memcpy(&output[14], &fixed, sizeof(bool));

        return output;
    }
    Track::SerialArray Track::serialize()
    {
        Track::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &speed, sizeof(uint16_t));
        std::memcpy(&output[4], &true_course, sizeof(int16_t));

        return output;
    }
    InvalidSentence::SerialArray InvalidSentence::serialize()
    {
        InvalidSentence::SerialArray output;
        output[0] = system_id;
        output[1] = id;

        std::memcpy(&output[2], &framing_error, sizeof(bool));
        std::memcpy(&output[3], &calculated_checksum, sizeof(uint8_t));
        std::memcpy(&output[4], &reported_checksum, sizeof(uint8_t));

        return output;
    }
} // end namespace GNSS
} // end namespace messages
