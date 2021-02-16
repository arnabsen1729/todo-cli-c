#include "commands.h"

#include "fileHandling.h"

void getToday(char dateTime[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateTime, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void cmdAddTodo(char **newTodos, int newCount) {
    if (newCount == 0) {
        printf("Error: Missing todo string. Nothing added!\n");
        return;
    }
    char todos[TODO_MAX_COUNT][TODO_MAX_SIZE];
    int count = todosFileCount(PENDING_TODOS_FILE);
    readTodos(todos, PENDING_TODOS_FILE);
    for (int index = 0; index < newCount; index++) {
        strcpy(todos[count + index], newTodos[index]);
        printf("Added todo: \"%s\"\n", todos[count + index]);
    }
    writeTodos(todos, count + newCount, PENDING_TODOS_FILE);
}

void cmdLs() {
    char todos[TODO_MAX_COUNT][TODO_MAX_SIZE];
    int count = todosFileCount(PENDING_TODOS_FILE);
    if (count == 0) {
        printf("There are no pending todos!\n");
        return;
    }
    readTodos(todos, PENDING_TODOS_FILE);
    for (int index = 0; index < count; index++) {
        printf("[%d] %s\n", (count - index), todos[count - index - 1]);
    }
}

void delItem(char arr[TODO_MAX_COUNT][TODO_MAX_SIZE], int index, int size) {
    for (int i = index; i < size - 1; i++) {
        strcpy(arr[index], arr[index + 1]);
    }
}
void cmdDelTodo(int todoIds[], int idCount) {
    int count = todosFileCount(PENDING_TODOS_FILE);
    if (idCount == 0) {
        printf("Error: Missing NUMBER for deleting todo.\n");
        return;
    }
    char todos[TODO_MAX_COUNT][TODO_MAX_SIZE];
    readTodos(todos, PENDING_TODOS_FILE);
    for (int id = 0; id < idCount; id++) {
        if ((todoIds[id] < 1) || (todoIds[id] > count)) {
            printf("Error: todo #%d does not exist. Nothing deleted.\n", todoIds[id]);
        } else {
            delItem(todos, todoIds[id] - 1, count);
            count--;
            printf("Deleted todo #%d\n", todoIds[id]);
        }
    }
    writeTodos(todos, count, PENDING_TODOS_FILE);
}

void cmdMarkDone(int todoIds[], int idCount) {
    if (idCount == 0) {
        printf("Error: Missing NUMBER for marking todo as done.\n");
        return;
    }

    char todos[TODO_MAX_COUNT][TODO_MAX_SIZE];
    int count = todosFileCount(PENDING_TODOS_FILE);
    readTodos(todos, PENDING_TODOS_FILE);

    for (int id = 0; id < idCount; id++) {
        if ((todoIds[id] < 1) || (todoIds[id] > count)) {
            printf("Error: todo #%d does not exist.\n", todoIds[id]);
        } else {
            char dateStr[20];
            getToday(dateStr);
            char completedTodoFmt[TODO_MAX_SIZE];
            sprintf(completedTodoFmt, "x %s %s", dateStr, todos[id]);
            appendTodo(completedTodoFmt, COMPLETED_TODOS_FILE);
            delItem(todos, todoIds[id] - 1, count);
            count--;
            printf("Marked todo #%d as done.\n", todoIds[id]);
        }
    }
    writeTodos(todos, count, PENDING_TODOS_FILE);
}

void cmdReport() {
    int pendingCount = todosFileCount(PENDING_TODOS_FILE);
    int completedCount = todosFileCount(COMPLETED_TODOS_FILE);
    char dateStr[20];
    getToday(dateStr);
    printf("%s Pending : %d Completed : %d\n", dateStr, pendingCount, completedCount);
}
