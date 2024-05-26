CC=clang
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
OBJS=graph.o stack.o path.o tsp.o
HEAD=graph.h stack.h path.h
EXEC=tsp

.PHONY: clean format scan-build

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

graph.o: graph.c graph.h 
	$(CC) $(CFLAGS) -c $< -o $@

stack.o: stack.c stack.h 
	$(CC) $(CFLAGS) -c $< -o $@

path.o: path.c graph.h stack.h path.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) *.o

scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]

