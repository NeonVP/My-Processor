#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "stack.h"

void StackAdd ( Stack_t* stk );
void StackSub ( Stack_t* stk );
void StackDiv ( Stack_t* stk );
void StackMult( Stack_t* stk );
void StackPow ( Stack_t* stk );
void StackSqrt( Stack_t* stk );

void StackOut ( Stack_t* stk );


#endif //CALCULATOR_H