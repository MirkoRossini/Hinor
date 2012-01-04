VERSION=0.1

CC=gcc
LD=-lpthread
DEB=-g #-fpack-struct
FLAGS=-Wall -Wstrict-prototypes
kinor : main.o char_trie.o  test
	$(CC) $(FLAGS) $(LD) -o hinor main.o char_trie.o  -lpthread $(DEB)

test : tests.o char_trie.o 
	$(CC) $(FLAGS) -o tests/test tests/tests.o char_trie.o  $(DEB)

tests.o : tests/tests.c
	$(CC) $(FLAGS) -c tests/tests.c -o tests/tests.o $(DEB)

char_trie.o : char_trie.c
	$(CC) $(FLAGS)  -c char_trie.c  $(DEB)

#server.o : server.c
#	$(CC) $(FLAGS)  -c server.c  $(DEB)

main.o : main.c
	$(CC) $(FLAGS)  -c main.c  $(DEB)

clean:
	@rm -f kinor char_trie.o server.o tests/tests.o tests/test
