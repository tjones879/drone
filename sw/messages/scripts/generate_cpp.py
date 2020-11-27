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


def generateSystem(template_def: str, compiler_setting: dict, out_dir: str, sys_yml_file: str) -> message.System:
    system = message.parse_system_def(sys_yml_file, CppField)
    namespace = {
        'system': system,
        'messages': system.messages,
        'arguments': [],
        'initializer': []
    }
    template = Template(template_def, searchList=namespace,
                        compilerSettings=compiler_setting)
    with open(out_dir + '/' + system.name + '.hpp', 'w') as output:
        output.write(str(template))
    return system


def generateTopInclude(template_def: str, compiler_setting: dict, out_dir: str, systems: [message.System]):
    namespace = {
        'systems': systems
    }
    template = Template(template_def, searchList=namespace,
                        compilerSettings=compiler_setting)
    with open(out_dir + '/messages.hpp', 'w') as output:
        output.write(str(template))


def main():
    compiler_setting = {
        'directiveStartToken': '//#',
        'directiveEndToken': '//#',
    }

    # First generate all of our system files
    sys_template = open('scripts/templates/cpp_template_system.templ', 'r').read()
    out_dir = sys.argv[1]
    systems = []
    for sys_def in sys.argv[2:]:
        systems.append(generateSystem(sys_template, compiler_setting, out_dir, sys_def))

    # Now generate the top level include
    top_template = open('scripts/templates/cpp_template_top.templ', 'r').read()
    generateTopInclude(top_template, compiler_setting, out_dir, systems)


if __name__ == '__main__':
    main()