#include "processor.h"


void ProcPush( Processor_t* processor) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    StackPush( &( processor->stk ), processor->byte_code[ processor->instruction_ptr++ ] );
}

void ProcPop( Processor_t* processor) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    StackPop( &( processor->stk ) );
}

void ProcAdd( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int a = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int b = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );

    StackPush( &( processor->stk ), a + b );
}

void ProcSub( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int b = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int a = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );

    StackPush( &( processor->stk ), a - b );
}

void ProcMul( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int a = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int b = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );

    StackPush( &( processor->stk ), a * b );
}

void ProcDiv( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int b   = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int a = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );

    assert( b != 0 );

    StackPush( &( processor->stk ), a / b );
}

void ProcPow( Processor_t* processor ) {  // FIXME: i don't work
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int indicator = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int base      = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int result    = 1;

    for ( int i = 1; i < indicator; i++ ) {
        result *= base;
    }

    StackPush( &( processor->stk ), result );
}

void ProcSqrt( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int a = StackTop( &( processor->stk ) );
    PRINT( "%d \n", a );
    StackPop( &( processor->stk ) );
    StackPush( &( processor->stk ), ( int ) sqrt( a ) );
}

void ProcIn( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    ProcDump( processor, 0 );
    int number = 0;

    fprintf( stderr, "Input a number: " );
    scanf( "%d", &number );

    StackPush( &( processor->stk ), number );
    StackDump( &( processor->stk ) );
}

void ProcOut( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    ProcDump( processor, 0 );
    int n = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );

    fprintf( stderr, "Output: %d \n", n );
}

void ProcPushR( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    StackPush( &( processor->stk ), processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] );
}

void ProcPopR( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
}

void ProcJump( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int command = processor->byte_code[ processor->instruction_ptr - 1 ];
    size_t index = ( size_t ) processor->byte_code[ processor->instruction_ptr++ ];

    if ( command == JMP_CMD ) {
        processor->instruction_ptr = index;
        return;
    }

    int b = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int a = StackTop( &( processor->stk ) );

    if ( command == JB_CMD && a < b ) {
        processor->instruction_ptr = index;
    }
    else if ( command == JA_CMD && a > b) {
        processor->instruction_ptr = index;
    }
    else if ( command == JBE_CMD && a <= b) {
        processor->instruction_ptr = index;
    }
    else if ( command == JAE_CMD && a >= b) {
        processor->instruction_ptr = index;
    }
    else if ( a == b ) {
        processor->instruction_ptr = index;
    }
}

void ProcCall( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    StackPush( &( processor->refund_stk ), ( int ) ( processor->instruction_ptr + 1 ) );

    processor->instruction_ptr = ( size_t ) processor->byte_code[ processor->instruction_ptr ];
}

void ProcRet( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    processor->instruction_ptr = ( size_t ) StackTop( &( processor->refund_stk ) );
    StackPop( &( processor->refund_stk ) );
}