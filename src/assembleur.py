# Ici, on définit les règles pour convertir les commandes assembleur en binaire.
# Utilisation de Regex pour vérifier les syntaxes par exemple.
# Lecture de fichiers, vérification des expressions, convertir en binaire selon règles binaires.

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


def search_in_file(the_lines):
    for line in the_lines:
        line.strip()
        # check which instruction is in the line
        instruction = check_instruction(line)
        # convert it to a binary code
        convert_to_binary(instruction)
        # store it into the output file


def check_instruction(line):
    """
    check which asm instruction is asked in the given line and return the corresponding encoding
    Example: can read instructions like "add r0, r1, r2"
    """
    # Définit les cas pour chaque instruction
    switch = {
        "comment": ["\s*#.*$", 5],
        'add': ["^\s*(add)\s+r(\d+)\s+r(\d+)\s+r(\d+)$", 1],
        'addi': ["^\s*(addi)\s+r(\d+)\s+r(\d+)\s+(-?\d+)$", 2],
    }
    for value in switch.values():
        expression_string = value[0]
        expression = re.compile(expression_string)
        matching = expression.match(line)
        if matching:
            print(f"match with: {value[1]}")
            # print(f"print the group 1: {matching.group(1)}")
            # print(f"print the group 2: {matching.group(2)}")
            return [value[1], matching.group(2), matching.group(3), matching.group(4)]
    print("no matching")
    return -1
    # Mettre une erreur pour le non matching (non ?)


def convert_to_binary(instruction: list):
    """
    Convert the recognized instruction into a binary instruction
    """
    opcode, rd, rs, im = instruction
    opcode = opcode << 26
    rd = rd << 21
    rs = rs << 16
    im = im & 0x0000ffff
    binary_instruction = opcode | rd | rs | im
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
    check_instruction("  add r0 r1 100")
    instruction_bin = [convert_to_binary([1, 0, 1, 2])]
    write_binary_file(instruction_bin)
