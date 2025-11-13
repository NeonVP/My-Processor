#ifndef FILERWUTILS_H
#define FILERWUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>

#include "AssertUtils.h"


struct FileStat {
    char* address = NULL;
    size_t nLines = 0;
    off_t  size   = 0;
};

struct StrPar{
    char* ptr = NULL;
    size_t len = 0;
};

int ArgvProcessing(int argc, char **argv, FileStat* input_file,  const char* input_file_standart_address,
                                          FileStat* output_file, const char* output_file_standart_address );

size_t RowCounter( const char* text );
off_t DetermineFileSize( const char* file_address );
size_t SplitIntoLines( StrPar* strings, char* text, const size_t nLines );

char* ReadToBuffer( FileStat* input_file );

#endif // FILERWUTILS_H