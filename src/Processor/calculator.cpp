#include "calculator.h"

void StackAdd( Stack_t* stk ) {
    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a + b );
}

void StackSub( Stack_t* stk ) {
    int b = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a - b );
}

void StackDiv( Stack_t* stk ) {
    int b   = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    assert( b != 0 );

    StackPush( stk, a / b );
}

void StackMult( Stack_t* stk ) {
    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a * b );
}

void StackPow( Stack_t* stk ) {
    int indicator = StackTop( stk );
    StackPop( stk );
    int base      = StackTop( stk );
    StackPop( stk );
    int result    = 1;

    for ( size_t i = 1; i < indicator; i++ ) {
        result *= base;
    }

    StackPush( stk, result );
}

void StackSqrt( Stack_t* stk ) {
    int a = StackTop( stk );
    StackPop( stk );
    StackPush( stk, ( int ) sqrt( a ) );
}

void StackOut( Stack_t* stk ) {
    fprintf( stderr, "%d\n", StackTop( stk ) );
    StackPop( stk );
}