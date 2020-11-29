#include "messages.hpp"

namespace messages {
    const char *getMessageName(uint8_t systemId, uint8_t messageId)
    {
        switch(systemId)
        {
        //#for $system in $systems
        case $system.name::system_id:
            //#set $functionCall = '%s::getMessageName(messageId)' % $system.name
            return $functionCall;
        //#end for
        default:
            return "UNKNOWN SYSTEM";
        }
    }
} // end namespace messages
