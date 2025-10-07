#include "calculator.h"

void StackAdd( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a + b );
}

void StackSub( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int b = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a - b );
}

void StackDiv( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int b   = StackTop( stk );
    StackPop( stk );
    int a = StackTop( stk );
    StackPop( stk );

    assert( b != 0 );

    StackPush( stk, a / b );
}

void StackMul( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    StackPop( stk );
    int b = StackTop( stk );
    StackPop( stk );

    StackPush( stk, a * b );
}

void StackPow( Stack_t* stk ) {
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

void StackSqrt( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int a = StackTop( stk );
    PRINT( "%d \n", a );
    StackPop( stk );
    StackPush( stk, ( int ) sqrt( a ) );
}

void StackIn( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    int number = 0;

    fprintf( stderr, "Input a number: " );
    scanf( "%d", &number );

    StackPush( stk, number );
}

void StackOut( Stack_t* stk ) {
    PRINT( "%s \n", __func__ )

    fprintf( stderr, "%d\n", StackTop( stk ) );
    StackPop( stk );
}

void StackPushR( Stack_t* stk, int* reg ) {
    StackPush( stk, *reg );
}

void StackPopR( Stack_t* stk, int* reg ) {
    *reg = StackTop( stk );
    StackPop( stk );
}