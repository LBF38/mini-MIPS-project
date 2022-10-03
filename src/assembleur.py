## Ici, on définit les règles pour convertir les commandes assembleur en binaire.
# Utilisation de Regex pour vérifier les syntaxes par exemple.
# Lecture de fichiers, vérification des expressions, convertir en binaire selon règles binaires.

# Imports
import re


def read_file(filename):
    """
    Lit le fichier et renvoit les lignes du fichier    
    """
    file=open(filename, 'r')
    the_lines=file.readlines()
    file.close()
    return the_lines

def search_in_file(the_lines):
    for line in the_lines:
        line.strip()
        # check which instruction is in the line
        check_instruction(line)
        # convert it to a binary code
        # store it into the output file

def check_instruction(line):
    """
    check which asm instruction is asked in the given line and return the corresponding encoding
    Example: can read instructions like "add r0, r1, r2"
    """
    switch={
        "comment":["\s*#.*$",5],
        'addi':["^\s*(add)\s+r(\d+)\s+r(\d+)\s+(-?\d+)$",1],
    } # Définit les cas pour chaque instruction
    for value in switch.values():
        expression_string=value[0]
        expression=re.compile(expression_string)
        matching=expression.match(line)
        if matching:
            print(f"match with: {value[1]}")
            print(f"print the group 1: {matching.group(1)}")
            print(f"print the group 2: {matching.group(2)}")
            return value[1]
    print("no matching")
    return -1
    # Mettre une erreur pour le non matching (non ?)

if __name__=="__main__":
    print("Testing the check function")
    check_instruction("  add r0 r1 100")



    
























