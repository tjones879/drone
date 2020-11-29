#pragma once

//#for $system in $systems
//#set $header = '%s.hpp' % system.name
#include "$header"
//#end for

namespace messages {
    const char *getMessageName(uint8_t systemId, uint8_t messageId);
} // end namespace messages
