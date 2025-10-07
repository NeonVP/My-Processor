#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "FileRWUtils.h"
#include "errors.h"

const size_t SIZE = 128;
const size_t MAX_CMD_LEN = 10;

struct Assembler_t {
    FileStat asm_file         = {};
    FileStat exe_file        = {};
    int      byte_codes[ SIZE ] = {};           // magic number + make expandable
    size_t   instruction_cnt    = 0;
};

void AsmCtor( int argc, char** argv, struct Assembler_t* assembler );
int AsmFileProcessing( Assembler_t* assembler );
int AsmCodeProcessing( char* instruction );
void OutputInFile(Assembler_t* assembler );

#endif //ASSEMBLER_H