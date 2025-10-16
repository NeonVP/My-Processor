#ifndef ERRORS_H
#define ERRORS_H

#include "colors.h"

#ifdef _DEBUG           // TODO: write with &&
    #define my_assert(arg, err_code)                                                                                       \
        if ( !arg ) {                                                                                                      \
            fprintf( stderr, COLOR_RED "Error in function %s %s:%d: %s \n" COLOR_RESET,                                    \
                    __func__, __FILE__, __LINE__, error_message[ err_code ]);                                              \
            abort();                                                                                                       \
        }   ;

    #define PRINT(str, ...) fprintf( stderr, str COLOR_RESET, ##__VA_ARGS__ );

    #define ON_DEBUG(...) __VA_ARGS__
#else
    #define my_assert(arg, err_code) ((void) (arg));
    #define PRINT(str, ...)
    #define ON_DEBUG(...) 
#endif //_DEBUG

enum Errors {
    ASSERT_ERR_NONE = 0,
    ASSERT_ERR_NULL_PTR = 1,
    ASSERT_ERR_INFINITE_NUMBER = 2,
    ASSERT_ERR_FAIL_OPEN = 3,
    ASSERT_ERR_FAIL_READ = 4,
    ASSERT_ERR_FAIL_CLOSE = 5,
    ASSERT_ERR_FAIL_STAT = 6,
    ASSERT_ERR_FAIL_ALLOCATE_MEMORY = 7
};

extern const char* error_message[];
#endif //ERRORS_H