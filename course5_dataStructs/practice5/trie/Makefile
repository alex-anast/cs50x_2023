CC = clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

all : trie

trie : trie.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
	rm -f trie.o *~

trie.o: trie.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -f trie.o *~
