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


def read_file(filename):
    """
    Lit le fichier et renvoit les lignes du fichier    
    """
    file = open(filename, 'r')
    the_lines = file.readlines()
    file.close()
    return the_lines


def assembling_file(the_lines):
    for line in the_lines:
        line.strip()
        # check which instruction is in the line
        instruction = check_instruction(line)
        # convert it to a binary code
        binary_instruction_list = encode_r(instruction)
        # store it into the output file
        write_binary_file(binary_instruction_list)


def check_instruction(line):
    """
    check which asm instruction is asked in the given line and return the corresponding encoding
    Example: can read instructions like "add r0, r1, r2"
    """
    # Définit les cas pour chaque instruction
    switch = {
        # "comment": ["\s*#.*$", 5],
        'add': {
            'regex': "^\s*(add)\s+r(\d+)\s+r(\d+)\s+r(\d+)$",
            'opcode': 2
        },
        'addi': {
            'regex': "^\s*(addi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)$",
            'opcode': 3
        },
        'sub': {
            'regex': "^\s*(sub)\s+r(\d+)\s+r(\d+)\s+r(\d+)$",
            'opcode': 4
        },
        'subi': {
            'regex': "^\s*(subi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)$",
            'opcode': 5
        },
        'mul': {
            'regex': "^\s*(mul)\s+r(\d+)\s+r(\d+)\s+r(\d+)$",
            'opcode': 6
        },
        'muli': {
            'regex': "^\s*(muli)\s+r(\d+)\s+r(\d+)\s+(-?\d+)$",
            'opcode': 7
        }
    }
    for case in switch.items():
        key,value=case
        expression_string = value['regex']
        expression = re.compile(expression_string)
        matching = expression.match(line)
        if matching:
            print(f"match with: {key} = {value['opcode']}")
            # print(f"print the group 1: {matching.group(1)}")
            # print(f"print the group 2: {matching.group(2)}")
            return [value['opcode'], matching.group(2), matching.group(3), matching.group(4)]
    print("no matching")
    return -1
    # Mettre une erreur pour le non matching (non ?)


def encode_r(opcode, rd, rs1, rs2):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    rd = rd << 21
    rs1 = rs1 << 16
    rs2 = rs2 << 11
    binary_instruction = opcode | rd | rs1 | rs2
    return binary_instruction


def encode_i(opcode, rd, rs, im):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    rd = rd << 21
    rs = rs << 16
    im = im & 0x0000ffff
    binary_instruction = opcode | rd | rs | im
    return binary_instruction


def encode_jr(opcode, rd, ra):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    rd = rd << 21
    ra = ra << 16
    binary_instruction = opcode | rd | ra
    return binary_instruction


def encode_ji(opcode, rd, addr):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    rd = rd << 21
    addr = addr & 0x000fffff
    binary_instruction = opcode | rd | addr
    return binary_instruction


def encode_b(opcode, rs, addr):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    rs = rs << 21
    addr = addr & 0x000fffff
    binary_instruction = opcode | rs | addr
    return binary_instruction


def encode_s(opcode, n):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    n = n & 0x03ffffff
    binary_instruction = opcode | n
    return binary_instruction


def encode_h(opcode):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode = opcode << 26
    binary_instruction = opcode
    return binary_instruction


def write_binary_file(binary_instruction_list: list):
    """
    Write the binary file for the given instruction
    """
    out_file = open("fichier.bin", "wb")
    for value in binary_instruction_list:
        out_file.write(struct.pack("<L", value))
    out_file.close()


if __name__ == "__main__":
    print("Testing the check function")
    check_instruction("  addi r0 r1 100")
    instruction_bin = [encode_r(2, 5, 3, 4)]
    print(instruction_bin)
    write_binary_file(instruction_bin)
