#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
char * ReadText(FILE * source);
char *document = NULL;

int main(void) {
    constexpr int CommandNum = 7;
    char *baseText = "> Choose the command: ";
    int command;
    char * appendText;
    char fileName[100];
    bool fileExist = false;
    while (true) {
        printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "1. Append text symbols to the end ",
            "2. Start the new line ", "3. Use files to load the information", "4. Use files to save the information",
            "5. Print the current text to console", "6. Insert the text by line and symbol index",
            "7. Search (please note that the text can be found more than once) ", "");
        printf("%s\n>", baseText);
        scanf("%d", &command);
        getchar();
        system("cls");
        switch(command) {
            case 1:
                printf("%s", "> Enter text to append: ");
                char *newText = ReadText(stdin);
                if (document == NULL) {
                    document = newText;
                }
                else {
                    int newSize = strlen(newText) + strlen(document);
                    document = realloc(document, newSize + 1);
                    strcat(document, newText);
                    free(newText);
                }
                break;
            case 2:
                printf("%s\n", "> New line is started");
                if (document != NULL) {
                    int zeroIndex = strlen(document);
                    document = realloc(document, zeroIndex + 2);
                    document[zeroIndex] = '\n';
                    document[zeroIndex + 1] = '\0';
                }
                else {
                    document = malloc(sizeof(char) * 2);
                    document[0] = '\n';
                    document[1] = '\0';
                }
                break;
            case 3:
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
                break;
            case 4:
                printf("%s", "> Enter the file name for loading: " );
                scanf("%s", fileName);
                FILE * file =  fopen(fileName, "r");
                if (file != NULL) {
                    free(document);
                    document = ReadText(file);
                    fclose(file);
                    printf("\n%s", "> Text has been loaded successfully ");
                }
                else {
                    printf("\n%s", "File doesn't exist or corrupted");
                }
                break;
            case 5:
                if (document != NULL) {
                    printf("%s", document);
                }
                else {
                    printf("\n%s", "Text doesn't exist or corrupted");
                }
                break;
            case 6:
                printf("\n%s\n>", "Choose line and index:");
                int targetLine, targetIndex;
                scanf("%d %d", &targetLine, &targetIndex);
                getchar();
                if (document == NULL) {
                    printf("Document is empty.\n");
                    break;
                }
                int absoluteIndex = 0;
                int currentLine = 0;
                while (document[absoluteIndex] != '\0' && currentLine < targetLine) {
                    if (document[absoluteIndex] == '\n') {
                        currentLine++;
                    }
                    absoluteIndex++;
                }

                int currentSymbol = 0;
                while (document[absoluteIndex] != '\0' && document[absoluteIndex] != '\n' && currentSymbol < targetIndex) {
                    absoluteIndex++;
                    currentSymbol++;
                }

                printf("\n%s\n", "> Enter text to insert: ");
                char *insertText = ReadText(stdin);
                int oldLen = strlen(document);
                int insertLen = strlen(insertText);
                char *newDocument = malloc(oldLen + insertLen + 1);
                int j = 0;
                for (int i = 0; i < absoluteIndex; i++) {
                    newDocument[j] = document[i];
                    j++;
                }

                for (int i = 0; i < insertLen; i++) {
                    newDocument[j] = insertText[i];
                    j++;
                }
                for (int i = absoluteIndex; i <= oldLen; i++) {
                    newDocument[j] = document[i];
                    j++;
                }
                free(document);
                document = newDocument;
                free(insertText);
                break;
            case 7:
                printf("\n%s>", "> Enter text to search:");
                char * searchText = ReadText(stdin);
                if (document != NULL) {
                    char *currentPos = document;
                    char *foundPos;
                    bool found = false;
                    while ((foundPos = strstr(currentPos, searchText)) != NULL) {
                        found = true;
                        int currentLine = 0;
                        int currentCol = 0;
                        for (char *ptr = document; ptr < foundPos; ptr++) {
                            if (*ptr == '\n') {
                                currentLine++;
                                currentCol = 0;
                            } else {
                                currentCol++;
                            }
                        }
                        printf("> Text is present in this position: %d %d\n", currentLine, currentCol);

                        currentPos = foundPos + strlen(searchText);
                    }
                    if (found == false) {
                        printf("> Text not found\n");
                    }
                }
                free(searchText);
                break;
            case 0:
                return false;
                break;
            default:
                printf("Command number %d\n is unknown", CommandNum);
        }
    }

    return 0;
}

//
// Created by akims on 26.05.2026.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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