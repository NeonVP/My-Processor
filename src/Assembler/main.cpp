#include "assembler.h"


int main( int argc, char** argv ) {
    Assembler_t assembler = {};

    ArgvProcessing( argc, argv, &( assembler.asm_file ), &( assembler.exe_file ) );

    PRINT( COLOR_BRIGHT_WHITE "FILES:\nfor input - %s\nfor output - %s\n", assembler.asm_file.address, assembler.exe_file.address );

    AsmCodeToByteCode( &assembler );

    OutputInFile( &assembler );
}