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
            return 'std::array<uint8_t, %d>' % int((self.size + 7)//8)
        elif self.dtype == message.DataType.BOOL:
            return 'bool'

    def format_desc(self) -> str:
        if len(self.description) > 80:
            prefix = '/**\n'
            comment = textwrap.fill(self.description, width=75,
                                    initial_indent='         * ',
                                    subsequent_indent='         * ')
            suffix = '\n         */'
            return prefix + comment + suffix
        else:
            return '// ' + self.description


def generateSystem(templs: (str, str), compiler_setting: dict, out_dir: str, sys_yml_file: str) -> message.System:
    system = message.parse_system_def(sys_yml_file, CppField)
    namespace = {
        'system': system,
        'messages': system.messages,
        'arguments': [],
        'initializer': []
    }
    header_templ, cpp_templ = templs
    header = Template(header_templ, searchList=namespace,
                      compilerSettings=compiler_setting)
    cpp = Template(cpp_templ, searchList=namespace,
                   compilerSettings=compiler_setting)
    with open(out_dir + '/' + system.name + '.hpp', 'w') as output:
        output.write(str(header))
    with open(out_dir + '/' + system.name + '.cpp', 'w') as output:
        output.write(str(cpp))

    return system


def generateTopInclude(templs: (str, str), compiler_setting: dict, out_dir: str, systems: [message.System]):
    namespace = {
        'systems': systems
    }
    header_templ, cpp_templ = templs
    header = Template(header_templ, searchList=namespace,
                      compilerSettings=compiler_setting)
    with open(out_dir + '/messages.hpp', 'w') as output:
        output.write(str(header))
    cpp = Template(cpp_templ, searchList=namespace,
                   compilerSettings=compiler_setting)
    with open(out_dir + '/messages.cpp', 'w') as output:
        output.write(str(cpp))


def main():
    compiler_setting = {
        'directiveStartToken': '//#',
        'directiveEndToken': '//#',
    }

    # First generate all of our system files
    sys_header_template = open('scripts/templates/cpp_template_system.h', 'r').read()
    sys_cpp_template =  open('scripts/templates/cpp_template_system.cpp', 'r').read()
    sys_templs = (sys_header_template, sys_cpp_template)
    out_dir = sys.argv[1]
    systems = []
    for sys_def in sys.argv[2:]:
        systems.append(generateSystem(sys_templs, compiler_setting, out_dir, sys_def))

    # Now generate the top level include
    top_header_template = open('scripts/templates/cpp_template_top.h', 'r').read()
    top_cpp_template = open('scripts/templates/cpp_template_top.cpp', 'r').read()
    top_templs = (top_header_template, top_cpp_template)
    generateTopInclude(top_templs, compiler_setting, out_dir, systems)


if __name__ == '__main__':
    main()
