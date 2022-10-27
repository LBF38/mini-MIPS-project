
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "vm.h"

u_int32_t memory[MEMORY_SIZE];
unsigned registers[NUM_REGS];

/* program counter */
int program_counter = 0;
/* instruction fields */
int instruction;
int opcode = 0;
int rd = 0;
int rs = 0;
int rs1 = 0;
int rs2 = 0;
int ra = 0;
int addr = 0;
int n = 0;
int immediate = 0;
/* the VM runs until this flag becomes 0 */
int running = 1;

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

/* display all registers as 4-digit hexadecimal words */
void show_registers()
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
    while (fread(&memory[i], 4, 1, inputFile))
    {
        // print_memory();
        i++;
    }
    // printf("i = %d\n",i);
}

void decode_r()
{
    rd = (instruction >> 21) & 0x1f;
    rs1 = (instruction >> 16) & 0x1f;
    rs2 = (instruction >> 11) & 0x1f;
}
void decode_i()
{
    rd = (instruction >> 21) & 0x1f;
    rs = (instruction >> 16) & 0x1f;
    immediate = instruction & 0xff;
}
void decode_jr()
{
    rd = (instruction >> 21) & 0x1f;
    ra = (instruction >> 16) & 0x1f;
}
void decode_ji()
{
    rd = (instruction >> 21) & 0x1f;
    addr = instruction & 0x1fffff;
}
void decode_b()
{
    rs = (instruction >> 21) & 0x1f;
    addr = instruction & 0x1fffff;
}
void decode_s()
{
    n = instruction & 0x3ffffff;
}

