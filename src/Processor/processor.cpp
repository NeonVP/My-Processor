#include "processor.h"    // TODO: the vynesti of the main in the of the OTDELNYYJJ fail вынести main в отдельный файл main.cpp


int main( int argc, char** argv ) {
    FileStat exe_file = {};
    ArgvProcessing( argc, argv, &exe_file );

    Processor_t processor = {};
    ProcCtor( &processor, 20 );

    ExeFileToByteCode( &processor, &exe_file );

    int result = ByteCodeProcessing( &processor );

    ProcDtor( &processor );

    if ( result == 1 ) {    // TODO25: выводить, что неправильная работа проги
        return 1;
    }
    else {
        return 0;
    }
}

void ProcCtor( Processor_t* processor, size_t stack_size ) {     // TODO: add byte_code_size
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )

    StackCtor( &( processor->stk ), stack_size );
    processor->byte_code = ( int* ) calloc ( SIZE, sizeof( *processor->byte_code ) );
    my_assert( processor->byte_code != NULL, ASSERT_ERR_FAIL_ALLOCATE_MEMORY )
}

void ProcDtor( Processor_t* processor ) {
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )

    StackDtor( &( processor->stk ) );
    free( processor->byte_code );
    processor->byte_code = NULL;
}

void ExeFileToByteCode( Processor_t* processor, FileStat* file ) {       // TODO: rename
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR );
    ;
    ;

    my_assert( file      != NULL, ASSERT_ERR_NULL_PTR )

    PRINT( "In %s \n", __func__ )

    file->size = DetermineFileSize( file->address );

    char* buffer = ReadToBuffer( file );
    PRINT( "%s \n", buffer );
    char* old_buffer_ptr = buffer;

    size_t number_of_instructions = 0;
    int n = 0;          // TODO: rename
    sscanf( buffer, "%lu%n", &number_of_instructions, &n );
    buffer += n;

    // size_t counter = 0;
    // while ( sscanf( buffer, "%d%n", &num, &n ) == 1 ) {
    //     processor->byte_code[ counter++ ] = num;
    //     buffer += n;
    //     PRINT( "%d", num )
    // }

    int num = 0;        // TODO: rename + transfer to sep + другой принт
    for ( size_t i = 0; i < number_of_instructions; i++ ) {
        if ( sscanf( buffer, "%d %n", &num, &n ) == 1 ) {
            processor->byte_code[ i ] = num;
            buffer += n;
            PRINT( " %d", num )
        }
        else {
            fprintf( stderr, "There are more instructions than expected \n" );
        }
    }

    fprintf( stderr, "\n" );

    free( old_buffer_ptr );

    PRINT( "Out %s \n", __func__ )
}

int ByteCodeProcessing( Processor_t* processor ) {
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR )

    PRINT( "In %s \n", __func__ )

    while ( processor->byte_code[ processor->instruction_ptr ] != HLT_CMD ) {           // FIXME: instruction ptr ariphmetics
        int cmd = processor->byte_code[ processor->instruction_ptr++ ];
        PRINT( GRID "Number of instruction: %lu \n", processor->instruction_ptr )

        switch ( cmd ) {
            case PUSH_CMD:
                CHECK_STK_IN_DEBUG( StackPush( &( processor->stk ), processor->byte_code[ processor->instruction_ptr++ ] ); )
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
            case JB_CMD:
            case JA_CMD:
            case JE_CMD:
            case JBE_CMD:
            case JAE_CMD:
                PRINT( "JMP \n" )
                ProcJump( processor );
                break;
            case PUSHR_CMD:
                ProcPushR( &( processor->stk ), &( processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] ) );
                break;
            case POPR_CMD:
                ProcPopR( &( processor->stk ), &processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] );
                break;
            case HLT_CMD:
                PRINT( "HLT \n" )
                return 0;
            default:
                fprintf( stderr, COLOR_RED "Incorrect command %d \n" COLOR_RESET, *( processor->byte_code ) );
                return 1;
        }
        usleep( 50000 );
    }

    PRINT( "Out %s \n", __func__ )

    return 0;
}

void ProcJump( Processor_t* processor ) {       // TODO: rework func diskran
    // my_assert( processor != NULL; ASSERT_ERR_NULL_PTR )

    int cmd = processor->byte_code[ processor->instruction_ptr - 1 ];
    int index = processor->byte_code[ processor->instruction_ptr++ ];

    if ( cmd == JMP_CMD ) {
        processor->instruction_ptr = index;
    }

    int b = StackTop( &( processor->stk ) );
    StackPop( &( processor->stk ) );
    int a = StackTop( &( processor->stk ) );

    if ( cmd == JB_CMD ) {
        if ( a < b ) {
            processor->instruction_ptr = index;
        }
    }
    else if ( cmd == JA_CMD ) {
        if ( a > b ) {
            processor->instruction_ptr = index;
        }
    }
    else if ( cmd == JBE_CMD ) {
        if ( a <= b ) {
            processor->instruction_ptr = index;
        }
    }
    else if ( cmd == JAE_CMD ) {
        if ( a >= b ) {
            processor->instruction_ptr = index;
        }
    }
    else {
        if ( a == b ) {
            processor->instruction_ptr = index;
        }
    }
}