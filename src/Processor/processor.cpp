#include "processor.h"    // TODO: the vynesti of the main in the of the OTDELNYYJJ fail вынести main в отдельный файл main.cpp


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

void ExeFileToByteCode( Processor_t* processor, FileStat* file ) {
    my_assert( processor != NULL, ASSERT_ERR_NULL_PTR );
    my_assert( file      != NULL, ASSERT_ERR_NULL_PTR );

    PRINT( COLOR_BRIGHT_YELLOW "In %s \n", __func__ )

    file->size = DetermineFileSize( file->address );

    char* buffer = ReadToBuffer( file );
    char* old_buffer_ptr = buffer;

    size_t number_of_instructions = 0;
    int n = 0;                                                              // TODO25: rename
    sscanf( buffer, "%lu%n", &number_of_instructions, &n );
    buffer += n;

    // size_t counter = 0;
    // while ( sscanf( buffer, "%d%n", &num, &n ) == 1 ) {
    //     processor->byte_code[ counter++ ] = num;
    //     buffer += n;
    //     PRINT( "%d", num )
    // }

    int num = 0;                                                         // TODO: rename + transfer to sep + другой принт
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

    // while ( processor->byte_code[ processor->instruction_ptr ] != HLT_CMD ) {           // FIXME: instruction ptr ariphmetics
    //     int command = processor->byte_code[ processor->instruction_ptr++ ];
    //     PRINT( GRID "Number of instruction: %lu \n", processor->instruction_ptr )

    //     switch ( command ) {
    //         case PUSH_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( StackPush( &( processor->&( processor->stk ) ), processor->byte_code[ processor->instruction_ptr++ ] ); )
    //             break;
    //         case POP_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( StackPop( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case ADD_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcAdd( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case SUB_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcSub( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case MUL_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcMul( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case DIV_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcDiv( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case SQRT_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcSqrt( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case POW_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcPow( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case IN_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcIn( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case OUT_CMD:
    //             CHECK_&( processor->stk )_IN_DEBUG( ProcOut( &( processor->&( processor->stk ) ) ); )
    //             break;
    //         case JMP_CMD:
    //         case JB_CMD:
    //         case JA_CMD:
    //         case JE_CMD:
    //         case JBE_CMD:
    //         case JAE_CMD:
    //             PRINT( "JMP \n" )
    //             ProcJump( processor );
    //             break;
    //         case PUSHR_CMD:
    //             ProcPushR( &( processor->&( processor->stk ) ), &( processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] ) );
    //             break;
    //         case POPR_CMD:
    //             ProcPopR( &( processor->&( processor->stk ) ), &processor->regs[ processor->byte_code[ processor->instruction_ptr++ ] ] );
    //             break;
    //         case HLT_CMD:
    //             PRINT( "HLT \n" )
    //             return 0;
    //         default:
    //             fprintf( stderr, COLOR_RED "Incorrect command %d \n" COLOR_RESET, *( processor->byte_code ) );
    //             return 1;
    //     }
    //     usleep( 50000 );
    // }

    int command = 0;
    while ( processor->byte_code[ processor->instruction_ptr ] != HLT_CMD ) {           // FIXME: instruction ptr ariphmetics
        command = processor->byte_code[ processor->instruction_ptr++ ];

        switch ( command ) {
            case PUSH_CMD:  ProcPush ( processor ); break;
            case POP_CMD:   ProcPop  ( processor ); break;
            case ADD_CMD:   ProcAdd  ( processor ); break;
            case SUB_CMD:   ProcSub  ( processor ); break;
            case MUL_CMD:   ProcMul  ( processor ); break;
            case DIV_CMD:   ProcDiv  ( processor ); break;
            case POW_CMD:   ProcPow  ( processor ); break;
            case SQRT_CMD:  ProcSqrt ( processor ); break;
            case IN_CMD:    ProcIn   ( processor ); break;
            case OUT_CMD:   ProcOut  ( processor ); break;
            case PUSHR_CMD: ProcPushR( processor ); break;
            case POPR_CMD:  ProcPopR ( processor ); break;

            case JMP_CMD:
            case JE_CMD:
            case JB_CMD:
            case JA_CMD:
            case JBE_CMD:
            case JAE_CMD:   ProcJump( processor ); break;

            case HLT_CMD:   return 0;

            default:
                fprintf( stderr, COLOR_RED "Incorrect command %d \n" COLOR_RESET, *( processor->byte_code ) );
                return 1;
        }
        usleep( 50000 );
    }

    PRINT( "Out %s \n", __func__ )

    return 0;
}