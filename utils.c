//
// Created by akims on 26.05.2026.
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * ReadText(FILE * source) {
    char temp[128];
     int capacity = 128;
    char *mainBuffer = malloc(128 * sizeof(char));
    mainBuffer[0] = '\0';
    while (true) {
        char * info = fgets(temp, 127, source);
        if (info == NULL) {
            break;
        }
        char * prt = strchr(temp, '\n');
        if (prt !=NULL) {
            *prt = '\0';
        }
        int usedInBuffer = strlen(temp);
        if ((strlen(mainBuffer) + usedInBuffer + 1) > capacity) {
            mainBuffer = realloc(mainBuffer, (capacity*2) +1);
            capacity = (2 * capacity) + 1;
        }
        strcat(mainBuffer, temp);
        if (prt != NULL) {
            break;
        }
    }
    return mainBuffer;
}

