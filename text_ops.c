#include "text_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

char *clipboard = NULL;
int cursorLine = 0;
int cursorCol = 0;

void FreeClipboard(void) {
    if (clipboard) {
        free(clipboard);
        clipboard = NULL;
    }
}

void SetCursor(void) {
    printf("\n> Enter line and index for cursor: ");
    scanf("%d %d", &cursorLine, &cursorCol);
    getchar();
    printf("> Cursor moved to line %d, index %d\n", cursorLine, cursorCol);
}

int GetAbsoluteIndex(char *document, int targetLine, int targetIndex) {
    if (!document) return -1;
    int absoluteIndex = 0;
    int currentLine = 0;
    while (document[absoluteIndex] != '\0' && currentLine < targetLine) {
        if (document[absoluteIndex] == '\n') currentLine++;
        absoluteIndex++;
    }
    int currentSymbol = 0;
    while (document[absoluteIndex] != '\0' && document[absoluteIndex] != '\n' && currentSymbol < targetIndex) {
        absoluteIndex++;
        currentSymbol++;
    }
    if (currentLine < targetLine || currentSymbol < targetIndex) return -1;
    return absoluteIndex;
}

void AppendText(char** document) {
    printf("%s", "> Enter text to append: ");
    char *newText = ReadText(stdin);
    if (*document == NULL) {
        *document = newText;
    } else {
        int newSize = strlen(newText) + strlen(*document);
        *document = realloc(*document, newSize + 1);
        strcat(*document, newText);
        free(newText);
    }
}

void NewLine(char** document) {
    printf("%s\n", "> New line is started");
    if (*document != NULL) {
        int zeroIndex = strlen(*document);
        *document = realloc(*document, zeroIndex + 2);
        (*document)[zeroIndex] = '\n';
        (*document)[zeroIndex + 1] = '\0';
    } else {
        *document = malloc(2);
        (*document)[0] = '\n';
        (*document)[1] = '\0';
    }
    cursorLine++;
    cursorCol = 0;
}

void PrintText(char* document) {
    if (document != NULL) {
        printf("\n--- DOCUMENT ---\n");
        printf("%s\n", document);
        printf("----------------\n");
        printf("> Cursor is currently at Line: %d, Index: %d\n", cursorLine, cursorCol);
    } else {
        printf("\n> Text doesn't exist or empty\n");
    }
}

void InsertText(char ** document) {
    if (*document == NULL) {
        printf("> Document is empty. Use append first.\n");
        return;
    }

    int absoluteIndex = GetAbsoluteIndex(*document, cursorLine, cursorCol);
    if (absoluteIndex == -1) {
        printf("> Cursor is out of bounds!\n");
        return;
    }

    printf("> Enter text to insert at cursor: ");
    char *insertText = ReadText(stdin);

    int mode;
    printf("> Choose mode (0 - insert, 1 - replacement): ");
    scanf("%d", &mode);
    getchar();

    int oldLen = strlen(*document);
    int insertLen = strlen(insertText);

    if (mode == 1) {
        int charsToReplace = insertLen;
        if (absoluteIndex + charsToReplace > oldLen) charsToReplace = oldLen - absoluteIndex;

        char *newDocument = malloc(oldLen + insertLen - charsToReplace + 1);
        strncpy(newDocument, *document, absoluteIndex);
        strcpy(newDocument + absoluteIndex, insertText);
        strcpy(newDocument + absoluteIndex + insertLen, *document + absoluteIndex + charsToReplace);

        free(*document);
        *document = newDocument;
    } else {
        char *newDocument = malloc(oldLen + insertLen + 1);
        strncpy(newDocument, *document, absoluteIndex);
        strcpy(newDocument + absoluteIndex, insertText);
        strcpy(newDocument + absoluteIndex + insertLen, *document + absoluteIndex);

        free(*document);
        *document = newDocument;
    }

    cursorCol += insertLen;
    free(insertText);
}

void DeleteText(char ** document) {
    if (*document == NULL) return;

    printf("\n> Enter number of symbols to delete from cursor: ");
    int numSymbols;
    scanf("%d", &numSymbols);
    getchar();

    int absoluteIndex = GetAbsoluteIndex(*document, cursorLine, cursorCol);
    if (absoluteIndex == -1) {
        printf("> Cursor is out of bounds!\n");
        return;
    }

    int oldLen = strlen(*document);
    if (absoluteIndex + numSymbols > oldLen) numSymbols = oldLen - absoluteIndex;

    char *newDocument = malloc(oldLen - numSymbols + 1);
    strncpy(newDocument, *document, absoluteIndex);
    strcpy(newDocument + absoluteIndex, *document + absoluteIndex + numSymbols);

    free(*document);
    *document = newDocument;
}

void CopyText(char * document) {
    if (document == NULL) return;

    printf("\n> Enter number of symbols to copy from cursor: ");
    int numSymbols;
    scanf("%d", &numSymbols);
    getchar();

    int absoluteIndex = GetAbsoluteIndex(document, cursorLine, cursorCol);
    if (absoluteIndex == -1) {
        printf("> Cursor is out of bounds!\n");
        return;
    }

    int oldLen = strlen(document);
    if (absoluteIndex + numSymbols > oldLen) numSymbols = oldLen - absoluteIndex;

    FreeClipboard();
    clipboard = malloc(numSymbols + 1);
    strncpy(clipboard, document + absoluteIndex, numSymbols);
    clipboard[numSymbols] = '\0';
    printf("> Copied to clipboard\n");
}

void CutText(char ** document) {
    CopyText(*document);

    if (clipboard && *document) {
        int numSymbols = strlen(clipboard);
        int absoluteIndex = GetAbsoluteIndex(*document, cursorLine, cursorCol);

        int oldLen = strlen(*document);
        char *newDocument = malloc(oldLen - numSymbols + 1);
        strncpy(newDocument, *document, absoluteIndex);
        strcpy(newDocument + absoluteIndex, *document + absoluteIndex + numSymbols);

        free(*document);
        *document = newDocument;
        printf("> Text cut successfully\n");
    }
}

void PasteText(char ** document) {
    if (!clipboard) {
        printf("> Clipboard is empty\n");
        return;
    }

    if (*document == NULL) {
        *document = malloc(strlen(clipboard) + 1);
        strcpy(*document, clipboard);
        return;
    }

    int absoluteIndex = GetAbsoluteIndex(*document, cursorLine, cursorCol);
    if (absoluteIndex == -1) {
        printf("> Cursor is out of bounds!\n");
        return;
    }

    int oldLen = strlen(*document);
    int clipLen = strlen(clipboard);
    char *newDocument = malloc(oldLen + clipLen + 1);

    strncpy(newDocument, *document, absoluteIndex);
    strcpy(newDocument + absoluteIndex, clipboard);
    strcpy(newDocument + absoluteIndex + clipLen, *document + absoluteIndex);

    free(*document);
    *document = newDocument;

    cursorCol += clipLen;
}

void SearchText(char * document) {
    printf("\n> Enter text to search: ");
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
}