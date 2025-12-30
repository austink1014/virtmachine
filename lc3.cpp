#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

// memory
#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

// REGISTERS
enum
{
    R_R0=0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, // program counter
    R_COND, // condition flag
    R_COUNT,
};
uint16_t reg[R_COUNT];

// OPCODES
// LC-3 only has a couple instructions compared to x86.
enum
{
    OP_BR = 0,  // branch
    OP_ADD,     // addition
    OP_LD,      // load
    OP_ST,      // store
    OP_AND,     // bitwise and
    OP_NOT,     // bitwise not
    OP_JSR,     // jump register
    OP_LDR,     // load register
    OP_STR,     // store register
    OP_RTI,     // return from interrupt, unused
    OP_LDI,     // load, indirect
    OP_JMP,     // jump
    OP_RES,     // reserved, unused
    OP_LEA,     // load effective address
    OP_TRAP     // execute trap
};

// CONDITION FLAGS
enum
{
    FL_POS = 1 << 0,    // P, Positive condition
    FL_ZRO = 1 << 1,    // Z, Zero condition
    FL_NEG = 1 << 2,    // N, Negative condition
};