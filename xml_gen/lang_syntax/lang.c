#include "lang.h"

char* converting_c_syntax(C_KEYWORDS keyword){
    char *translated = malloc(sizeof(char) * MAX_LENGTH_OF_C_KEYWORD);
    switch (keyword) {
        case C_VOID:
            translated = "void";
            break;
        case C_INT:
            translated = "int";
            break;
        case C_DOUBLE:
            translated = "double";
            break;
        case C_LONG:
            translated = "long";
            break;
    }
    return translated;
}
