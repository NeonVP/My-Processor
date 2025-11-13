#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

#include "FileRWUtils.h"

struct CodeGenerator_t {
    FileStat input_file        = {};
    FileStat command_list_file = {};
    StrPar*  strings           = NULL;
};

enum GenerationStatus {
    FAIL    = 0,
    SUCCESS = 1
};

void GeneratorCtor( CodeGenerator_t* generator, int argc, char** argv );
void GeneratorDtor( CodeGenerator_t* generator );

void GeneratorReadToStrings( CodeGenerator_t* generator );
GenerationStatus GeneratorEnumFormation( CodeGenerator_t* generator );
GenerationStatus GeneratorCommandListFormation( CodeGenerator_t* generator );

#endif
