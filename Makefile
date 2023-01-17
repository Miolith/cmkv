
all: main 

main:
	g++ *.cc -o main -DNDEBUG -O5 -std=c++17 -lpthread -Wl,--no-as-needed

test: main
	TESTSUITE=1 ./main

.PHONY: main test
