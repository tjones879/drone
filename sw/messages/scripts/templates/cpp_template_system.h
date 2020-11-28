#pragma once
#include <array>
#include <stdint.h>

namespace messages {

namespace $system.name {
    const uint8_t system_id = $system.id;

    //#for $message in $messages
    class $message.name {
        //#set $arguments = [field.type_str() + ' _' + field.name for field in $message.fields]
        //#set $initializer = ['%s(_%s)' % (field.name, field.name) for field in $message.fields]
        $message.name (//#echo ', '.join($arguments)//#)
        //#echo '        : ' + ',\n          '.join($initializer)

        {}
    public:
        static const uint8_t id = $message.id;
        //#for $field in message.fields
        $field.format_desc()
        $field.type_str() $field.name;
        //#end for
    };

    //#end for

    const char * getMessageName(uint8_t messageId);
} // end namespace $system.name
} // end namespace messages
