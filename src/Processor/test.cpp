#include "stack.h"

int main() {
    Stack_t stack = {};
    StackCtor( &stack, 10 );

    StackPush( &stack, 10 );
    StackPush( &stack, 20 );
    StackPush( &stack, 30 );
    printf( "%d \n", StackTop( &stack ) );

    StackPop( &stack );
    StackDump( &stack );
    

    StackDtor( &stack );
}