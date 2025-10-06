#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

// #include "common.h"
#include "file_processing.h"


struct Assembler_t {
    FileStat input_file      = {};
    FileStat output_file     = {};
    int      byte_codes[200] = {};
    size_t   instruction_cnt = 0;
};

void AsmCtor( int argc, char** argv, struct Assembler_t* assembler );
int AsmFileProcessing( Assembler_t* assembler );
int AsmCodeProcessing( char* instruction );
void OutputInFile(Assembler_t* assembler );

int main( int argc, char** argv ) {
    Assembler_t assembler = {};

    AsmCtor( argc, argv, &assembler );
    fprintf( stderr, "FILES:\nfor input - %s\nfor output - %s\n", assembler.input_file.address, assembler.output_file.address );

    AsmFileProcessing( &assembler );

    OutputInFile( &assembler );
}

void AsmCtor( int argc, char** argv, Assembler_t* assembler ) {
    assert( argc > 0 );
    assert( argv != NULL );
    assert( assembler != NULL );

    assembler->input_file.address  = "./asm.txt";
    assembler->output_file.address = "./byte-code.txt";
    
    const char* const opts = "i:o:";
    int opt = 0;

    while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
        switch ( opt ) {
            case 'i':
                assembler->input_file.address  = strdup( optarg );
                break;
            case 'o':
                assembler->output_file.address = strdup( optarg );
                break;
            default:
                fprintf( stderr, "Incorrect cmd params. Program will use std files.\n" );
                break;
        }
    }

    assembler->input_file.size = determining_the_file_size( assembler->input_file.address );
}

int AsmFileProcessing( Assembler_t* assembler ) {
    assert( assembler != NULL );

    char* buffer = ( char* ) calloc ( assembler->input_file.size, sizeof( char ) );
    assert( buffer != NULL );

    ReadingFile( &( assembler->input_file ), buffer );

    StrPar* strings = ( StrPar* ) calloc ( assembler->input_file.nLines, sizeof( StrPar ) );
    assert( strings != NULL );

    SplittingIntoLines( strings, buffer, assembler->input_file.nLines );

    char instruction[10] = "";
    int  number          = 0;
    int  byte_code       = 0;
    int  cnt_of_elem     = 0;

    size_t index = 0;
    for ( size_t i = 0; i < assembler->input_file.nLines; i++ ) {
        cnt_of_elem = sscanf( strings[i].ptr, "%s %d", &instruction, &number );
        byte_code = AsmCodeProcessing( instruction );

        fprintf( stderr, "Number of elements in line = %d \n"
                         "Instruction = %s, number = %d   \n", cnt_of_elem, instruction, number );

        if ( cnt_of_elem == 2 ) {
            fprintf( stderr, "before switch for 2 elements \n" );
            switch ( byte_code ) {
                case PUSH_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->byte_codes[ index++ ] = number;
                    assembler->instruction_cnt += 2;
                    fprintf( stderr, "%d %d  ---  %s %d \n", byte_code, number, instruction, number );
                    break;
                case POP_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->byte_codes[ index++ ] = number;
                    assembler->instruction_cnt += 2;
                    fprintf( stderr, "%d %d  ---  %s %d \n", byte_code, number, instruction, number );
                    break;
                default:
                    fprintf( stderr, "Incorrect assembler command \"%s %d\" in line %lu. \n", i );
                    return 0;
            }
        }
        else {
            fprintf( stderr, "before switch for 1 element \n" );
            switch ( byte_code ) {
                case ADD_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case SUB_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case MUL_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case DIV_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case POW_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case SQRT_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case OUT_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                case HLT_CMD:
                    assembler->byte_codes[ index++ ] = byte_code;
                    assembler->instruction_cnt++;
                    fprintf( stderr, "%d  ---  %s \n", byte_code, instruction );
                    break;
                default:
                    fprintf( stderr, "Incorrect assembler command \"%s\" in line %lu. \n", strings[i].ptr, i );
                    return 0;
                    break;
            }
        }
        fprintf( stderr, "Processed %lu strings, nLines = %lu \n", i + 1, assembler->input_file.nLines );
    }

    return 1;
}

int AsmCodeProcessing( char* instruction ) {
    if ( strcmp( instruction, "PUSH" ) == 0 ) {
        return PUSH_CMD;
    }

    if ( strcmp( instruction, "POP" ) == 0 ) {
        return POP_CMD;
    }

    if ( strcmp( instruction, "ADD") == 0 ) {
        return ADD_CMD;
    }

    if ( strcmp( instruction, "SUB" ) == 0 ) {
        return SUB_CMD;
    }

    if ( strcmp( instruction, "MUL" ) == 0 ) {
        return MUL_CMD;
    }

    if ( strcmp( instruction, "DIV" ) == 0 ) {
        return DIV_CMD;
    }

    if ( strcmp( instruction, "POW" ) == 0 ) {
        return POW_CMD;
    }

    if ( strcmp( instruction, "SQRT" ) == 0 ) {
        return SQRT_CMD;
    }

    if ( strcmp( instruction, "OUT" ) == 0 ) {
        return OUT_CMD;
    }

    if ( strcmp( instruction, "HLT" ) == 0 ) {
        return HLT_CMD;
    }

    return 0;
}

void OutputInFile(Assembler_t* assembler ) {
    assert( assembler != NULL );

    FILE* file = fopen( assembler->output_file.address, "w" );
    assert( file != NULL );

    for ( size_t i = 0; i < assembler->instruction_cnt; i++ ) {
        fprintf( file, "%d ", assembler->byte_codes[i] );
    }

    fclose( file );
}