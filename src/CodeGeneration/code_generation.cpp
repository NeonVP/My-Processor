#include "code_generation.h"
#include "AssertUtils.h"
#include "FileRWUtils.h"


void GeneratorCtor( CodeGenerator_t* generator, int argc, char** argv ) {
    my_assert( generator,        ASSERT_ERR_NULL_PTR        );
    my_assert( argv,             ASSERT_ERR_NULL_PTR        );
    my_assert( isfinite( argc ), ASSERT_ERR_INFINITE_NUMBER );

    PRINT_IN;
    
    ArgvProcessing( argc, argv, &( generator->input_file ),         "./commands.txt", 
                                &( generator->command_list_file ), "./include/command_list.h" );

    PRINT_OUT;
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

    char* buffer = ReadToBuffer( &( generator->input_file ) );

    generator->strings = ( StrPar* ) calloc ( generator->input_file.nLines, sizeof( *( generator->strings ) ) );

    SplitIntoLines( generator->strings, buffer, generator->input_file.nLines );
}

GenerationStatus GeneratorEnumFormation( CodeGenerator_t* generator );
GenerationStatus GeneratorCommandListFormation( CodeGenerator_t* generator );
