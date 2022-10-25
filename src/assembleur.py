#!/usr/bin/env python3
# Ici, on définit les règles pour convertir les commandes assembleur en binaire.
# Utilisation de Regex pour vérifier les syntaxes par exemple.
# Lecture de fichiers, vérification des expressions, convertir en binaire selon règles binaires.

# TODO vérifier fonctionnement des fonctions pour l'opérateur ADD et ADDI
# TODO tester le fichier binaire dans la VM / ISS.
# TODO implémenter de nouvelles commandes simples (SUB, MULT, ...)
# TODO gérer les labels
# TODO implémenter de nouvelles commandes complexes (JUMP, B)


# Imports
import re
import struct
import sys


class Assembly():
    instructionSwitch = {
        "comment": {
            'regex': "\s*#.*$",
            'opcode': 99,
            'format': 'r'
        },
        "label": {
            'regex':"^(.*):\s*$",
            'opcode':99,
            'format':'r'
        },
        'add': {
            'regex': "^\s*(add)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 2,
            'format': 'r'
        },
        'addi': {
            'regex': "^\s*(addi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 3,
            'format': 'i'
        },
        'sub': {
            'regex': "^\s*(sub)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 4,
            'format': 'r'
        },
        'subi': {
            'regex': "^\s*(subi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 5,
            'format': 'i'
        },
        'mul': {
            'regex': "^\s*(mul)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 6,
            'format': 'r'
        },
        'muli': {
            'regex': "^\s*(muli)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 7,
            'format': 'i'
        },
        'div': {
            'regex': "^\s*(div)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 8,
            'format': 'r'
        },
        'divi': {
            'regex': "^\s*(divi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 9,
            'format': 'i'
        },
        'and': {
            'regex': "^\s*(and)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 10,
            'format': 'r'
        },
        'andi': {
            'regex': "^\s*(andi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 11,
            'format': 'i'
        },
        'or': {
            'regex': "^\s*(or)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 12,
            'format': 'r'
        },
        'ori': {
            'regex': "^\s*(ori)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 13,
            'format': 'i'
        },
        'xor': {
            'regex': "^\s*(xor)\s+r(\d+)\s+r(\d+)\s+r(\d+)",
            'opcode': 14,
            'format': 'r'
        },
        'xori': {
            'regex': "^\s*(xori)\s+r(\d+)\s+r(\d+)\s+(-?\d+)",
            'opcode': 15,
            'format': 'i'
        },
        'stop': {
            'regex': "^\s*(stop)",
            'opcode': 35,
            'format': 'h'
        },
    }

    def __init__(self, source, destination) -> None:
        print("This is the Assembly class to assemble files for a mini-MIPS Virtual Machine.\n")
        self.read_file(source)
        self.assembling_file(destination)

    def read_file(self, filename):
        """
        Lit le fichier et stocke les lignes du fichier
        """
        file = open(filename, 'r')
        self.the_lines = file.readlines()
        file.close()

    def assembling_file(self, destination):
        self.binary_instruction_list = []
        for line in self.the_lines:
            line.strip()
            # check which instruction is in the line
            if (self.check_instruction(line)):
                # convert it to a binary code
                self.binary_instruction_list.append(
                    Encode(self.opcode, self.arg1, self.arg2, self.arg3, self.format).encode())
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
                    print("A comment has been recognized.")
                    print(f"This is the recognized line : {line}")
                    return False
                if key == "label":
                    print("A label has been recognized.")
                    print(f"This is the recognized line : {line}")
                    return False
                self.store_instruction(matching)
                return True

        raise Exception("error input file : no matching instruction")

    def store_instruction(self, matching):
        if self.format in 'ri':
            self.arg1 = int(matching.group(2))
            self.arg2 = int(matching.group(3))
            self.arg3 = int(matching.group(4))
        if self.format in 'jr ji b':
            self.arg1 = int(matching.group(2))
            self.arg2 = int(matching.group(3))
        if self.format in 's':
            self.arg1 = int(matching.group(2))

    def write_binary_file(self, destination: str = "bin/destination.bin"):
        """
        Write the binary file for the given instruction
        """
        out_file = open(destination, "wb")
        print(self.binary_instruction_list)
        for value in self.binary_instruction_list:
            out_file.write(struct.pack("<L", value))
        out_file.close()


class Encode():
    def __init__(self, opcode, arg1, arg2, arg3, format) -> None:
        print("This is the encoding class to encode instructions")
        self.opcode = opcode
        self.arg1 = arg1
        self.arg2 = arg2
        self.arg3 = arg3
        self.format = format

    def encode(self):
        switch = {
            'r': self.encode_r(),
            'i': self.encode_i(),
            'jr': self.encode_jr(),
            'ji': self.encode_ji(),
            'b': self.encode_b(),
            's': self.encode_s(),
            'h': self.encode_h()
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
        """
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        ra = self.arg2 << 16
        binary_instruction = opcode | rd | ra
        return binary_instruction

    def encode_ji(self):
        """
        Convert the recognized instruction into a binary instruction
        """
        opcode = self.opcode << 26
        rd = self.arg1 << 21
        addr = self.arg2 & 0x000fffff
        binary_instruction = opcode | rd | addr
        return binary_instruction

    def encode_b(self):
        """
        Convert the recognized instruction into a binary instruction
        """
        opcode = self.opcode << 26
        rs = self.arg1 << 21
        addr = self.arg2 & 0x000fffff
        binary_instruction = opcode | rs | addr
        return binary_instruction

    def encode_s(self):
        """
        Convert the recognized instruction into a binary instruction
        """
        opcode = self.opcode << 26
        n = self.arg1 & 0x03ffffff
        binary_instruction = opcode | n
        return binary_instruction

    def encode_h(self):
        """
        Convert the recognized instruction into a binary instruction
        """
        opcode = self.opcode << 26
        binary_instruction = opcode
        return binary_instruction


if __name__ == "__main__":
    # print("Testing the check function")
    # check_instruction("  addi r0 r1 100")
    # instruction_bin = encode(3, 5, 3, 4, 'i')
    # print(instruction_bin)
    # write_binary_file(instruction_bin)
    print("Testing to assemble")
    try:
        source = sys.argv[1]
        # print(source)
    except IndexError as error:
        print("No source file given. Please provide a source file to assemble.")
        # TODO : faire une fonction pour les usages du fichier et les options possibles.
        print("Usage:  ...in the work...")
        sys.exit(-1)
    try:
        destination = sys.argv[2]
    except IndexError:
        print("No output file given. Writing in the default file : bin/destination.bin\n")
        destination = "bin/destination.bin"
    Assembly(source, destination)
