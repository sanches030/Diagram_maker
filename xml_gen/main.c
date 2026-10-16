#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lang_syntax/lang.h"
#include "nodes/node.h"

#define MAX_PATH_LEN 100

typedef enum FileMode{
    READ,
    WRITE,
    APPEND
} FileMode;

FILE *open_file(FileMode mode, const char *path) {
    FILE *fptr;
    switch (mode){
        case READ:
            fptr = fopen(path, "r");
            break;
        case WRITE:
            fptr = fopen(path, "w");
            break;
        case APPEND:
            fptr = fopen(path, "a");
            break;
    }
    return fptr;
}


void file_formatting(FILE* fptr, Language lang, Node* head) { // maiun formattign happens here
    char data[4096];
    while (fgets(data, sizeof(data), fptr) != NULL){
        switch (lang){
            case C: 
                break;
            case CPP:
                break;
            case CS:
                break;
            case RS:
                break;
            case PY:
                break;
        }
    }
}

Language language_recognition(char* path){
    const char *dot = strchr(path, '.');

    if (dot == NULL){
        return UNKNOWN;
    }

    const char *ext = dot + 1;

    Language lang;

    if (strcmp(ext, "c") == 0){
        lang = C;
    }
    else if (strcmp(ext, "cpp") == 0){
        lang = CPP;
    }
    else if (strcmp(ext, "cs") == 0){
        lang = CS;
    }
    else if (strcmp(ext, "rs") == 0){
        lang = RS;
    }
    else if (strcmp(ext, "py") == 0){
        lang = PY;
    }else{
        lang = UNKNOWN;
    }

    return lang;
}


int main(void){

    Node head = creating_node("idk yet");

    char *s = "text.cs";
    char *r = "output.xml";

    printf("THE LANG RECOGNIZED IS: %d\n", language_recognition(s));

    FILE *source = open_file(READ, "test.c");
    FILE *result = open_file(WRITE, "output.xml");

    int index = 1;

    if (source == NULL || result == NULL){
        printf("The file was not found\n");
        return 0;
    }

    fprintf(result, "<code>\n");

    //file_formatting();

    fprintf(result, "</code>\n");
    return 0;
}
