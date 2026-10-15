#include <stdlib.h>
#include <stdio.h>

#define MAX_PATH_LEN 100

int main(void){
    printf("Plese enter path to the file: ");
    char *path = malloc(sizeof(char) * MAX_PATH_LEN);
    scanf("%99s", path);

    FILE *fptr;

    fptr = fopen(path, "r");
    char data[100];

    if (fptr == NULL){
        printf("The file was not found\n");
        return 0;
    }
    else{
        printf("The data in that file looks like that: \n");

        while (fgets(data, 100, fptr) != NULL){
            printf("%s", data);
        }
        fclose(fptr);
    }   

    free(path);
    return 0;
}
