#ifndef FILERWUTILS_H
#define FILERWUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"
#include "errors.h"

#ifdef _ASM
#define ON_ASM(...) __VA_ARGS__
#else
#define ON_ASM(...)
#endif

void ArgvProcessing( int argc, char** argv, ON_ASM( FileStat* asm_file, ) FileStat* exe_file );

size_t RowCounter( const char* text );
off_t DetermineFileSize( const char* file_address );
void SplitIntoLines( StrPar* strings, char* text, const size_t nLines );

char* ReadToBuffer( FileStat* input_file );

#endif // FILERWUTILS_H