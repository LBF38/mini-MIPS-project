
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "vm.h"

u_int32_t memory[MEMORY_SIZE];
// u_int32_t PC = 0; // program counter
// u_int32_t IR;     // instruction register

unsigned registers[NUM_REGS];

/* program counter */
int pc = 0;
/* instruction fields */
int instruction;
int opcode = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;

void print_memory()
{
    printf("Memory content:\n");
    int j = 0;
    while (j < MEMORY_SIZE && memory[j] != 0)
    {
        for (int i = 0; i < 5; i++)
        {
            printf("%08X ", memory[j++]);
        }
        printf("\n");
    }
    printf("END Memory\n");
}

void read_file(char *filename)
{
    printf("This is the read_file function. We read a binary file.\n");
    FILE *inputFile = fopen(filename, "rb");
    // Gestion erreur ouverture fichier
    if (inputFile == NULL)
    {
        perror("==vm.c== Error opening file");
        exit(-1);
    }
    int i = 0;
    while (fread(&memory[i], 1, 32, inputFile))
    {
        print_memory();
        i++;
    }
}

/* decode a word */
void decode_i(int instruction)
{
    opcode = (instruction & 0xF000) >> 12;
    reg1 = (instruction & 0xF00) >> 8;
    reg2 = (instruction & 0xF0) >> 4;
    reg3 = (instruction & 0xF);
    imm = (instruction & 0xFF);
}

void add()
{
    int rd = (instruction >> 21) & 0x1f;
    int rs1 = (instruction >> 16) & 0x1f;
    int rs2 = (instruction >> 11) & 0x1f;
    printf("add r%d r%d r%d\n", rd, rs1, rs2);
}

void addi()
{
    int rd = (instruction >> 21) & 0x1f;
    int rs = (instruction >> 16) & 0x1f;
    int immediate = (instruction & 0xFF);
    printf("add r%d r%d %d\n", rd, rs, immediate);
}

/* the VM runs until this flag becomes 0 */
int running = 1;

/* evaluate the last decoded instruction */
void eval()
{
    switch (opcode)
    {
    case OPCODE_STOP:
        printf("Stop\n");
        running = 0;
        break;
    case OPCODE_LOAD:
        printf("load r%d #%d\n", reg1, imm);
        registers[reg1] = imm;
        break;
    case OPCODE_ADD:
        add();
        // printf("add r%d r%d r%d\n", reg1, reg2, reg3);
        // registers[reg1] = registers[reg2] + registers[reg3];
        break;
    case OPCODE_ADDI:
        addi();
        break;
    case OPCODE_SUB:
        printf("sub r%d r%d r%d\n", reg1, reg2, reg3);
        registers[reg1] = registers[reg2] - registers[reg3];
        break;
    case OPCODE_MUL:
        printf("mult r%d r%d r%d\n", reg1, reg2, reg3);
        registers[reg1] = registers[reg2] * registers[reg3];
        break;
    case OPCODE_DIV:
        printf("div r%d r%d r%d\n", reg1, reg2, reg3);
        if (registers[reg3] == 0)
        {
            fprintf(stderr, "error input: division by zero\n");
            exit(-1);
        }
        registers[reg1] = registers[reg2] / registers[reg3];
        break;
    case OPCODE_AND:
        printf("and r%d r%d r%d\n", reg1, reg2, reg3);
        registers[reg1] = registers[reg2] && registers[reg3];
        break;
    case OPCODE_OR:
        printf("or r%d r%d r%d\n", reg1, reg2, reg3);
        registers[reg1] = registers[reg2] || registers[reg3];
        break;
    case OPCODE_XOR:
        printf("xor r%d r%d r%d\n", reg1, reg2, reg3);
        registers[reg1] = registers[reg2] ^ registers[reg3];
        break;
    default:
        perror("ERROR: unknown opcode\n");
        printf("Opcode : %d\n",opcode);
        running = 0;
        break;
    }
}

/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
    int i;
    printf("registers = ");
    for (i = 0; i < NUM_REGS; i++)
        printf("%04X ", registers[i]);
    printf("\n");
}

void write_registers(int index, int value)
{
    if (index == 0)
    {
        value = 0;
    }
    registers[index] = value;
}

void run()
{
    while (running)
    {
        showRegs();
        instruction = memory[pc];
        opcode = (instruction >> 26) & 0x3f;
        eval();
        pc++;
    }
    showRegs();
}

int main(int argc, const char *argv[])
{
    // run();
    // int i;
    // for (i = 0; i < argc; i++)
    // {
    //     printf("argv[%d] = \"%s\" \n", i, argv[i]);
    // }
    // read_file("bin/destination.bin");
    char *filename = "bin/file.bin";
    read_file(filename);
    run();

    return EXIT_SUCCESS;
}