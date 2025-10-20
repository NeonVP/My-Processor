#include "processor.h"


void ProcCtor( Processor_t* processor, size_t stack_size, size_t refund_stack_size ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR )

    StackCtor( &( processor->stk ), stack_size );
    StackCtor( &( processor->refund_stk ), refund_stack_size );
}

void ProcDtor( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR )

    StackDtor( &( processor->stk ) );
    free( processor->byte_code );
    processor->byte_code = NULL;
}

// ProcessorStatus_t ProcVerify( Processor_t* processor ) {

// }

ProcessorStatus_t ProcDump( Processor_t* processor, const int error ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    // Processor INFO
    PRINT( COLOR_BRIGHT_YELLOW "+=+=+=+=+=+=+=+ PROCESSOR +=+=+=+=+=+=+=+ \n" );
    PRINT( COLOR_CYAN          "Processor address: " COLOR_RESET "%p \n", processor );
    PRINT( COLOR_CYAN          "Byte code pointer: " COLOR_RESET "%p \n", (void*)processor->byte_code );
    PRINT( COLOR_CYAN          "Instruction ptr  : " COLOR_RESET "%lu\n", processor->instruction_ptr );

    // Registers
    PRINT( COLOR_BRIGHT_MAGENTA "\nRegisters:\n" );
    for ( size_t i = 0; i < REGS_NUMBER; i++ ) {
        PRINT( "    R%cX = %d \n", i == 0 ? 'O' : ( int ) ( 'A' - 1 + i ), processor->regs[ i ] );
    }

    PRINT( COLOR_GREEN "\nMain Stack:\n" );
    StackDump( &( processor->stk ) );

    // PRINT( COLOR_GREEN "\nRefund Stack:\n" );
    // StackDump( &( processor->refund_stk ) );

    PRINT( COLOR_BRIGHT_YELLOW "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ \n" );

    return SUCCESS;
}

void ExeFileToByteCode( Processor_t* processor, FileStat* file ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );
    my_assert( file,      ASSERT_ERR_NULL_PTR );

    PRINT( COLOR_BRIGHT_YELLOW "In %s \n", __func__ )

    file->size = DetermineFileSize( file->address );

    char* buffer = ReadToBuffer( file );
    char* old_buffer_ptr = buffer;

    size_t number_of_instructions    = 0;
    int    number_of_characters_read = 0;
    sscanf( buffer, "%lu%n", &number_of_instructions, &number_of_characters_read );
    buffer += number_of_characters_read;

    // Every row have maximum 2 instructions, so max number of instructions is number of lines twice
    processor->byte_code = ( int* ) calloc ( number_of_instructions, sizeof( *processor->byte_code ) );
    assert( processor->byte_code && "Memory allocation error \n" );

    FillInByteCode( processor, buffer, number_of_instructions );

    fprintf( stderr, "\n" );

    free( old_buffer_ptr );

    PRINT( "Out %s \n", __func__ )
}

void FillInByteCode( Processor_t* processor, char* buffer, size_t number_of_instructions ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR );

    int instruction = 0;
    int number_of_characters_read = 0;

    for ( size_t i = 0; i < number_of_instructions; i++ ) {
        if ( sscanf( buffer, "%d %n", &instruction, &number_of_characters_read ) == 1 ) {
            processor->byte_code[ i ] = instruction;
            buffer += number_of_characters_read;
            PRINT( " %d", instruction )
        }
    }
}

int ByteCodeProcessing( Processor_t* processor ) {
    my_assert( processor, ASSERT_ERR_NULL_PTR )

    PRINT( "In %s \n", __func__ );

    int command = 0;
    while ( processor->byte_code[ processor->instruction_ptr ] != HLT_CMD ) {
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

            case CALL_CMD:  ProcCall ( processor ); break;
            case RET_CMD:   ProcRet  ( processor ); break;

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