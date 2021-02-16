#include "fileHandling.h"

int todosFileCount(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return 0;
    else {
        int count = 0;
        while (!feof(fp)) {
            if (fgetc(fp) == '\n') count++;
        }
        return count;
    }
}

void readTodos(char todos[TODO_MAX_COUNT][TODO_MAX_SIZE], char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return;
    else {
        int index = 0;
        while (!feof(fp)) {
            fgets(todos[index], sizeof(todos[index]), fp);
            // Remove \n from the line.
            todos[index][strcspn(todos[index], "\n")] = 0;
            index++;
        }
    }
    fclose(fp);
}

void writeTodos(char todos[TODO_MAX_COUNT][TODO_MAX_SIZE], int todosCount, char filename[]) {
    FILE *fp = fopen(filename, "w");
    for (int index = 0; index < todosCount; index++) {
        fputs(todos[index], fp);
        fputc('\n', fp);
    }
    fclose(fp);
}

void appendTodo(char todo[TODO_MAX_SIZE], char filename[]) {
    FILE *fp = fopen(filename, "a");
    fputs(todo, fp);
    fputc('\n', fp);
    fclose(fp);
}
