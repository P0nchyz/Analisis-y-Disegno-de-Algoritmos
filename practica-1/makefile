# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Library files
LIB = lib/tiempo.c lib/BST.c lib/sorting/bubble.c lib/sorting/heap.c lib/sorting/insertion.c lib/sorting/merge.c lib/sorting/quick.c lib/sorting/selection.c lib/sorting/shell.c lib/sorting/tree.c

# Output executable name
TARGET = sort.out

all: $(TARGET) $(LIB)
	$(CC) -o $(TARGET) $(CGLAGS) main.c $(LIB)
