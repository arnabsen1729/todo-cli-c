#include <stdio.h>
#include <string.h>

#define PENDING_TODOS_FILE "todo.txt"
#define COMPLETED_TODOS_FILE "done.txt"
#define TODO_MAX_SIZE 200
#define TODO_MAX_COUNT 200

int todosFileCount(char[]);
void readTodos(char[TODO_MAX_COUNT][TODO_MAX_SIZE], char[]);
void writeTodos(char[TODO_MAX_COUNT][TODO_MAX_SIZE], int, char[]);
void appendTodo(char[TODO_MAX_SIZE], char[]);
