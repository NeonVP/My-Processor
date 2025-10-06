#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "common.h"

size_t lines_counter( const char* text );
off_t determining_the_file_size( const char* file_address );
void SplittingIntoLines( StrPar* strings, char* text, const size_t nLines );

void ReadingFile( FileStat* input_file, char** buffer );

#endif //FILE_PROCESSING_H