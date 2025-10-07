// FIXME: разнести файлы, архитектуру

#include "processor.h"

struct Processor_t {
    Stack_t stk = {};
    int byte_code[100] = {};
    size_t instruction_ptr = 0;
    // StackData_t regs[8] = {};            // TODO: add registers, PUSHR, POPR
};

void ProcCtor( Processor_t* proc );
void ExeFileProcessing( Processor_t* proc, FileStat* file );
void ArgvProcessing( int argc, char** argv, FileStat* input_file );

int main( int argc, char** argv ) {
    FileStat input_file = {};
    ArgvProcessing( argc, argv, &input_file );

    Processor_t proc = {};
    ProcCtor( &proc );
    fprintf( stderr, "ProcCtor \n" );

    ExeFileProcessing( &proc, &input_file );
}

void ProcCtor( Processor_t* proc ) {         // TODO: more commands ( function for function )
    StackCtor( &proc->stk, 10 );       // magic number
}

void ArgvProcessing( int argc, char** argv, FileStat* input_file ) {                // TODO: conditional compilated for assert
    assert( argv != NULL );
    assert( input_file != NULL );

    input_file->address = "./byte-code.txt";    // TODO: in default

    int opt = 0;
    const char* opts = "i:";

    while ( ( opt = getopt( argc, argv, opts ) ) != -1 ) {
        switch ( opt ) {
            case 'i':
                input_file->address = strdup( optarg );
                break;

            default:
                break;
        }
    }
}

void ExeFileProcessing( Processor_t* proc, FileStat* file ) {       // TODO: rename
    file->size = DetermineFileSize( file->address );
    char* buffer = NULL;
    fprintf( stderr, "In %s \n", __func__ );

    ReadToBuffer( file, &buffer );

    sscanf( buffer, "%d", &proc->instruction_ptr );

    size_t counter = 0;
    int num = 0;

    while ( sscanf( buffer, "%d", &num ) == 1 ) {
        proc->byte_code[ counter++ ] = num;
        buffer += 1;
        fprintf( stderr, "%d ", num );
    }

    fprintf( stderr, "\n" );

    free( buffer );      // FIXME: save old address to buffer
}
