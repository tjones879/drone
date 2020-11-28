//#set $header = "%s.hpp" % $system.name
#include "$header"

namespace messages {

namespace $system.name {
    const char * getMessageName(uint8_t messageId)
    {
        switch(messageId)
        {
        //#for $message in sorted($messages, key=lambda x: x.id)
        //#set $id_var = '%s::id' % $message.name
        case $id_var:
            return "$system.name::$message.name";
        //#end for
        default:
            return "UNKNOWN $system.name message";
        }
    }
} // end namespace $system.name
} // end namespace messages
