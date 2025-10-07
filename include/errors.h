#ifndef ERRORS_H
#define ERRORS_H

#include "colors.h"

#ifdef _DEBUG
    #define my_assert(arg, err_code)                                                                                       \
        if ( !arg ) {                                                                                                      \
            fprintf( stderr, COLOR_RED "Error in function %s %s:%d: %s \n" COLOR_RESET,                                    \
                    __func__, __FILE__, __LINE__, error_message[ err_code ]);                                               \
            abort();                                                                                                       \
        }

    #define PRINT(str, ...) fprintf( stderr, COLOR_BRIGHT_CYAN str COLOR_RESET, ##__VA_ARGS__ );
#else
    #define my_assert(arg, err_code)
    #define PRINT(str, ...)
#endif //_DEBUG

enum Errors {
    ERR_NONE = 0,
    ERR_NULL_PTR = 1,
    ERR_INFINITE_NUMBER = 2,
    ERR_FAIL_OPEN = 3,
    ERR_FAIL_READ = 4,
    ERR_FAIL_CLOSE = 5,
    ERR_FAIL_STAT = 6
};

extern const char* error_message[];

#endif //ERRORS_H