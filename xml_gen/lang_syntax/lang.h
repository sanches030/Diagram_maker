#ifndef LANGUAGE_SYNTAX
#define LANGUAGE_SYNTAX

#include <stdlib.h>

#define MAX_LENGTH_OF_C_KEYWORD 15
typedef enum C_KEYWORDS{
    C_VOID,
    C_INT,
    C_DOUBLE,
    C_LONG
} C_KEYWORDS;

char* converting_c_syntax(C_KEYWORDS keyword);


#endif
