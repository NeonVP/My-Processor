#include "file_processing.h"

void ReadingFile( FileStat* input_file, char** buffer ) {        // TODO: check for buffer, determening size if size = 0
    fprintf( stderr, "In %s \n", __func__ );

    if ( *buffer == NULL ) {
        if ( input_file->size == 0 ) {
            input_file->size = determining_the_file_size( input_file->address );
        }

        *buffer = ( char* ) calloc ( ( size_t )input_file->size, sizeof( char ) );
        if ( buffer == NULL ) {
            fprintf( stderr, "Error in allocate data for buffer \n" );
            abort();
        }
    }

    FILE* file = fopen( input_file->address, "r" );
    assert( file != NULL );
    fprintf( stderr, "after opening file \n" );

    size_t result_of_read = fread( *buffer, sizeof( char ), ( size_t )input_file->size, file );
    assert( result_of_read   != 0 );

    fprintf( stderr, "%s \n", buffer );

    int result_of_fclose = fclose( file );
    assert( result_of_fclose == 0 );

    input_file->nLines = lines_counter( *buffer );
    assert( input_file->nLines > 0 );
}

size_t lines_counter( const char* text ) {
    assert( text != NULL );

    size_t cnt = 0;

    while ( *text != '\0' ) {
        if ( *text == '\n' && *( text + 1 ) != '\n' )  cnt++;

        text++;
    }

    return cnt;
}

off_t determining_the_file_size( const char* file_address ) {
    struct stat file_stat;
    int check_stat = stat( file_address, &file_stat );
    assert( check_stat == 0 );

    return file_stat.st_size;
}

void SplittingIntoLines( StrPar* strings, char* text, const size_t nLines ) {
    assert( strings != NULL );
    assert( text    != NULL );
    assert( nLines   > 0    );

    for ( size_t i = 0; i < nLines; i++ ) {
        strings[i].ptr = text;

        while ( *text != '\n' ) {
            strings[i].len++;
            text++;
        }

        *text = '\0';
        text++;
    }

    fprintf( stderr, "End of splitting into lines\n" );
}