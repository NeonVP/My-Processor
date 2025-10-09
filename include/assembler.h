#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "FileRWUtils.h"
#include "errors.h"

struct Assembler_t {
    FileStat asm_file        = {};
    FileStat exe_file        = {};
    size_t   instruction_cnt = 0;
    int*     byte_code       = NULL;
    int      labels[10]      = {};
};

const size_t MAX_INSTRUCT_LEN = 10;

int AsmCodeToByteCode( Assembler_t* assembler );
int AsmCommandProcessing( char* instruction );
int RegNameProcessing( char* name );

void OutputInFile(Assembler_t* assembler );

#endif //ASSEMBLER_H