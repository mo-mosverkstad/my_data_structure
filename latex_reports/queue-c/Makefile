CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = main.o rawqueue.o queue.o arrayqueue.o bench.o
TARGET = main

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Pattern rule for compiling any .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
    
$(OBJ): $(HEADERS)

clean:
	rm -f $(OBJ) $(TARGET)
