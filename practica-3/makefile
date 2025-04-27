# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Library files
LIB = lib/huffman.c lib/binary.c

# Output executable name
TARGET = huffman.out

OUT_DIR = out

all: $(TARGET) $(OUT_DIR)

$(TARGET): main.c $(LIB)
	$(CC) -o $(TARGET) $(CFLAGS) main.c $(LIB)

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -dr out
	rm $(TARGET)