void op_add()
{
    decode_r();
    printf("add r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] + registers[rs2]);
}

void op_addi()
{
    decode_i();
    printf("add r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] + immediate);
}

void op_sub()
{
    decode_r();
    printf("sub r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] - registers[rs2]);
}
void op_subi()
{
    decode_i();
    printf("sub r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] - immediate);
}
void op_mul()
{
    decode_r();
    printf("mul r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] * registers[rs2]);
}
void op_muli()
{
    decode_i();
    printf("mul r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] * immediate);
}
void op_div()
{
    decode_r();
    printf("div r%d r%d r%d\n", rd, rs1, rs2);
    if (registers[rs2] == 0)
    {
        fprintf(stderr, "error input: division by zero\n");
        exit(-1);
    }
    write_registers(rd, registers[rs1] / registers[rs2]);
}
void op_divi()
{
    decode_i();
    printf("div r%d r%d %d\n", rd, rs, immediate);
    if (immediate == 0)
    {
        fprintf(stderr, "error input: division by zero\n");
        exit(-1);
    }
    write_registers(rd, registers[rs] / immediate);
}
void op_and()
{
    decode_r();
    printf("and r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] && registers[rs2]);
}
void op_andi()
{
    decode_i();
    printf("and r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] && immediate);
}
void op_or()
{
    decode_r();
    printf("or r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] || registers[rs2]);
}
void op_ori()
{
    decode_i();
    printf("or r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] || immediate);
}
void op_xor()
{
    decode_r();
    printf("xor r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] ^ registers[rs2]);
}
void op_xori()
{
    decode_i();
    printf("xor r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] ^ immediate);
}
void op_shl()
{
    decode_r();
    printf("shl r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] << registers[rs2]);
}
void op_shli()
{
    decode_i();
    printf("shl r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] << immediate);
}
void op_shr()
{
    decode_r();
    printf("shr r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] >> registers[rs2]);
}
void op_shri()
{
    decode_i();
    printf("shr r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] >> immediate);
}
void op_slt()
{
    decode_r();
    printf("slt r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] < registers[rs2]);
}
void op_slti()
{
    decode_i();
    printf("slt r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] < immediate);
}
void op_sle()
{
    decode_r();
    printf("sle r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] <= registers[rs2]);
}
void op_slei()
{
    decode_i();
    printf("sle r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] <= immediate);
}
void op_seq()
{
    decode_r();
    printf("seq r%d r%d r%d\n", rd, rs1, rs2);
    write_registers(rd, registers[rs1] == registers[rs2]);
}
void op_seqi()
{
    decode_i();
    printf("seq r%d r%d %d\n", rd, rs, immediate);
    write_registers(rd, registers[rs] == immediate);
}
void op_load()
{
    // A vérifier
    decode_i();
    printf("load r%d r%d %d\n", rd, rs, immediate);
    if (rs + immediate >= MEMORY_SIZE)
    {
        perror("Error load operator: indexError. Can't access in memory.\n");
        exit(-1);
    }
    write_registers(rd, memory[rs + immediate]);
}
void op_store()
{
    decode_i();
    printf("store r%d r%d %d\n", rd, rs, immediate);
    if (rs + immediate >= MEMORY_SIZE)
    {
        perror("Error store operator: indexError. Can't access in memory.\n");
        exit(-1);
    }
    memory[rs + immediate] = rd;
}
void op_jmpr()
{
    decode_jr();
    printf("jmp r%d r%d\n", rd, ra);
    write_registers(rd, program_counter);
    program_counter = ra - 1; // pour être à ra au prochain tour. (program_counter++ à la fin de op_jmpr dans run())
}
void op_jmpi()
{
    decode_ji();
    printf("jmp r%d %d\n", rd, addr);
    write_registers(rd, program_counter);
    program_counter = addr - 1;
}
void op_braz()
{
    decode_b();
    printf("braz r%d %d\n", rs, addr);
    if (rs == 0)
    {
        program_counter = addr - 1;
    }
}
void op_branz()
{
    decode_b();
    printf("branz r%d %d\n", rs, addr);
    if (rs != 0)
    {
        program_counter = addr - 1;
    }
}
void op_scall()
{
    // vérifier toutes les fonctionnalités de cette fonction.
    decode_s();
    printf("scall %d\n", n);
    int userInput;
    // int r20;
    switch (n)
    {
    case 0:
        scanf("Input a number: %d\n", &userInput);
        write_registers(registers[20], userInput);
        break;
    case 1:
        printf("%d\n", registers[20]);
        break;
    case 3:
        printf("%c\n", registers[20]);
        break;
    // case 4:
    //     // char *r20 = registers[20];
    //     printf("%s\n", registers[20]);
    //     break;
    default:
        break;
    }
}
void op_stop()
{
    printf("stop\n");
    running = 0;
}

/* evaluate the last decoded instruction */
void eval()
{
    switch (opcode)
    {
    case OPCODE_ADD:
        op_add();
        break;
    case OPCODE_ADDI:
        op_addi();
        break;
    case OPCODE_SUB:
        op_sub();
        break;
    case OPCODE_SUBI:
        op_subi();
        break;
    case OPCODE_MUL:
        op_mul();
        break;
    case OPCODE_MULI:
        op_muli();
        break;
    case OPCODE_DIV:
        op_div();
        break;
    case OPCODE_DIVI:
        op_divi();
        break;
    case OPCODE_AND:
        op_and();
        break;
    case OPCODE_ANDI:
        op_andi();
        break;
    case OPCODE_OR:
        op_or();
        break;
    case OPCODE_ORI:
        op_ori();
        break;
    case OPCODE_XOR:
        op_xor();
        break;
    case OPCODE_XORI:
        op_xori();
        break;
    case OPCODE_SHL:
        op_shl();
        break;
    case OPCODE_SHLI:
        op_shli();
        break;
    case OPCODE_SHR:
        op_shr();
        break;
    case OPCODE_SHRI:
        op_shri();
        break;
    case OPCODE_SLT:
        op_slt();
        break;
    case OPCODE_SLTI:
        op_slti();
        break;
    case OPCODE_SLE:
        op_sle();
        break;
    case OPCODE_SLEI:
        op_slei();
        break;
    case OPCODE_SEQ:
        op_seq();
        break;
    case OPCODE_SEQI:
        op_seqi();
        break;
    case OPCODE_LOAD:
        op_load();
        break;
    case OPCODE_STORE:
        op_store();
        break;
    case OPCODE_JMPR:
        op_jmpr();
        break;
    case OPCODE_JMPI:
        op_jmpi();
        break;
    case OPCODE_BRAZ:
        op_braz();
        break;
    case OPCODE_BRANZ:
        op_branz();
        break;
    case OPCODE_SCALL:
        op_scall();
        break;
    case OPCODE_STOP:
        op_stop();
        break;
    default:
        perror("ERROR: unknown opcode\n");
        printf("Opcode : %d\n", opcode);
        running = 0;
        break;
    }
}

void run()
{
    while (running)
    {
        show_registers();
        instruction = memory[program_counter];
        opcode = (instruction >> 26) & 0x3f;
        eval();
        program_counter++;
    }
    printf("END of program\n");
    show_registers();
}

int main(int argc, const char *argv[])
{
    // int i;
    // for (i = 0; i < argc; i++)
    // {
    //     printf("argv[%d] = \"%s\" \n", i, argv[i]);
    // }
    // read_file("bin/destination.bin");
    if (argc >= 2)
    {
        char *filename = (char *)malloc(100 * sizeof(char));
        strcpy(filename, argv[1]);
        read_file(filename);
        free(filename);
        run();
    }
    else
    {
        int i;
        for (i = 0; i < argc; i++)
        {
            printf("argv[%d] = \"%s\" \n", i, argv[i]);
        }
    }

    return EXIT_SUCCESS;
}