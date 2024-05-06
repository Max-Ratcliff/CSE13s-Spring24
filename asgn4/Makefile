CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -g
LFLAGS =
EXEC = xd
HEADERS = 

all: $(EXEC)

$(EXEC): $(EXEC).o xd.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
