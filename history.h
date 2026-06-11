#ifndef HISTORY_H
#define HISTORY_H

#define MAX_HISTORY 5

typedef struct {
    char *states[MAX_HISTORY];
    int current_index;
    int total_states;
} TextHistory;

void InitHistory(TextHistory *history);
void SaveState(TextHistory *history, const char *current_document);
char* Undo(TextHistory *history, char *current_document);
char* Redo(TextHistory *history, char *current_document);

#endif //HISTORY_H