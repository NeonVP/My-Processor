#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h>
#include <math.h>

struct StrPar{
    const char* ptr = NULL;
    size_t len = 0;
};

enum ASM_CMD {
    PUSH_CMD  = 1,
    POP_CMD   = 2,
    ADD_CMD   = 3,
    SUB_CMD   = 4,
    MUL_CMD   = 5,
    DIV_CMD   = 6,
    POW_CMD   = 7,
    SQRT_CMD  = 8,
    IN_CMD    = 9,
    OUT_CMD   = 10,
    JMP_CMD   = 11,
    JB_CMD    = 12,
    JA_CMD    = 13,
    JBE_CMD   = 14,
    JAE_CMD   = 15,
    JE_CMD    = 16,
    HLT_CMD   = 17,
    PUSHR_CMD = 33,
    POPR_CMD  = 34
};

const size_t SIZE = 128;

// struct AsmCommand_t{
//     int cmd_number = 0;

// };

#endif