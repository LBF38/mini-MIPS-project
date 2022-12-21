#!/usr/bin/env python3
# Ici, on définit les règles pour convertir les commandes assembleur en binaire.
# Utilisation de Regex pour vérifier les syntaxes par exemple.
# Lecture de fichiers, vérification des expressions, convertir en binaire selon règles binaires.

# Imports
import re
import struct
import sys
import os
from os import path


class Assembly:
    """Assembly class
    This class is used to assemble a file in asm format to a binary file
    """

    instructionSwitch = {
        "comment": {
            'regex': r"^\s*(#|\n|\r|\r\n).*$",
            'opcode': 99,
            'format': 'r'
        },
        "label": {
            'regex': r"^(.+):\s*$",
            'opcode': 99,
            'format': 'r'
        },
        "data": {
            'regex': r"^\s*([0-9]+)\s*#?(.*)$",
            'opcode': 99,
            'format': 'data'
        },
        'add': {
            'regex': r"^\s*(add)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 2,
            'format': 'r'
        },
        'addi': {
            'regex': r"^\s*(add)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 3,
            'format': 'i'
        },
        'sub': {
            'regex': r"^\s*(sub)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 4,
            'format': 'r'
        },
        'subi': {
            'regex': r"^\s*(sub)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 5,
            'format': 'i'
        },
        'mul': {
            'regex': r"^\s*(mul)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 6,
            'format': 'r'
        },
        'muli': {
            'regex': r"^\s*(mul)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 7,
            'format': 'i'
        },
        'div': {
            'regex': r"^\s*(div)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 8,
            'format': 'r'
        },
        'divi': {
            'regex': r"^\s*(div)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 9,
            'format': 'i'
        },
        'and': {
            'regex': r"^\s*(and)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 10,
            'format': 'r'
        },
        'andi': {
            'regex': r"^\s*(and)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 11,
            'format': 'i'
        },
        'or': {
            'regex': r"^\s*(or)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 12,
            'format': 'r'
        },
        'ori': {
            'regex': r"^\s*(or)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 13,
            'format': 'i'
        },
        'xor': {
            'regex': r"^\s*(xor)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 14,
            'format': 'r'
        },
        'xori': {
            'regex': r"^\s*(xor)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 15,
            'format': 'i'
        },
        'shl': {
            'regex': r"^\s*(shl)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 16,
            'format': 'r'
        },
        'shli': {
            'regex': r"^\s*(shl)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 17,
            'format': 'i'
        },
        'shr': {
            'regex': r"^\s*(shr)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 18,
            'format': 'r'
        },
        'shri': {
            'regex': r"^\s*(shr)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 19,
            'format': 'i'
        },
        'slt': {
            'regex': r"^\s*(slt)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 20,
            'format': 'r'
        },
        'slti': {
            'regex': r"^\s*(slt)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 21,
            'format': 'i'
        },
        'sle': {
            'regex': r"^\s*(sle)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 22,
            'format': 'r'
        },
        'slei': {
            'regex': r"^\s*(sle)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 23,
            'format': 'i'
        },
        'seq': {
            'regex': r"^\s*(seq)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 24,
            'format': 'r'
        },
        'seqi': {
            'regex': r"^\s*(seq)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 25,
            'format': 'i'
        },
        'load': {
            'regex': r"^\s*(load)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 27,
            'format': 'i'
        },
        'store': {
            'regex': r"^\s*(store)\s+r(\d+)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 29,
            'format': 'i'
        },
        'jmpr': {
            'regex': r"^\s*(jmp)\s+r(\d+)\s+r(\d+)",
            'opcode': 30,
            'format': 'jr'
        },
        'jmpi': {
            'regex': r"^\s*(jmp)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 31,
            'format': 'ji'
        },
        'braz': {
            'regex': r"^\s*(braz)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 32,
            'format': 'b'
        },
        'branz': {
            'regex': r"^\s*(branz)\s+r(\d+)\s+(-?\d+|\w+\b)",
            'opcode': 33,
            'format': 'b'
        },
        'scall': {
            'regex': r"^\s*(scall)\s+(-?\d+)",
            'opcode': 34,
            'format': 's'
        },
        'stop': {
            'regex': r"^\s*(stop)",
            'opcode': 35,
            'format': 'h'
        },
    }
    address = 0
    labels = {}
    labels_used = {}
    opcode = 0
    arg1 = 0
    arg2 = 0
    arg3 = 0
    format = 'r'

    def __init__(self, source, destination) -> None:
        """
        Class constructor
        """
        print("This is the Assembly class to assemble files for a mini-MIPS Virtual Machine.\n")
        self.read_file(source)
        self.assembling_file(destination)

    def read_file(self, source):
        """
        Lit le fichier et stocke les lignes du fichier
        """
        file = open(source, 'r')
        self.the_lines = file.readlines()
        file.close()

    def assembling_file(self, destination):
        """
        This function will assemble the file
        """
        self.binary_instruction_list = []
        # self.check_labels()
        for line in self.the_lines:
            line.strip()
            # check comments
            matching = re.compile(
                self.instructionSwitch['comment']['regex']).match(line)
            if matching:
                continue
            # check labels
            matching = re.compile(
                self.instructionSwitch['label']['regex']).match(line)
            if matching:
                self.labels[matching.group(1)] = self.address
            # check which instruction is in the line
            matching = self.check_instruction(line)
            if matching:
                label = self.store_instruction(matching)
                # convert it to a binary code
                if (not label):
                    encodedInstruction = Encode(
                        self.opcode, self.arg1, self.arg2, self.arg3, self.format).encode()
                else:
                    encodedInstruction = Encode(
                        self.opcode, self.arg1, self.arg2, self.arg3, self.format).encode()
                    self.labels_used[self.address] = label
                self.binary_instruction_list.append(encodedInstruction)
                self.address += 1
        for key, value in self.labels_used.items():
            address = key
            label = value
            self.binary_instruction_list[address] = self.binary_instruction_list[address] | self.labels[label]
        print(f"dict labels : {self.labels}")
        # store all assembled instructions into the output binary file
        self.write_binary_file(destination)

    def check_instruction(self, line):
        """
        check which asm instruction is asked in the given line and return the corresponding encoding
        Example: can read instructions like "add r0, r1, r2"
        :return: Boolean : True if instruction correct and calls the function to store data recognized.
        False if comment to pass to next line.
        """
        # Définit les cas pour chaque instruction
        for case in self.instructionSwitch.items():
            key, value = case
            expression_string = value['regex']
            expression = re.compile(expression_string)
            matching = expression.match(line)
            if matching:
                print(f"match with: {key} = {value['opcode']}")
                self.opcode = value['opcode']
                self.format = value['format']
                if key == "comment":
                    # print("A comment has been recognized.")
                    # print(f"This is the recognized line : {line}")
                    return None
                if key == "label":
                    # print("A label has been recognized.")
                    # print(f"This is the recognized line : {line}")
                    return None
                return matching
        raise Exception(
            f"error reading instruction : no matching instruction with line : {line}")

    def store_instruction(self, matching):
        """
        This function will store the instruction in the class for later encoding it
        """
        if self.format in 'r':
            self.arg1 = int(matching.group(2))
            self.arg2 = int(matching.group(3))
            self.arg3 = int(matching.group(4))
        if self.format in 'i':
            self.arg1 = int(matching.group(2))
            try:
                self.arg2 = int(matching.group(3))
            except ValueError as error:
                self.arg2 = 0
                print(
                    f"solved error {error} with label : {matching.group(3)}. Set argument at 0. Returned the label")
                return matching.group(3)
            try:
                self.arg3 = int(matching.group(4))
            except ValueError as error:
                self.arg3 = 0
                print(
                    f"solved error {error} with label : {matching.group(4)}. Set argument at 0. Returned the label")
                return matching.group(4)
        if self.format in 'jr ji b':
            self.arg1 = int(matching.group(2))
            try:
                self.arg2 = int(matching.group(3))
            except ValueError as error:
                self.arg2 = 0
                print(
                    f"solved error {error} with label : {matching.group(3)}. Set argument at 0. Returned the label")
                return matching.group(3)
        if self.format in 's':
            self.arg1 = int(matching.group(2))
        if self.format in 'data':
            self.arg1 = int(matching.group(1))

    def write_binary_file(self, destination: str = "bin/destination.bin"):
        """
        Write the binary file for the given instruction
        """
        if not path.exists(path.dirname(destination)):  # creates output folder if it doesn't exist
            os.mkdir(path.dirname(destination))
        out_file = open(destination, "wb")
        print(self.binary_instruction_list)
        for value in self.binary_instruction_list:
            out_file.write(struct.pack("<L", value))
        out_file.close()

    def check_labels(self):
        """
        Check if there are labels in the file and store them in a dictionary
        It will be used to replace the label by the address of the instruction
        """
        self.labels = {}
        for i, line in enumerate(self.the_lines):
            matching = re.compile(
                self.instructionSwitch['label']['regex']).match(line)
            if matching:
                # adresse suivante, après le label.
                self.labels[matching.group(1)] = i+1
        print(self.labels)


