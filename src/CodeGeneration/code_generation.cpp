#include "code_generation.h"

void ArgvProcessing( int argc, char** argv, CodeGenerator_t* generator ) {
    my_assert( argv,             ASSERT_ERR_NULL_PTR        )
    my_assert( generator,        ASSERT_ERR_NULL_PTR        )
    my_assert( isfinite( argc ), ASSERT_ERR_INFINITE_NUMBER )

    PRINT( COLOR_BRIGHT_YELLOW "In %s \n", __func__ )

    generator->input_file.address        = strdup( "./command_list.txt" );
    generator->enum_file.address         = strdup( "./include/enum.h" );
    generator->command_list_file.address = strdup( "./include/command_list.h" );

    int opt = 0;
    const char* opts = "i:o:";

    while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
        switch ( opt ) {
            case 'i':
                generator
        }
    }

    PRINT( COLOR_BRIGHT_YELLOW "Out %s \n", __func__ )
}

void GeneratorCtor( CodeGenerator_t* generator, int argc, char** argv ) {
    my_assert( generator, ASSERT_ERR_NULL_PTR );
    my_assert( argv,      ASSERT_ERR_NULL_PTR );


}

void GeneratorDtor( CodeGenerator_t* generator ) {
    my_assert( generator, ASSERT_ERR_NULL_PTR );

    free( generator->strings );
    generator->strings = NULL;

    free( generator->enum_file.address );
    generator->enum_file.address = NULL;

    free( generator->command_list_file.address );
    generator->command_list_file.address = NULL;

    free( generator->input_file.address );
    generator->input_file.address = NULL;
}
// -o имя папки, где создаются выходные файлы

void GeneratorReadToStrings( CodeGenerator_t* generator ) {
    my_assert( generator, ASSERT_ERR_NULL_PTR );

    char* buffer = ReadToBuffer(
}

GenerationStatus GeneratorEnumFormation( CodeGenerator_t* generator );
GenerationStatus GeneratorCommandListFormation( CodeGenerator_t* generator );
