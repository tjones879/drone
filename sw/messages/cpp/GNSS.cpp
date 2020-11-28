#include "GNSS.hpp"

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
        default:
            return "UNKNOWN GNSS message";
        }
    }
} // end namespace GNSS
} // end namespace messages
