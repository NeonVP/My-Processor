#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "stack.h"

void ProcAdd ( Stack_t* stk );
void ProcSub ( Stack_t* stk );
void ProcDiv ( Stack_t* stk );
void ProcMul ( Stack_t* stk );
void ProcPow ( Stack_t* stk );
void ProcSqrt( Stack_t* stk );

void ProcIn ( Stack_t* stk );
void ProcOut( Stack_t* stk );

void ProcPushR( Stack_t* stk, int* reg );
void ProcPopR ( Stack_t* stk, int* reg );

#endif // CALCULATOR_H