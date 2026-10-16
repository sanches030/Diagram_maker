#ifndef LANGUAGE_SYNTAX
#define LANGUAGE_SYNTAX

#include "../nodes/node.h"
#include <stdlib.h>
#include <string.h>

typedef enum Language {
    C,
    CPP,
    CS,
    RS,
    PY,
    UNKNOWN
} Language;



//for c
NodeType c_recognition(char[] data){
    if (strstr(data, "scanf")){
        return NodeType::NODE_IO;
    }else{
        return NodeType::NODE_PROCESS;
    }

}



#endif
