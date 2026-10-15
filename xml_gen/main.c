#include <stdlib.h>
#include <stdio.h>

#define MAX_PATH_LEN 100

typedef enum FileMode{
    READ,
    WRITE,
    APPEND
} FileMode;

typedef enum Language {
    C,
    CPP,
    CS,
    CSS,
    RS
} Language;

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


void file_formatting(FILE* fptr, Language lang) {
    char data[4096];
    while (fgets(data, sizeof(data), fptr) != NULL){
        switch (lang){
            case C:
                break;
            case CPP:
                break;
            case CS:
                break;
            case CSS:
                break;
            case RS:
                break;
        }
        fprintf(result, "%s\n", data);
    }
    fclose(source);
}

int main(void){
    FILE *source = open_file(READ, "test.txt");
    FILE *result = open_file(WRITE, "output.xml");

    
    int index = 1;

    if (source == NULL || result == NULL){
        printf("The file was not found\n");
        return 0;
    }
    else{
        file_formatting();
    }   

    return 0;
}
