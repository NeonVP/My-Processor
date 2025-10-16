#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <ctype.h>

#include "FileRWUtils.h"
#include "stack.h"

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


void ProcPush( Processor_t* processor);
void ProcPop( Processor_t* processor);

void ProcAdd ( Processor_t* processor );
void ProcSub ( Processor_t* processor );
void ProcDiv ( Processor_t* processor );
void ProcMul ( Processor_t* processor );
void ProcPow ( Processor_t* processor );
void ProcSqrt( Processor_t* processor );

void ProcIn ( Processor_t* processor );
void ProcOut( Processor_t* processor );

void ProcPushR( Processor_t* processor );
void ProcPopR ( Processor_t* processor );

void ProcJump( Processor_t* processor );


#endif // PROCESSOR_H