class Encode:
    def __init__(self, opcode, arg1, arg2, arg3, format) -> None:
        """
        Class constructor
        """
        # print("This is the encoding class to encode instructions")
        self.opcode = opcode
        self.arg1 = arg1
        self.arg2 = arg2
        self.arg3 = arg3
        self.format = format

    def encode(self):
        """
        Simple switch to call the right encoding function
        (there is no switch in python for now => maybe in 3.10 ?)
        """
        switch = {
            'r': self.encode_r(),
            'i': self.encode_i(),
            'jr': self.encode_jr(),
            'ji': self.encode_ji(),
            'b': self.encode_b(),
            's': self.encode_s(),
            'h': self.encode_h(),
            'data': self.encode_data()
        }
        return switch[self.format]

    def encode_r(self):
        """
        Convert the recognized instruction into a binary instruction
        """
        if (self.opcode == None or self.arg1 == None or self.arg2 == None or self.arg3 == None):
            raise Exception(
                "Error input arguments. Please use valid arguments using integer type.\n")
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        rs1 = self.arg2 << 16
        rs2 = self.arg3 << 11
        binary_instruction = opcode | rd | rs1 | rs2
        return binary_instruction

    def encode_i(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode rd rs im
        """
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        rs = self.arg2 << 16
        im = self.arg3 & 0x0000ffff
        binary_instruction = opcode | rd | rs | im
        return binary_instruction

    def encode_jr(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode rd ra
        """
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        ra = self.arg2 << 16
        binary_instruction = opcode | rd | ra
        return binary_instruction

    def encode_ji(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode rd addr
        """
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        addr = self.arg2 & 0x000fffff
        binary_instruction = opcode | rd | addr
        return binary_instruction

    def encode_b(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode rs addr
        """
        opcode = self.opcode << 26
        rs = self.arg1 << 21
        addr = self.arg2 & 0x000fffff
        binary_instruction = opcode | rs | addr
        return binary_instruction

    def encode_s(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode n
        """
        opcode = self.opcode << 26
        n = self.arg1 & 0x03ffffff
        binary_instruction = opcode | n
        return binary_instruction

    def encode_h(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: opcode
        """
        opcode = self.opcode << 26
        binary_instruction = opcode
        return binary_instruction

    def encode_data(self):
        """
        Convert the recognized instruction into a binary instruction
        Format: data
        """
        return self.arg1


if __name__ == "__main__":
    try:
        source = sys.argv[1]
        # print(source)
    except IndexError as error:
        print("No source file given. Please provide a source file to assemble.")
        print(f"""
Usage:  {sys.argv[0]} <source_file> <destination_file>

Example: {sys.argv[0]} data/program.asm bin/program.bin

If no destination file is given, the default name will be bin/filename.bin""")
        sys.exit(-1)
    try:
        destination = sys.argv[2]
    except IndexError:
        # Default compilation named file => bin/filename.bin (where filename is the name of the given source file)
        matching = re.compile(r"^.*/(\w+).(\w+\b)").match(sys.argv[1])
        destination = f"bin/{matching.group(1)}.bin"
        print(
            f"No output file given. Writing in the corresponding file : {destination}\n")
    Assembly(source, destination)
