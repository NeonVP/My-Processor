#include "commands.h"


void ProcAdd( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a + b );
}

void ProcSub( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int b = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a - b );
}

void ProcDiv( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int b   = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    assert( b != 0 );

    StackPush( stk, a / b );
}

void ProcMul( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a * b );
}

void ProcPow( Stack_t* stk ) {  // FIXME: i don't work
    PRINT( "%s \n", __func__ )

    int indicator = StackTop( stk );
    StackPop( stk );
    int base      = StackTop( stk );
    StackPop( stk );
    int result    = 1;

    for ( int i = 1; i < indicator; i++ ) {
        result *= base;
    }

    StackPush( stk, result );
}

void ProcSqrt( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    PRINT( "%d \n", a );
    StackPop( stk );
    StackPush( stk, ( int ) sqrt( a ) );
}

void ProcIn( Stack_t* stk ) {           // FIXME: i don't work
    PRINT( "%s \n", __func__ )

    int number = 0;

    fprintf( stderr, "Input a number: " );
    scanf( "%d", &number );

    StackPush( stk, number );
}

void ProcOut( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int n = StackTop( stk );
    StackPop( stk );

    fprintf( stderr, "Output: %d \n", n );
}

void ProcPushR( Stack_t* stk, int* reg ) {
    StackPush( stk, *reg );
}

void ProcPopR( Stack_t* stk, int* reg ) {
    *reg = StackTop( stk );
    StackPop( stk );
}
