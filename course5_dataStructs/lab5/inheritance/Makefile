CC = gcc
CFLAGS = -Wall -Werror -Wextra -ggdb3 -O0

inheritance: inheritance.o
	$(CC) $(CFLAGS) -o inheritance inheritance.o

inheritance.o: inheritance.c
	$(CC) $(CFLAGS) -c inheritance.c

clean:
	rm -f inheritance inheritance.o
