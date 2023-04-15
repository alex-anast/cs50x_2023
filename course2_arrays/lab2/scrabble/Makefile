CC = clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

EXEC = scrabble

SRCS = $(EXEC).c
OBJS = $(SRCS:.c=.o)

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)
	rm -f $(EXEC).o *~

.PHONY : clean
clean :
	rm -f $(EXEC).o *~
