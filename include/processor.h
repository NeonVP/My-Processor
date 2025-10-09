#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <ctype.h>

#include "FileRWUtils.h"
#include "commands.h"

#ifdef _DEBUG
#define CHECK_STK_IN_DEBUG(...)                                    \
    __VA_ARGS__                                                    \
    ON_DEBUG( StackDump( &( processor->stk ) ); PRINT( "\n\n" ) )
#else
#define CHECK_STK_IN_DEBUG(...) __VA_ARGS__
#endif // _DEBUG


struct Processor_t {
    Stack_t stk    = {};
    int* byte_code = NULL;
    size_t instruction_ptr = 0;
    StackData_t regs[8] = {};       // magic number
};

void ProcCtor( Processor_t* processor, size_t size );
void ProcDtor( Processor_t* processor );

void ExeFileToByteCode ( Processor_t* processor, FileStat* file );
int  ByteCodeProcessing( Processor_t* processor );

void ProcJump( Processor_t* processor );

#endif // PROCESSOR_H