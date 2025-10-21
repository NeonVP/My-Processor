#include "code_generation.h"

int main( int argc, char** argv ) {
    CodeGenerator_t generator = {};
    GeneratorCtor( &generator, argc, argv );

    GeneratorReadToStrings( &generator );

    GeneratorEnumFormation( &generator );
    GeneratorCommandListFormation( &generator );

    GeneratorDtor( &generator );
}
