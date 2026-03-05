CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = main.o list_pq1.o list_pq2.o bst_heap.o tree_heap.o array_heap.o
TARGET = main

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Pattern rule for compiling any .c file into .o
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
