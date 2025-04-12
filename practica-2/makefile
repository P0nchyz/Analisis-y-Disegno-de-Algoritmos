# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Library files
LIB = lib/tiempo.c lib/BST.c lib/searching/searching.c lib/searching/thread_searching.c

# Output executable
TARGET = search.out

all: main.c $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LIB)
