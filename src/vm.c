#include "vm.h"

u_int32_t memory[MEMORY_SIZE];
int registers[NUM_REGS];

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
u_int32_t immediate = 0;
/* the VM runs until this flag becomes 0 */
int running = 1;

/* Debug flag */
int debug = 0;

void print_memory()
{
    printf("Memory content:\n");
    int j = 0;
    while (j < MEMORY_SIZE && memory[j] != 0)
    {
        for (int i = 0; i < 15; i++)
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
        printf("r%d = %04X ", i, registers[i]);
    printf("\n");
}

void write_registers(int address, int value)
{
    if (address == 0)
    {
        value = 0;
    }
    registers[address] = value;
}

void read_file(char *filename)
{
    printf(GREEN "This is the read_file function. We read a binary file.\n" RESET);
    FILE *inputFile = fopen(filename, "rb");
    // Gestion erreur ouverture fichier
    if (inputFile == NULL)
    {
        perror(RED "==vm.c== Error opening file" RESET);
        exit(-1);
    }
    int i = 0;
    while (fread(&memory[i], 4, 1, inputFile))
    {
        i++;
    }
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
    immediate = instruction & 0x0000ffff;

    if ((immediate & 0x00008000) != 0)
    {
        immediate |= 0xffff0000;
    }
    if (debug)
        printf(YELLOW "%08X\n" RESET, immediate);
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
    if (debug)
        printf(YELLOW "add r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] + registers[rs2]);
}

void op_addi()
{
    decode_i();
    if (debug)
        printf(YELLOW "add r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] + immediate);
}

void op_sub()
{
    decode_r();
    if (debug)
        printf(YELLOW "sub r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] - registers[rs2]);
}
void op_subi()
{
    decode_i();
    if (debug)
        printf(YELLOW "sub r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] - immediate);
}
void op_mul()
{
    decode_r();
    if (debug)
        printf(YELLOW "mul r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] * registers[rs2]);
}
void op_muli()
{
    decode_i();
    if (debug)
        printf(YELLOW "mul r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] * immediate);
}
void op_div()
{
    decode_r();
    if (debug)
        printf(YELLOW "div r%d r%d r%d\n" RESET, rd, rs1, rs2);
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
    if (debug)
        printf(YELLOW "div r%d r%d %d\n" RESET, rd, rs, immediate);
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
    if (debug)
        printf(YELLOW "and r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] && registers[rs2]);
}
void op_andi()
{
    decode_i();
    if (debug)
        printf(YELLOW "and r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] && immediate);
}
void op_or()
{
    decode_r();
    if (debug)
        printf(YELLOW "or r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] || registers[rs2]);
}
void op_ori()
{
    decode_i();
    if (debug)
        printf(YELLOW "or r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] || immediate);
}
void op_xor()
{
    decode_r();
    if (debug)
        printf(YELLOW "xor r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] ^ registers[rs2]);
}
void op_xori()
{
    decode_i();
    if (debug)
        printf(YELLOW "xor r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] ^ immediate);
}
void op_shl()
{
    decode_r();
    if (debug)
        printf(YELLOW "shl r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] << registers[rs2]);
}
void op_shli()
{
    decode_i();
    if (debug)
        printf(YELLOW "shl r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] << immediate);
}
void op_shr()
{
    decode_r();
    if (debug)
        printf(YELLOW "shr r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] >> registers[rs2]);
}
void op_shri()
{
    decode_i();
    if (debug)
        printf(YELLOW "shr r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] >> immediate);
}
void op_slt()
{
    decode_r();
    if (debug)
        printf(YELLOW "slt r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] < registers[rs2]);
}
void op_slti()
{
    decode_i();
    if (debug)
        printf(YELLOW "slt r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] < immediate);
}
void op_sle()
{
    decode_r();
    if (debug)
        printf(YELLOW "sle r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] <= registers[rs2]);
}
void op_slei()
{
    decode_i();
    if (debug)
        printf(YELLOW "sle r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] <= immediate);
}
void op_seq()
{
    decode_r();
    if (debug)
        printf(YELLOW "seq r%d r%d r%d\n" RESET, rd, rs1, rs2);
    write_registers(rd, registers[rs1] == registers[rs2]);
}
void op_seqi()
{
    decode_i();
    if (debug)
        printf(YELLOW "seq r%d r%d %d\n" RESET, rd, rs, immediate);
    write_registers(rd, registers[rs] == immediate);
}
void op_load()
{
    // A vérifier
    decode_i();
    if (debug)
        printf(YELLOW "load r%d r%d %d\n" RESET, rd, rs, immediate);
    if (rs + immediate >= MEMORY_SIZE)
    {
        fprintf(stderr, "Error load operator: indexError. Can't access in memory. (rs=%d, imm=%d)\n", rs, immediate);
        exit(-1);
    }
    write_registers(rd, memory[registers[rs] + immediate]);
}
void op_store()
{
    decode_i();
    if (debug)
        printf(YELLOW "store r%d r%d %d\n" RESET, rd, rs, immediate);
    if ((rs + immediate >= MEMORY_SIZE) && (rs + immediate <= 0))
    {
        fprintf(stderr, "Error store operator: indexError. Can't access in memory. (rs=%d, imm=%d)\n", rs, immediate);
        exit(-1);
    }
    memory[registers[rs] + immediate] = registers[rd]; // valeur du registre à stocker !!
}
void op_jmpr()
{
    decode_jr();
    if (debug)
        printf(YELLOW "jmp r%d r%d\n" RESET, rd, ra);
    write_registers(rd, program_counter);
    program_counter = registers[ra];
}
void op_jmpi()
{
    decode_ji();
    if (debug)
        printf(YELLOW "jmp r%d %d\n" RESET, rd, addr);
    write_registers(rd, program_counter);
    program_counter = addr;
}
void op_braz()
{
    decode_b();
    if (debug)
        printf(YELLOW "braz r%d %d\n" RESET, rs, addr);
    if (registers[rs] == 0)
    {
        if (debug)
            printf(YELLOW "rs == 0\n" RESET);
        program_counter = addr;
    }
}
void op_branz()
{
    decode_b();
    if (debug)
        printf(YELLOW "branz r%d %d\n" RESET, rs, addr);
    if (registers[rs] != 0)
    {
        if (debug)
            printf(YELLOW "rs != 0\n" RESET);
        program_counter = addr;
    }
}
void op_scall()
{
    // vérifier toutes les fonctionnalités de cette fonction.
    decode_s();
    if (debug)
        printf(YELLOW "scall %d\n" RESET, n);
    int userInput;
    switch (n)
    {
    case 0:
        printf("Input a number: ");
        scanf("%d", &userInput);
        write_registers(20, userInput);
        break;
    case 1:
        printf("%d\n", registers[20]);
        break;
    case 3:
        printf("%c\n", registers[20] & 0x7f);
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
    if (debug)
        printf(YELLOW "stop\n" RESET);
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
        perror(RED "ERROR: unknown opcode\n");
        printf("opcode : %d\n" RESET, opcode);
        running = 0;
        break;
    }
}

void run()
{
    while (running)
    {
        // show_registers();
        instruction = memory[program_counter++];
        opcode = (instruction >> 26) & 0x3f;
        eval();
    }
    printf(GREEN "END of program\n" RESET);
    // show_registers();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            debug = 1;
        }
    }
    char *filename = (char *)malloc(100 * sizeof(char));
    strcpy(filename, argv[1]);
    read_file(filename);
    free(filename);
    // print_memory();
    run();
    // print_memory();
    // printf("memory[10] = %d\n",memory[10]);

    return EXIT_SUCCESS;
}