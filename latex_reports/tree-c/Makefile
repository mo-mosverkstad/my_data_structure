CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = 
TARGET = tree_benchmark
OBJS = main_new.o tree.o stack.o benchmark.o latex_output.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main_new.o: main_new.c benchmark.h
	$(CC) $(CFLAGS) -c main_new.c

tree.o: tree.c tree.h stack.h
	$(CC) $(CFLAGS) -c tree.c

stack.o: stack.c stack.h tree.h
	$(CC) $(CFLAGS) -c stack.c

benchmark.o: benchmark.c benchmark.h tree.h latex_output.h
	$(CC) $(CFLAGS) -c benchmark.c

latex_output.o: latex_output.c latex_output.h
	$(CC) $(CFLAGS) -c latex_output.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
