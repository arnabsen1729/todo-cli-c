// #include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "fileHandling.h"

char HELP_STRING[] = "Usage :-\n$ ./todo add \"todo item\"  # Add a new todo\n$ ./todo ls               # Show remaining todos\n$ ./todo del NUMBER       # Delete a todo\n$ ./todo done NUMBER      # Complete a todo\n$ ./todo help             # Show usage\n$ ./todo report           # Statistics";

//https://stackoverflow.com/questions/1442116

char **getArgs(char *argv[], int count) {
    char **args = malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) {
        args[i] = malloc(TODO_MAX_SIZE * sizeof(char));
        strcpy(args[i], argv[i + 2]);
    }
    return args;
}

int *convertInt(char *args[], int count) {
    int *intArgs = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        intArgs[i] = atoi(args[i]);
    }
    return intArgs;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("%s\n", HELP_STRING);
    } else {
        char command[10];
        strcpy(command, argv[1]);
        int argCount = argc - 2;
        char **args = getArgs(argv, argCount);
        if (strcmp(command, "add") == 0) {
            cmdAddTodo(args, argCount);
        } else if (strcmp(command, "ls") == 0) {
            cmdLs();
        } else if (strcmp(command, "del") == 0) {
            int *intArgs = convertInt(args, argCount);
            cmdDelTodo(intArgs, argCount);
        } else if (strcmp(command, "done") == 0) {
            int *intArgs = convertInt(args, argCount);
            cmdMarkDone(intArgs, argCount);
        } else if (strcmp(command, "report") == 0) {
            cmdReport();
        } else {
            printf("%s\n", HELP_STRING);
        }
    }
    return 0;
}
