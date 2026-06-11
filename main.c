#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file_io.h"
#include "text_ops.h"
#include "utils.h"
#include "history.h"

char *document = NULL;
TextHistory history;

int main(void) {
    InitHistory(&history);
    SaveState(&history, document);

    int command = 0;
    char fileName[100];

    while (true) {
        char *baseText = "> Choose the command:";
        printf("\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1. Append text symbols to the end",
               "2. Start the new line",
               "3. Use files to save the information",
               "4. Use files to load the information",
               "5. Print the current text to console",
               "6. Insert text at cursor (with replacement)",
               "7. Search",
               "8. Delete text at cursor",
               "9. Undo",
               "10. Redo",
               "11. Cut at cursor",
               "12. Paste at cursor",
               "13. Copy at cursor",
               "14. Set cursor position",
               "0. Exit");
        printf("%s\n> ", baseText);

        if (scanf("%d", &command) != 1) break;
        getchar();

        switch(command) {
            case 1:
                AppendText(&document);
                SaveState(&history, document);
                break;
            case 2:
                NewLine(&document);
                SaveState(&history, document);
                break;
            case 3:
                SaveFile(document, fileName);
                break;
            case 4:
                LoadFile(&document, fileName);
                break;
            case 5:
                PrintText(document);
                break;
            case 6:
                InsertText(&document);
                SaveState(&history, document);
                break;
            case 7:
                SearchText(document);
                break;
            case 8:
                DeleteText(&document);
                SaveState(&history, document);
                break;
            case 9:
                document = Undo(&history, document);
                break;
            case 10:
                document = Redo(&history, document);
                break;
            case 11:
                CutText(&document);
                SaveState(&history, document);
                break;
            case 12:
                PasteText(&document);
                SaveState(&history, document);
                break;
            case 13:
                CopyText(document);
                break;
            case 14:
                SetCursor();
                break;
            case 0:
                FreeClipboard();
                if (document) free(document);
                return 0;
            default:
                printf("> Command number is unknown\n");
        }
    }

    return 0;
}