#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_PATH_LEN 100

typedef enum FileMode{
    READ,
    WRITE,
    APPEND
} FileMode;

typedef enum Language{
    C,
    CPP,
    CS,
    RS,
    PY,
    UNKNOWN,
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


Language language_recognition(char* path){
    const char *dot = strrchr(path, '.');

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

typedef enum Type{
    //nested
    DECISION_START,
    DECISION_END,
    SUBPROCESS_START,
    SUBPROCESS_END,
    PROGRAM_START,
    PROGRAM_END,

    //un-nested
    PROCESS,
    IO,
} Type;

typedef struct Element{
    Type type;
    int depth;
    char text[2048];
} Element;

bool strong_contains(const char* base, const char* target){
    if (strstr(base, target) != NULL)
        return true;
    return false;
}

bool weak_contains(const char* base, const char* target){
    int t = strlen(target);
    for (int i = 0; i < strlen(target); ++i){
        for (int j = i; j < strlen(base); ++j){
            if (base[j] == target[i]){
                --target;
            }
        }
    }
    printf("target: %d\n", target);
    return t <= 0 ? false : true;
}


int read(Element *stack, FILE* source){
    if (source == NULL)
        return 0;

    char data[2048];
    int i = 0;
    unsigned int depth = 0;

    Type open_blocks[256];
    int block_top = 0;


    while (fgets(data, sizeof(data), source) != NULL){
        bool recognized = false;
        if (strong_contains(data, " = ")){
            recognized = true;

            int index = 0;
            bool found = false;

            for (int j = 0; j < strlen(data); ++j){
                if (data[j] != ' '){
                    found = true;
                }
                if (found){
                    stack[i].text[index++] = data[j]; 
                }
            }
            stack[i].text[index - 2] = '\0';
                
            stack[i].type = PROCESS;
            stack[i].depth = depth;
        }
        else if (strong_contains(data, "scanf(")){
            recognized = true;
            stack[i].type = IO;
            stack[i].depth = depth;
        } else if (strong_contains(data, "if (")){
            recognized = true;
            stack[i].type = DECISION_START;
            stack[i].depth = depth;
        
            open_blocks[block_top++] = DECISION_START;
            ++depth;
        }
        else if (strong_contains(data, "int main(")){
            recognized = true;
            stack[i].type = PROGRAM_START;
            stack[i].depth = depth;

            open_blocks[block_top++] = PROGRAM_START;
            ++depth;
        }
        else if (strchr(data, '}') != NULL) {
            if (block_top > 0) {
                recognized = true;
                Type opening = open_blocks[--block_top];

                depth--;

                stack[i].depth = depth;

                switch (opening) {
                    case DECISION_START:
                        stack[i].type = DECISION_END;
                        break;

                    case SUBPROCESS_START:
                        stack[i].type = SUBPROCESS_END;
                        break;

                    case PROGRAM_START:
                        stack[i].type = PROGRAM_END;
                        break;

                    default:
                        break;
                }
            }
        }
        if (recognized) {
            ++i;

            if (stack[i - 1].type == PROGRAM_END)
                break;
        }
    }

    return i;
}

void write(Element* stack, FILE* result, int size){
    if (result == NULL)
        return;

    for (int i = 0; i < size; ++i){
        for (int j = 0; j < stack[i].depth * 4; ++j)
            fputc(' ', result);

        switch (stack[i].type){
            case DECISION_START:
                printf("DECISION_START\n");
                fprintf(result, "%s%s%s", "<decision>", stack[i].text, "\n");
                break;
            case DECISION_END:
                printf("DECISION_END\n");
                fprintf(result, "%s", "</decision>\n");
                break;
            case SUBPROCESS_START:
                printf("SUBPROCESS_START\n");
                fprintf(result, "%s%s%s", "<subprocess>", stack[i].text, "\n");
                break;
            case SUBPROCESS_END:
                printf("SUBPROCESS_END\n");
                fprintf(result, "%s", "</subprocess>\n");
                break;
            case PROGRAM_START:
                printf("PROGRAM_START\n");
                fprintf(result, "%s%s%s", "<program>", stack[i].text, "\n");
                break;
            case PROGRAM_END:
                printf("PROGRAM_END\n");
                fprintf(result, "%s", "</program>\n");
                break;
            case PROCESS:
                printf("PROCESS\n");
                fprintf(result, "%s%s%s", "<process>", stack[i].text, "</process>\n");
                break;
            case IO:
                printf("IO\n");
                fprintf(result, "%s%s%s", "<io></io>", stack[i].text, "\n");
                break;
        }
    }
}

int main(void){

    char *s = "test.c";
    char *r = "output.xml";

    printf("THE LANG RECOGNIZED IS: %d\n", language_recognition(s));

    FILE *source = open_file(READ, s);
    FILE *result = open_file(WRITE, r);

    if (source == NULL || result == NULL){
        printf("The file was not found\n");
        return 0;
    }

    Element *stack = malloc(sizeof(Element) * 2048);
    int size = read(stack, source);
    write(stack, result, size);


    fclose(source);
    fclose(result);

    free(stack);
    return 0;

}
