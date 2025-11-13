#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "FileRWUtils.h"
#include "AssertUtils.h"


int ArgvProcessing( int argc, char** argv, FileStat* input_file,   const char* input_file_standart_address, 
                                           FileStat* output_file,  const char* output_file_standart_address ) {
    my_assert( argv,                         ASSERT_ERR_NULL_PTR );
    my_assert( input_file,                   ASSERT_ERR_NULL_PTR );
    my_assert( input_file_standart_address,  ASSERT_ERR_NULL_PTR );

    int opt = 0;
    const char* opts = "i:o:";

    while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
        switch ( opt ) {
            case 'i':
                input_file->address =  strdup( optarg );   break;
            case 'o':
                output_file->address = strdup( optarg );   break;
            default:
                fprintf( stderr, "Unknown option. Usage: %s [-i filename] [-o filename] \n", argv[0] );
                return 1;
        }
    }

    if ( argc == 1 ) {
        input_file->address  = strdup( input_file_standart_address  );
        output_file->address = strdup( output_file_standart_address );
    }

    return 0;
}


char* ReadToBuffer( FileStat* input_file ) {
    PRINT( COLOR_BRIGHT_YELLOW "In %s \n", __func__ )

    if ( input_file->size == 0 ) {
        input_file->size = DetermineFileSize( input_file->address );
    }

    char* buffer = ( char* ) calloc ( ( size_t ) input_file->size + 1, sizeof( *buffer ) );
    my_assert( buffer, ASSERT_ERR_NULL_PTR )

    FILE* file = fopen( input_file->address, "r" );
    my_assert( file, ASSERT_ERR_FAIL_OPEN )

    size_t result_of_read = fread( buffer, sizeof( char ), ( size_t )input_file->size, file );
    assert( result_of_read != 0 && "Fail read to buffer \n" );

    int result_of_fclose = fclose( file );
    assert( result_of_fclose == 0 && "Fail close file \n" );

    input_file->nLines = RowCounter( buffer );
    PRINT( COLOR_BRIGHT_YELLOW "Out %s \n", __func__ )

    return buffer;
}

size_t SplitIntoLines( StrPar* strings, char* buffer, size_t nLines ) {
    my_assert( strings, ASSERT_ERR_NULL_PTR );
    my_assert( buffer,  ASSERT_ERR_NULL_PTR );

    PRINT( COLOR_BRIGHT_YELLOW "In %s \n", __func__ )

    if ( nLines == 0 ) {
        nLines = RowCounter( buffer );
    }

    size_t line = 0;
    size_t actual_line = 0;
    strings[ actual_line ].ptr = buffer;
    strings[ actual_line ].len = 0;

    while ( *buffer != '\0' ) {
        if ( *buffer == '\n' ) {
            *buffer = '\0';

            if ( strings[ actual_line ].len > 0 ) {
                actual_line++;
            }

            strings[ actual_line ].ptr = buffer + 1;
            strings[ actual_line ].len = 0;

            line++;
        }
        else {
            strings[ actual_line ].len++;
        }

        buffer++;
    }

    if ( strings[ actual_line ].len == 0 && actual_line > 0 ) {
        actual_line--;
    }

    PRINT( COLOR_BRIGHT_YELLOW "Out %s\n", __func__ )

    return actual_line + 1;
}

size_t RowCounter( const char* buffer ) {
    my_assert( buffer, ASSERT_ERR_NULL_PTR );

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