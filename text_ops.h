#ifndef TEXT_OPS_H
#define TEXT_OPS_H

// Глобальні змінні курсора
extern int cursorLine;
extern int cursorCol;

void SetCursor(void);
void NewLine(char** document);
void AppendText(char** document);
void PrintText(char* document);
void InsertText(char ** document);
void SearchText(char * document);
void DeleteText(char ** document);
void CopyText(char * document);
void PasteText(char ** document);
void CutText(char ** document);
void FreeClipboard(void);

#endif //TEXT_OPS_H