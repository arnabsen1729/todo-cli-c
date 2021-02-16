CC=gcc
FILE=commands.c fileHandling.c main.c
OBJ=todo

compile:
	$(CC) $(FILE) -o $(OBJ)
