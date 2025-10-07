#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "FileRWUtils.h"
#include "errors.h"

const size_t MAX_CMD_LEN = 10;

struct Assembler_t {
    FileStat asm_file          = {};
    FileStat exe_file          = {};
    size_t   instruction_cnt   = 0;
    int      byte_code[ SIZE ] = {};           // TODO: make expandable
};

int AsmFileProcessing( Assembler_t* assembler );
int AsmCodeProcessing( char* instruction );
int RegNameProcessing( char* name );

void OutputInFile(Assembler_t* assembler );

#endif //ASSEMBLER_H