CC = clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

all : colorize

colorize : colorize.o helpers.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	rm -f colorize.o helpers.o bmp.o *~

colorize.o: colorize.c bmp.h helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -f colorize.o helpers.o bmp.o smiley_colored.bmp
