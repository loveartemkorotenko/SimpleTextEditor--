//
// Created by akims on 10.06.2026.
//

#include "file_io.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void SaveFile(char * document, char * fileName) {\
    printf("%s", "> Enter the file name for saving: " );
    scanf("%s", fileName);
    if (document != NULL) {
        FILE * file =  fopen(fileName, "w");
        if (file != NULL) {
            fprintf(file, "%s", document);
            fclose(file);
            printf( "%s", "> Text has been saved successfully");
        }
        else {
            printf("%s", "File doesn't exist or corrupted");
        }
    }
}


void LoadFile(char ** document, char * fileName) {
    printf("%s", "> Enter the file name for loading: " );
    scanf("%s", fileName);
    FILE * file =  fopen(fileName, "r");
    if (file != NULL) {
        free(*document);
        *document = ReadText(file);
        fclose(file);
        printf("\n%s", "> Text has been loaded successfully ");
    }
    else {
        printf("\n> File doesn't exist or corrupted\n");
        if (*document != NULL) {
            free(*document);
            *document = NULL;
        }
    }
}
