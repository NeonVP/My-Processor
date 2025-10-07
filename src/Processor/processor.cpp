// FIXME: разнести файлы, архитектуру

#include "processor.h"

int main( int argc, char** argv ) {
    FileStat exe_file = {};
    ArgvProcessing( argc, argv, &exe_file );

    Processor_t processor = {};
    ProcCtor( &processor, 20 );

    ExeFileToByteCode( &processor, &exe_file );

    int result = ByteCodeProcessing( &processor );

    ProcDtor( &processor );

    if ( result == 1 ) {
        return 1;
    }
    else {
        return 0;
    }
}

void ProcCtor( Processor_t* processor, size_t size ) {
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )

    StackCtor( &( processor->stk ), size );
    processor->byte_code = ( int* ) calloc ( SIZE, sizeof( *processor->byte_code ) );
}

void ProcDtor( Processor_t* processor ) {
    StackDtor( &( processor->stk ) );
    // free( processor->byte_code );
    processor->byte_code = 0;
}

void ExeFileToByteCode( Processor_t* processor, FileStat* file ) {       // TODO: rename
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )
    my_assert( file      != NULL, ASSERT_ERR_NULL_PTR )

    PRINT( "In %s \n", __func__ )

    file->size = DetermineFileSize( file->address );

    char* buffer = ReadToBuffer( file );
    PRINT( "%s \n", buffer )
    char* old_buffer_ptr = buffer;

    int n = 0;
    sscanf( buffer, "%lu%n", &( processor->instruction_ptr ), &n );
    buffer += n;

    size_t counter = 0;
    int num = 0;
    while ( sscanf( buffer, "%d%n", &num, &n ) == 1 ) {
        processor->byte_code[ counter++ ] = num;
        buffer += n;
        PRINT( "%d ", num )
    }
    fprintf( stderr, "\n" );

    free( old_buffer_ptr );      // FIXME: save old address to buffer

    PRINT( "Out %s \n", __func__ )
}

int ByteCodeProcessing( Processor_t* processor ) {
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )

    PRINT( "In %s \n", __func__ )

    size_t index = 0;
    while ( index < processor->instruction_ptr ) {
        int cmd = processor->byte_code[ index++ ];
        PRINT( GRID "Number of instruction: %lu \n", index )

        switch ( cmd ) {
            case PUSH_CMD:
                CHECK_STK_IN_DEBUG( StackPush( &( processor->stk ), processor->byte_code[ index++ ] ); )
                break;
            case POP_CMD:
                CHECK_STK_IN_DEBUG( StackPop( &( processor->stk ) ); )
                break;
            case ADD_CMD:
                CHECK_STK_IN_DEBUG( ProcAdd( &( processor->stk ) ); )
                break;
            case SUB_CMD:
                CHECK_STK_IN_DEBUG( ProcSub( &( processor->stk ) ); )
                break;
            case MUL_CMD:
                CHECK_STK_IN_DEBUG( ProcMul( &( processor->stk ) ); )
                break;
            case DIV_CMD:
                CHECK_STK_IN_DEBUG( ProcDiv( &( processor->stk ) ); )
                break;
            case SQRT_CMD:
                CHECK_STK_IN_DEBUG( ProcSqrt( &( processor->stk ) ); )
                break;
            case POW_CMD:
                CHECK_STK_IN_DEBUG( ProcPow( &( processor->stk ) ); )
                break;
            case IN_CMD:
                CHECK_STK_IN_DEBUG( ProcIn( &( processor->stk ) ); )
                break;
            case OUT_CMD:
                CHECK_STK_IN_DEBUG( ProcOut( &( processor->stk ) ); )
                break;
            case JMP_CMD:
                PRINT( "JMP \n" )
                index = processor->byte_code[ index++ ];
                break;
            case PUSHR_CMD:
                ProcPushR( &( processor->stk ), &( processor->regs[ processor->byte_code[ index++ ] ] ) );
                break;
            case POPR_CMD:
                ProcPopR( &( processor->stk ), &processor->regs[ processor->byte_code[ index++ ] ] );
                break;
            case HLT_CMD:
                PRINT( "HLT \n" )
                return 0;
            default:
                fprintf( stderr, COLOR_RED "Incorrect command %d \n" COLOR_RESET, *( processor->byte_code ) );
                return 1;
        }
        usleep( 200000 );
    }

    PRINT( "Out %s \n", __func__ )

    return 0;
}