#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "assembler.h"


int main( int argc, char** argv ) {
    Assembler_t assembler = {};
    ArgvProcessing( argc, argv, &( assembler.asm_file ), &( assembler.exe_file ) );

    // AsmCtor( argc, argv, &assembler );            // TODO: transfer parser to separate function

    PRINT( "FILES:\nfor input - %s\nfor output - %s\n", assembler.asm_file.address, assembler.exe_file.address );

    AsmFileProcessing( &assembler );

    OutputInFile( &assembler );
}

// void AsmCtor( int argc, char** argv, Assembler_t* assembler ) {
//     assert( argc > 0 );
//     assert( argv != NULL );
//     assert( assembler != NULL );

//     assembler->asm_file.address  = "./asm.txt";
//     assembler->exe_file.address = "./byte-code.txt";

//     const char* const opts = "i:o:";
//     int opt = 0;

//     // TODO: transfer all parsers to separate function
//     while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
//         switch ( opt ) {
//             case 'i':
//                 assembler->input_file.address  = strdup( optarg );
//                 break;
//             case 'o':
//                 assembler->output_file.address = strdup( optarg );
//                 break;
//             default:
//                 fprintf( stderr, "Incorrect cmd params. Program will use std files.\n" );
//                 break;
//         }
//     }

//     assembler->input_file.size = DetermineFileSize( assembler->input_file.address );
// }

int AsmFileProcessing( Assembler_t* assembler ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR );

    char* buffer = ReadToBuffer( &( assembler->asm_file ) );

    StrPar* strings = ( StrPar* ) calloc ( assembler->asm_file.nLines, sizeof( StrPar ) );
    my_assert( strings != NULL, ASSERT_ERR_NULL_PTR );

    SplitIntoLines( strings, buffer, assembler->asm_file.nLines );

    char instruction[ MAX_CMD_LEN ] = "";
    int  number                     = 0;
    int  byte_code                  = 0;
    int  number_of_params           = 0;

    PRINT( "Start of loop with sscanf \n" )
    size_t index = 0;
    for ( size_t i = 0; i < assembler->asm_file.nLines; i++ ) {
        number_of_params = sscanf( strings[i].ptr, "%s %d", instruction, &number );           //number of params
        byte_code = AsmCodeProcessing( instruction );

        if ( number_of_params == 2 ) {
            switch ( byte_code ) {
                case PUSH_CMD:
                case POP_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->byte_codes[ index++ ] = number;
                    assembler->instruction_cnt += 2;
                    PRINT( "%d %d  ---  %s %d \n", assembler->byte_codes[ index - 2 ], assembler->byte_codes[ index - 1 ], instruction, number );
                    break;
                default:
                    fprintf( stderr, "Incorrect assembler command \"%s %d\" in line %lu. \n", instruction, number, i );
                    free( buffer );
                    free( strings );
                    return 0;
            }
        }
        else {
            switch ( byte_code ) {
                case ADD_CMD:
                case SUB_CMD:
                case MUL_CMD:
                case DIV_CMD:
                case POW_CMD:
                case SQRT_CMD:
                case OUT_CMD:
                case HLT_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    PRINT( "%d  ---  %s \n", byte_code, instruction )
                    break;
                default:
                    fprintf( stderr, "Incorrect assembler command \"%s\" in line %lu. \n", strings[i].ptr, i );
                    free( buffer );
                    free( strings );

                    return 0;
            }
        }
    }

    free( buffer );
    free( strings );

    return 1;
}

int AsmCodeProcessing( char* instruction ) {     // FIXME: strncmp
    if ( strncmp( instruction, "PUSH", 4 ) == 0 ) {
        return PUSH_CMD;
    }

    if ( strncmp( instruction, "POP", 3 ) == 0 ) {
        return POP_CMD;
    }

    if ( strncmp( instruction, "ADD", 3 ) == 0 ) {
        return ADD_CMD;
    }

    if ( strncmp( instruction, "SUB", 3 ) == 0 ) {
        return SUB_CMD;
    }

    if ( strncmp( instruction, "MUL", 3 ) == 0 ) {
        return MUL_CMD;
    }

    if ( strncmp( instruction, "DIV", 3 ) == 0 ) {
        return DIV_CMD;
    }

    if ( strncmp( instruction, "POW", 3 ) == 0 ) {
        return POW_CMD;
    }

    if ( strncmp( instruction, "SQRT", 4 ) == 0 ) {
        return SQRT_CMD;
    }

    if ( strncmp( instruction, "IN", 2 ) == 0 ) {
        return SQRT_CMD;
    }

    if ( strncmp( instruction, "OUT", 3 ) == 0 ) {
        return OUT_CMD;
    }

    if ( strncmp( instruction, "HLT", 3 ) == 0 ) {
        return HLT_CMD;
    }

    // TODO: add PUSHR, POPR processing

    return 0;
}

void OutputInFile(Assembler_t* assembler ) {
    my_assert( assembler != NULL, ASSERT_ERR_NULL_PTR )

    FILE* file = fopen( assembler->exe_file.address, "w" );
    my_assert( file != NULL, ASSERT_ERR_FAIL_OPEN );

    fprintf( file, "%lu", assembler->instruction_cnt );

    int element = 0;

    for ( size_t i = 0; i < assembler->instruction_cnt; i++ ) {
        fprintf( file, " %d", assembler->byte_codes[i] );
    }

    int result_of_fclose = fclose( file );
    my_assert( result_of_fclose == 0, ASSERT_ERR_FAIL_CLOSE )
}