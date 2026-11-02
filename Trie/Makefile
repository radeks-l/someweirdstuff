
.PHONY: simple test trie

GTEST_INC:=/home/r.hrynda/APPS/googletest/include
GTEST_LIB:=/home/r.hrynda/APPS/googletest/lib

trie: main.cpp Trie.hpp
	g++ -g -O2 -pg -pedantic -std=c++11 main.cpp -o $@

test: test.cpp Trie.hpp
	g++ -g -pedantic -std=c++11 -I$(GTEST_INC) -L$(GTEST_LIB) test.cpp -o $@ -lgmock_main -lpthread

run_test: test
	./test

clean:
	rm trie core test

