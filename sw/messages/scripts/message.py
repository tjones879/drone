#!/usr/bin/python

import yaml
from enum import Enum
import re


class DataType(Enum):
    UNKNOWN = 0
    INT = 1
    UINT = 2
    FLOAT = 3
    BYTES = 4
    BOOL = 5
    ENUM = 6

    @staticmethod
    def from_str(field_type: str) -> 'DataType':
        label = field_type.lower()
        size = re.match('.*?([0-9]+)$', label)
        if 'uint' in label:
            return DataType.UINT, int(size.group(1))
        elif 'int' in label:
            return DataType.INT, int(size.group(1))
        elif 'float' in label:
            return DataType.FLOAT, int(size.group(1))
        elif 'byte' in label:
            return DataType.BYTES, int(size.group(1))
        elif 'bool' in label:
            return DataType.BOOL, 1
        else:
            return None, None

class Field:
    def __init__(self, name: str, dtype: DataType, size: int, description: str):
        self.name = name
        self.dtype = dtype
        self.size = size
        self.description = description

    def type_str(self) -> str:
        raise NotImplementedError("MUST IMPLEMENT")


class Message:
    def __init__(self, msg_name: str, id: int):
        self.name = msg_name
        self.fields = []
        self.id = id

    def addField(self, field: Field):
        self.fields.append(field)

    def __str__(self) -> str:
        return self.name

    def size(self) -> int:
        accum = 2 # SYS_ID + MSG_ID
        for field in self.fields:
            accum += int((field.size + 7) / 8)
        return accum


class System:
    def __init__(self, name: str, id: int):
        self.name = name
        self.id = id
        self.messages = []

    def addMessage(self, msg: Message):
        self.messages.append(msg)

    def __str__(self) -> str:
        msgs = ', '.join([str(m) for m in self.messages])
        return self.name + '; ID: ' + str(self.id) + '; MESSAGES: ' + msgs


def parse_system_def(yaml_file, field_repr: type) -> System:
    with open(yaml_file, 'r') as yml:
        msg_def = yaml.load(yml.read())
        system = System(msg_def['system_name'], msg_def['id'])
        curr_id = 1
        for key, message in msg_def['messages'].items():
            msg = Message(key, curr_id)
            for field_name, field_def in message['fields'].items():
                dtype, size = DataType.from_str(field_def['type'])
                desc = field_def['description'] if 'description' in field_def else ''
                msg.addField(field_repr(field_name, dtype, size, desc))
            system.addMessage(msg)
            curr_id += 1
        return system


if __name__ == '__main__':
    print(parse_system_def('gnss.yml'), Field)
