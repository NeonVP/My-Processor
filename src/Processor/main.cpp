#include "processor.h"

int main( int argc, char** argv ) {
    FileStat exe_file = {};
    ArgvProcessing( argc, argv, &exe_file );

    Processor_t processor = {};
    ProcCtor( &processor, 8, 5 );

    ExeFileToByteCode( &processor, &exe_file );

    int result = ByteCodeProcessing( &processor );

    ProcDtor( &processor );

    if ( result == 1 ) {    // TODO25: выводить, что неправильная работа проги
        return EXIT_FAILURE;
    }
    else {
        return EXIT_SUCCESS;
    }
}