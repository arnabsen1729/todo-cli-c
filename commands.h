#include <time.h>

#include "fileHandling.h"

void cmdAddTodo(char**, int);
void cmdLs();
void delItem(char[TODO_MAX_COUNT][TODO_MAX_SIZE], int, int);
void cmdDelTodo(int[], int);
void cmdMarkDone(int[], int);
void cmdReport();
