

# Imports
import unittest
import sys
import os
sys.path.insert(0, os.path.join(os.getcwd(), "src"))
import assembleur as asm


class TestAssembleur(unittest.TestCase):
    def setUp(self):
        self.addi_instruction = "add r0 r1 100"
        self.commented_line = "# this is a commented line"
        self.add_instruction_with_comment = "add r0 r1 100 #this is a comment"
        self.writefile()
        # self.the_lines = asm.Assembly().read_file("testfile.txt")

    def writefile(self):
        f = open(os.path.join("src", "tests", "testfile.txt"), "w")
        f.write(self.addi_instruction+"\n")
        f.write(self.commented_line+"\n")
        f.write(self.add_instruction_with_comment+"\n")
        f.close()

    # def testCheckInstruction(self):
    #     """
    #     Teste la partie vérification d'une instruction
    #     """
    #     self.assertEqual(asm.check_instruction(self.addi_instruction), 1)

    def testAssembling(self):
        """
        Teste l'assemblage d'un fichier
        """
        asm.Assembly(os.getcwd() + "/src/tests/testfile.txt", "bin/testfile.bin")
        self.assertTrue(os.path.isfile("bin/testfile.bin"))

    # def testReadFile(self):
    #     """
    #     Teste la lecture de fichiers
    #     """
    #     self.assertIsInstance(asm.read_file(os.path.join("tests","testfile.txt")),list)

    # def testSearchInLine(self):
    #     """
    #     Teste la fonction search_in_line
    #     """
    #     self.assertEqual(asm.search_in_file(self.the_lines))


if __name__ == "__main__":
    unittest.main()
