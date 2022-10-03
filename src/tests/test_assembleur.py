

# Imports
import sys
import os

sys.path.insert(0, os.path.join(os.getcwd(),"src"))
import unittest
import assembleur as asm

class TestAssembleur(unittest.TestCase):
    def setUp(self):
        self.add_instruction="add r0 r1 100"
    
    def testCheckInstruction(self):
        """
        Teste la partie vérification d'une instruction
        """
        self.assertEqual(asm.check_instruction(self.add_instruction),1)











