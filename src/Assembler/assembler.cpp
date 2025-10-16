#include "assembler.h"

#define StrCompare( str1, str2 ) strncmp( str1, str2, sizeof( str2 ) - 1 )


void AssemblerDtor( Assembler_t* assembler ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR );

    free( assembler->byte_code );
    free( assembler->asm_file.address );
    free( assembler->exe_file.address );
}

int AsmCodeToByteCode( Assembler_t* assembler ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR );

    PRINT( GRID COLOR_BRIGHT_YELLOW "In %s \n\n", __func__ )

    char* buffer = ReadToBuffer( &( assembler->asm_file ) );

    StrPar* strings = ( StrPar* ) calloc ( assembler->asm_file.nLines, sizeof( *strings ) );
    my_assert( strings != NULL, ASSERT_ERR_NULL_PTR );

    SplitIntoLines( strings, buffer, assembler->asm_file.nLines );

    // Every row have maximum 2 instructions, so max number of instructions is number of lines twice
    assembler->byte_code = ( int* ) calloc ( assembler->asm_file.nLines * 2, sizeof( int ) );
    my_assert( assembler->byte_code != NULL, ASSERT_ERR_FAIL_ALLOCATE_MEMORY )

        PRINT( COLOR_BRIGHT_YELLOW "\n---First Run---\n" );
    int translate_result = TranslateAsmToByteCode( assembler, strings );
        PRINT( COLOR_BRIGHT_YELLOW "\n---Second Run---\n");
        translate_result = TranslateAsmToByteCode( assembler, strings );

    free( buffer );
    free( strings );

    PRINT( "\n" GRID COLOR_BRIGHT_YELLOW "Out %s \n", __func__ )

    return translate_result;
}

int TranslateAsmToByteCode( Assembler_t* assembler, StrPar* strings ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR );
    my_assert( strings   != NULL, ASSERT_ERR_NULL_PTR );

    assembler->instruction_cnt = 0;

    char instruction1[ MAX_INSTRUCT_LEN ] = "";
    char instruction2[ MAX_INSTRUCT_LEN ] = "";
    int  number                           = 0;

    int command          = 0;
    int number_of_params = 0;
    int n                = 0;       // TODO25: rename
    int register_or_not  = 0;
    const char* str_pointer = 0;

    for ( size_t i = 0; i < assembler->asm_file.nLines; i++ ) {
        str_pointer = strings[ i ].ptr;
        number_of_params = sscanf( str_pointer, "%s%n", instruction1, &n );
        str_pointer += n;
        command = AsmCodeProcessing( instruction1 );

        switch ( command ) {
            case MARK_CMD:
                assembler->labels[ instruction1[1] - '0' ] = assembler->instruction_cnt + 1;

                break;
            case PUSH_CMD:
                assembler->byte_code[ assembler->instruction_cnt++ ] = command;

                sscanf( str_pointer, "%s", instruction2 );
                register_or_not = RegisterNameProcessing( instruction2 );

                if ( register_or_not == -1 ) {
                    number = atoi( instruction2 );
                    assembler->byte_code[ assembler->instruction_cnt++ ] = number;
                }
                else {
                    assembler->byte_code[ assembler->instruction_cnt - 1 ] += 32;
                    assembler->byte_code[ assembler->instruction_cnt++ ]    = register_or_not;
                }

                PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d %d \n", instruction1, instruction2, assembler->byte_code[ assembler->instruction_cnt - 2 ],
                                                                                                   assembler->byte_code[ assembler->instruction_cnt - 1 ] );

                break;
            case POP_CMD:
                assembler->byte_code[ assembler->instruction_cnt++ ] = command;

                sscanf( str_pointer, "%s", instruction2 );
                if ( strlen( instruction2 ) > 0 ) {
                    assembler->byte_code[ assembler->instruction_cnt - 1 ] += 32;
                    register_or_not = RegisterNameProcessing( instruction2 );
                    if ( register_or_not != -1 ) {
                        assembler->byte_code[ assembler->instruction_cnt++ ] = register_or_not;
                        PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d %d \n", instruction1, instruction2, command, register_or_not );
                    }
                    else {
                        PRINT( COLOR_BRIGHT_RED "Incorrect register name \"%s\" in file: %s:%lu \n", instruction2, assembler->asm_file.address, i );
                        return 0;
                    }
                }
                else {
                    PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d \n", instruction1, "", command );
                }

                break;
            case ADD_CMD:
            case SUB_CMD:
            case MUL_CMD:
            case DIV_CMD:
            case POW_CMD:
            case SQRT_CMD:
            case IN_CMD:
            case OUT_CMD:
                assembler->byte_code[ assembler->instruction_cnt++ ] = command;

                PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d \n", instruction1, "", command );
                break;
            case HLT_CMD:
                assembler->byte_code[ assembler->instruction_cnt++ ] = command;

                PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d \n", instruction1, "", command );
                return 1;
            default:
                fprintf( stderr, COLOR_BRIGHT_RED "Incorrect command \"%s\" in file: %s:%lu \n", instruction1, assembler->asm_file.address, i );
                return 0;
        }
    }

    fprintf( stderr, COLOR_BRIGHT_RED "There is no final HLT command \n" COLOR_RESET );
    return 0;
}

int AsmCodeProcessing( char* instruction ) {
    my_assert( instruction != NULL, ASSERT_ERR_NULL_PTR );

    if ( instruction[0] == ':' )                  { return MARK_CMD; }

    if ( StrCompare( instruction, "PUSH" ) == 0 ) { return PUSH_CMD; }
    if ( StrCompare( instruction, "POP"  ) == 0 ) { return POP_CMD;  }
    if ( StrCompare( instruction, "ADD"  ) == 0 ) { return ADD_CMD;  }
    if ( StrCompare( instruction, "SUB"  ) == 0 ) { return SUB_CMD;  }
    if ( StrCompare( instruction, "MUL"  ) == 0 ) { return MUL_CMD;  }
    if ( StrCompare( instruction, "DIV"  ) == 0 ) { return DIV_CMD;  }
    if ( StrCompare( instruction, "POW"  ) == 0 ) { return POW_CMD;  }
    if ( StrCompare( instruction, "SQRT" ) == 0 ) { return SQRT_CMD; }
    if ( StrCompare( instruction, "IN"   ) == 0 ) { return SQRT_CMD; }
    if ( StrCompare( instruction, "OUT"  ) == 0 ) { return OUT_CMD;  }
    if ( StrCompare( instruction, "JMP"  ) == 0 ) { return JMP_CMD;  }
    if ( StrCompare( instruction, "HLT"  ) == 0 ) { return HLT_CMD;  }

    return 0;
}

void OutputInFile( Assembler_t* assembler ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR );

    FILE* file = fopen( assembler->exe_file.address, "w" );
    my_assert( file != NULL, ASSERT_ERR_FAIL_OPEN );

    fprintf( file, "%lu", assembler->instruction_cnt );

    for ( size_t i = 0; i < assembler->instruction_cnt; i++ ) {
        fprintf( file, " %d", assembler->byte_code[i] );
    }

    int result_of_fclose = fclose( file );
    my_assert( result_of_fclose == 0, ASSERT_ERR_FAIL_CLOSE )
}

int RegisterNameProcessing( char* name ) {
    my_assert( name != NULL, ASSERT_ERR_NULL_PTR );

    int number = 0;
    if ( strlen( name ) == 3 ) {
        if ( name[0] == 'R' && name[2] == 'X' ) {
            number = name[1] - 'A' + 1;

            if ( number < 8 ) {
                return number;
            }
            else {
                return -1;
            }
        }
    }

    return -1;
}