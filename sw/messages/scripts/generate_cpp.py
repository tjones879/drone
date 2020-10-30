#!usr/bin/python

from Cheetah.Template import Template
import message
import sys
import textwrap

class CppField(message.Field):
    def type_str(self) -> str:
        if self.dtype == message.DataType.INT:
            return 'int%d_t' % self.size
        elif self.dtype == message.DataType.UINT:
            return 'uint%d_t' % self.size
        elif self.dtype == message.DataType.FLOAT:
            if self.size == 32:
                return 'float'
            else:
                return 'double'
        elif self.dtype == message.DataType.BYTES:
            return 'std::array<uint8_t, %d>' % self.size
        elif self.dtype == message.DataType.BOOL:
            return 'bool'

    def format_desc(self) -> str:
        if len(self.description) > 80:
            return textwrap.fill(self.description, width=75,
                                initial_indent='/** ',
                                subsequent_indent='    * ') + '\n    */'
        else:
            return '// ' + self.description


def main():
    templateDef = open('scripts/templates/cpp_template.templ', 'r').read()
    compiler_setting = {
        'directiveStartToken': '//#',
        'directiveEndToken': '//#',
    }
    namespace = {
        'system': None,
        'messages': None,
        'arguments': [],
        'initializer': []
    }
    out_dir = sys.argv[1]
    for sys_def in sys.argv[2:]:
        system = message.parse_system_def(sys_def, CppField)
        namespace = {
            'system': system,
            'messages': system.messages,
            'arguments': [],
            'initializer': []
        }
        template = Template(templateDef, searchList=namespace,
                            compilerSettings=compiler_setting)
        with open(out_dir + '/' + system.name + '.hpp', 'w') as output:
            output.write(str(template))


if __name__ == '__main__':
    main()
