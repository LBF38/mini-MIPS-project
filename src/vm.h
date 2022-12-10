/**
 * @brief Structure de la VM 
 * On définit ici les fonctions de base de la VM
 * @author Mathis URIEN
 * @version 1.0
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MEMORY_SIZE 2048
#define NUM_REGS 32

#define OPCODE_ADD 2
#define OPCODE_ADDI 3
#define OPCODE_SUB 4
#define OPCODE_SUBI 5
#define OPCODE_MUL 6
#define OPCODE_MULI 7
#define OPCODE_DIV 8
#define OPCODE_DIVI 9
#define OPCODE_AND 10
#define OPCODE_ANDI 11
#define OPCODE_OR 12
#define OPCODE_ORI 13
#define OPCODE_XOR 14
#define OPCODE_XORI 15
#define OPCODE_SHL 16
#define OPCODE_SHLI 17
#define OPCODE_SHR 18
#define OPCODE_SHRI 19
#define OPCODE_SLT 20
#define OPCODE_SLTI 21
#define OPCODE_SLE 22
#define OPCODE_SLEI 23
#define OPCODE_SEQ 24
#define OPCODE_SEQI 25
#define OPCODE_LOAD 27
#define OPCODE_STORE 29
#define OPCODE_JMPR 30
#define OPCODE_JMPI 31
#define OPCODE_BRAZ 32
#define OPCODE_BRANZ 33
#define OPCODE_SCALL 34
#define OPCODE_STOP 35

/**
 * @brief affiche le contenu de la mémoire
 *  
 */
void print_memory();

/**
 * @brief affiche le contenu des registres
 * 
 */
void show_registers();

/**
 * @brief écrit dans un registre
 * 
 * @param address 
 * @param value 
 */
void write_registers(int address, int value);

/**
 * @brief lit le fichier d'instruction
 * 
 * @param filename 
 */
void read_file(char *filename);

/**
 * @brief decode l'instruction de type r
 * 
 */
void decode_r();

/**
 * @brief decode l'instruction de type i
 * 
 */
void decode_i();

/**
 * @brief decode l'instruction de type j
 * 
 */
void decode_j();

/**
 * @brief decode l'instruction de type jr
 * 
 */
void decode_jr();

/**
 * @brief decode l'instruction de type jmpi
 * 
 */
void decode_ji();

/**
 * @brief decode l'instruction de type bra
 * 
 */
void decode_b();

/**
 * @brief decode l'instruction de type scall
 * 
 */
void decode_s();

/**
 * @brief instruction add
 * avec des registres
 */
void op_add();

/**
 * @brief instruction add
 * avec un registre et une constante
 */
void op_addi();

/**
 * @brief instruction sub
 * avec des registres
 */
void op_sub();

/**
 * @brief instruction sub
 * avec un registre et une constante
 */
void op_subi();

/**
 * @brief instruction mul
 * avec des registres
 */
void op_mul();

/**
 * @brief instruction mul
 * avec un registre et une constante
 */
void op_muli();

/**
 * @brief instruction div
 * avec des registres
 */
void op_div();

/**
 * @brief instruction div
 * avec un registre et une constante
 */
void op_divi();

/**
 * @brief instruction and
 * avec des registres
 */
void op_and();

/**
 * @brief instruction and
 * avec un registre et une constante
 */
void op_andi();

/**
 * @brief instruction or
 * avec des registres
 */
void op_or();

/**
 * @brief instruction or
 * avec un registre et une constante
 */
void op_ori();

/**
 * @brief instruction xor
 * avec des registres
 */
void op_xor();

/**
 * @brief instruction xor
 * avec un registre et une constante
 */
void op_xori();

/**
 * @brief instruction shl
 * avec des registres
 */
void op_shl();

/**
 * @brief instruction shl
 * avec un registre et une constante
 */
void op_shli();

/**
 * @brief instruction shr
 * avec des registres
 */
void op_shr();

/**
 * @brief instruction shr
 * avec un registre et une constante
 */
void op_shri();

/**
 * @brief instruction slt
 * avec des registres
 */
void op_slt();

/**
 * @brief instruction slt
 * avec un registre et une constante
 */
void op_slti();

/**
 * @brief instruction sle
 * avec des registres
 */
void op_sle();

/**
 * @brief instruction sle
 * avec un registre et une constante
 */
void op_slei();

/**
 * @brief instruction seq
 * avec des registres
 */
void op_seq();

/**
 * @brief instruction seq
 * avec un registre et une constante
 */
void op_seqi();

/**
 * @brief instruction load
 * 
 */
void op_load();

/**
 * @brief instruction store
 * 
 */
void op_store();

/**
 * @brief instruction jmp
 * 
 */
void op_jmpr();

/**
 * @brief instruction jmpi
 * 
 */
void op_jmpi();

/**
 * @brief instruction braz
 * 
 */
void op_braz();

/**
 * @brief instruction branz
 * 
 */
void op_branz();

/**
 * @brief instruction scall
 * 
 */
void op_scall();

/**
 * @brief instruction stop
 * 
 */
void op_stop();

/**
 * @brief evaluation des instructions
 * 
 */
void eval();

/**
 * @brief fonction principale de l'assembleur
 * 
 */
void run();

/**
 * @brief lance l'assembleur
 * 
 */
int main(int argc, const char *argv[]);

