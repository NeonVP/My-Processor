#include "processor.h"      // TODO: massive of struct for Processor command

int main( int argc, char** argv ) {
    FileStat exe_file = {};
    ArgvProcessing( argc, argv, &exe_file );

    Processor_t processor = {};
    // processor.stk = { INIT( stk ) };
    // processor.refund_stk = { INIT( refund_stk ) };
    ProcCtor( &processor, 8, 5 );

    ExeFileToByteCode( &processor, &exe_file );

    int result = ByteCodeProcessing( &processor );

    ProcDtor( &processor );

    if ( result == 1 ) {
        fprintf( stderr, COLOR_BRIGHT_RED "Incorrect processor operation \n" );
        return EXIT_FAILURE;
    }
    else {
        return EXIT_SUCCESS;
    }
}