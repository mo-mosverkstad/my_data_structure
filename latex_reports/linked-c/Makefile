CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = main.o linked.o bench.o
TARGET = main

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Pattern rule for compiling any .c file into .o
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
