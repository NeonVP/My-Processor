#include "FileRWUtils.h"

void ArgvProcessing( int argc, char** argv, ON_ASM( FileStat* asm_file, ) FileStat* exe_file ) {
            my_assert( argv     != NULL, ASSERT_ERR_NULL_PTR        )
    ON_ASM( my_assert( asm_file != NULL, ASSERT_ERR_NULL_PTR        ) )
            my_assert( exe_file != NULL, ASSERT_ERR_NULL_PTR        )
            my_assert( isfinite( argc ), ASSERT_ERR_INFINITE_NUMBER )

    ON_ASM( asm_file->address = "./asm-code.txt"; )
            exe_file->address = "./byte-code.txt";

    int opt = 0;
    const char* opts = "i:o:";

    while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
        switch ( opt ) {
            case 'i': ON_ASM( asm_file->address = strdup( optarg ); )     exe_file->address = strdup( optarg );   break;
            case 'o': ON_ASM( exe_file->address = strdup( optarg ); )                                             break;

            default:
                ON_ASM( fprintf( stderr, "Warning: asm_file will be \"%s\" \n", asm_file->address ); )
                        fprintf( stderr, "Warning: exe_file will be \"%s\" \n", exe_file->address );
                break;
        }
    }
}

char* ReadToBuffer( FileStat* input_file ) {
    PRINT( "In %s \n", __func__ )                       // TODO: return buffer

    if ( input_file->size == 0 ) {
        input_file->size = DetermineFileSize( input_file->address );
    }

    char* buffer = ( char* ) calloc ( ( size_t ) input_file->size + 1, sizeof( *buffer ) );
    my_assert( buffer != NULL, ASSERT_ERR_NULL_PTR )

    FILE* file = fopen( input_file->address, "r" );
    my_assert( file != NULL, ASSERT_ERR_FAIL_OPEN )

    size_t result_of_read = fread( buffer, sizeof( char ), ( size_t )input_file->size, file );
    my_assert( result_of_read != 0, ASSERT_ERR_FAIL_READ );

    int result_of_fclose = fclose( file );
    my_assert( result_of_fclose == 0, ASSERT_ERR_FAIL_CLOSE );

    input_file->nLines = RowCounter( buffer );
    PRINT( "Out %s \n", __func__ )

    return buffer;
}

void SplitIntoLines( StrPar* strings, char* buffer, size_t nLines ) {           // TODO: conditional compilation PRINT
    my_assert( strings != NULL, ASSERT_ERR_NULL_PTR );
    my_assert( buffer  != NULL, ASSERT_ERR_NULL_PTR );

    PRINT( "In %s \n", __func__ )

    if ( nLines == 0 ) {
        nLines = RowCounter( buffer );
    }

    // TODO: in one loop
    // for ( size_t i = 0; i < nLines; i++ ) {
    //     strings[i].ptr = buffer;

    //     while ( *buffer != '\n' || *buffer != '\0' ) {
    //         strings[i].len++;
    //         buffer++;
    //     }

    //     *buffer = '\0';
    //     buffer++;
    // }

    size_t line = 0;
    strings[ line ].ptr = buffer;

    while ( *buffer != '\0' ) {
        if ( *buffer == '\n') {
            *buffer = '\0';
            line++;
            strings[ line ].ptr = buffer + 1;
        }
        else {
            strings[ line ].len++;
        }

        buffer++;
    }

    PRINT( "Out %s \n", __func__ )
}

size_t RowCounter( const char* buffer ) {
    my_assert( buffer != NULL, ASSERT_ERR_NULL_PTR );

    size_t cnt = 1;

    while ( *buffer != '\0' ) {
        if ( *buffer == '\n' )  cnt++;

        buffer++;
    }

    return cnt;
}

off_t DetermineFileSize( const char* file_address ) {
    struct stat file_stat;
    int check_stat = stat( file_address, &file_stat );
    my_assert( check_stat == 0, ASSERT_ERR_FAIL_STAT );

    return file_stat.st_size;
}