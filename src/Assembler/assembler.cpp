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

    char instruction1[ MAX_INSTRUCT_LEN ] = "";
    char instruction2[ MAX_INSTRUCT_LEN ] = "";
    int  number                           = 0;

    int command          = 0;
    int number_of_params = 0;
    int n                = 0;
    int register_or_not  = 0;

    PRINT( "Start of loop with sscanf \n" )
    // for ( size_t i = 0; i < assembler->asm_file.nLines; i++ ) {
    //     number_of_params = sscanf( strings[ i ].ptr, "%s%n", instruction1, &n );
    //     strings[ i ].ptr += n;
    //     command = AsmCommandProcessing( instruction1 );

    //     switch ( command ) {
    //         case PUSH_CMD:
    //         case POP_CMD:
    //             assembler->byte_code[ assembler->instruction_cnt++ ] = command;
    //             number_of_params = sscanf( strings[ i ].ptr, "%s", instruction2 );
    //             number = atoi( instruction2 );

    //             if ( number == 0 && instruction2[ 0 ] != '\0' ) {
    //                 fprintf( stderr, COLOR_RED "Incorrect assembler command \"%s %s\" in line %lu. \n" COLOR_RESET, instruction1, instruction2, i + 1 );
    //                 free( buffer );
    //                 free( strings );
    //                 return 0;
    //             }

    //             assembler->byte_code[ assembler->instruction_cnt++ ] = number;
    //             PRINT( "%d %d  ---  %s %d \n", assembler->byte_code[ assembler->instruction_cnt - 2 ], assembler->byte_code[ assembler->instruction_cnt - 1 ], instruction1, number );
    //             break;
    //         case JMP_CMD:
    //         case JA_CMD:
    //         case JB_CMD:
    //         case JAE_CMD:
    //         case JBE_CMD:
    //         case JE_CMD:
    //             break;
    //         case ADD_CMD:
    //         case SUB_CMD:
    //         case MUL_CMD:
    //         case DIV_CMD:
    //         case POW_CMD:
    //         case SQRT_CMD:
    //         case OUT_CMD:
    //         case HLT_CMD:
    //             assembler->byte_code[ assembler->instruction_cnt++ ] = command;
    //             PRINT( "%d  ---  %s \n", command, instruction1 )
    //             break;
    //         default:
    //             fprintf( stderr, "Incorrect assembler command \"%s %d\" in line %lu. \n", instruction1, number, i + 1 );
    //             free( buffer );
    //             free( strings );
    //             return 0;
    //         }
    //     switch ( command ) {
    //         case ADD_CMD:
    //         case SUB_CMD:
    //         case MUL_CMD:
    //         case DIV_CMD:
    //         case POW_CMD:
    //         case SQRT_CMD:
    //         case OUT_CMD:
    //         case HLT_CMD:
    //             assembler->byte_code[ assembler->instruction_cnt++ ] = command;
    //             PRINT( "%d  ---  %s \n", command, instruction1 )
    //             break;
    //         default:
    //             fprintf( stderr, "Incorrect assembler command \"%s\" in line %lu. \n", strings[i].ptr, i + 1 );
    //             free( buffer );
    //             free( strings );

    //             return 0;
    //     }
    // }

    for ( size_t i = 0; i < assembler->asm_file.nLines; i++ ) {
        number_of_params = sscanf( strings[ i ].ptr, "%s%n", instruction1, &n );
        strings[ i ].ptr += n;
        command = AsmCodeProcessing( instruction1 );
        assembler->byte_code[ assembler->instruction_cnt++ ] = command;

        switch ( command ) {
            case PUSH_CMD:
                sscanf( strings[ i ].ptr, "%s", instruction2 );
                register_or_not = RegisterNameProcessing( instruction2 );

                if ( register_or_not == -1 ) {
                    number = atoi( instruction2 );
                    assembler->byte_code[ assembler->instruction_cnt++ ] = number;
                }
                else {
                    assembler->byte_code[ assembler->instruction_cnt - 1 ] += 32;
                    assembler->byte_code[ assembler->instruction_cnt++ ]    = register_or_not;
                }

                PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d %d \n", instruction1, instruction2, command, number );

                break;
            case POP_CMD:
                sscanf( strings[ i ].ptr, "%s", instruction2 );
                if ( strlen( instruction2 ) > 0 ) {
                    assembler->byte_code[ assembler->instruction_cnt - 1 ] += 32;
                    register_or_not = RegisterNameProcessing( instruction2 );
                    if ( register_or_not != -1 ) {
                        assembler->byte_code[ assembler->instruction_cnt++ ] = register_or_not;
                        PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d %d \n", instruction1, instruction2, command, number );
                    }
                    else {
                        PRINT( COLOR_BRIGHT_RED "Incorrect register name \"%s\" in file: %s::%lu \n", instruction2, assembler->asm_file.address, i );
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
                PRINT( COLOR_BRIGHT_GREEN "%-4s %-10s --- %-2d \n", instruction1, "", command );
                break;
            default:
                fprintf( stderr, COLOR_BRIGHT_RED "Incorrect command \"%s\" in file: %s::%lu \n", instruction1, assembler->asm_file.address, i );
                return 0;
        }
    }

    free( buffer );
    free( strings );

    PRINT( GRID COLOR_BRIGHT_YELLOW "Out %s \n", __func__ )

    return 1;
}

int AsmCodeProcessing( char* instruction ) {
    my_assert( instruction != NULL, ASSERT_ERR_NULL_PTR );

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

    if ( strlen( name ) == 3 ) {
        if ( name[0] == 'R' && name[2] == 'X' ) {
            return name[1] - 'A' + 1;
        }
    }

    return -1;
}