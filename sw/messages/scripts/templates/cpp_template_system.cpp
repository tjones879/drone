//#set $header = "%s.hpp" % $system.name
#include "$header"

#include <cstring>

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

    //#for $message in sorted($messages, key=lambda x: x.id)
    //#set $ret_type = '%s::SerialArray' % $message.name
    //#set $serialize_method = '%s::serialize()' % $message.name
    $ret_type $serialize_method
    {
        $ret_type output;
        output[0] = system_id;
        output[1] = id;

        //#set $pos = 2
        //#for $field in message.fields
        std::memcpy(&output[$pos], &$field.name, sizeof($field.type_str()));
        //#set $pos = pos + int(($field.size + 7) / 8)
        //#end for

        return output;
    }
    //#end for
} // end namespace $system.name
} // end namespace messages
