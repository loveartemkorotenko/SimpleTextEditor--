#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitHistory(TextHistory *history) {
    for (int i = 0; i < MAX_HISTORY; i++) {
        history->states[i] = NULL;
    }
    history->current_index = -1;
    history->total_states = 0;
}

void SaveState(TextHistory *history, const char *current_document) {
    while (history->total_states - 1 > history->current_index) {
        free(history->states[history->total_states - 1]);
        history->states[history->total_states - 1] = NULL;
        history->total_states--;
    }

    char *copy = NULL;
    if (current_document != NULL) {
        copy = malloc(strlen(current_document) + 1);
        strcpy(copy, current_document);
    } else {
        copy = malloc(1);
        copy[0] = '\0';
    }

    if (history->total_states == MAX_HISTORY) {
        free(history->states[0]);
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            history->states[i] = history->states[i + 1];
        }
        history->states[MAX_HISTORY - 1] = copy;
    } else {
        history->current_index++;
        history->states[history->current_index] = copy;
        history->total_states++;
    }
}

char* Undo(TextHistory *history, char *current_document) {
    if (history->current_index > 0) {
        history->current_index--;
        char *prev = history->states[history->current_index];
        char *restored = malloc(strlen(prev) + 1);
        strcpy(restored, prev);
        free(current_document);
        printf("> Undo successful\n");
        return restored;
    } else if (history->current_index == 0) {
        history->current_index--;
        free(current_document);
        printf("> Undo successful\n");
        return NULL;
    }
    printf("> Nothing to undo\n");
    return current_document;
}

char* Redo(TextHistory *history, char *current_document) {
    if (history->current_index < history->total_states - 1) {
        history->current_index++;
        char *next = history->states[history->current_index];
        char *restored = malloc(strlen(next) + 1);
        strcpy(restored, next);
        free(current_document);
        printf("> Redo successful\n");
        return restored;
    }
    printf("> Nothing to redo\n");
    return current_document;
}