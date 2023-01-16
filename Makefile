
all: main 

main:
	g++ *.cc -o main -DNDEBUG -O5 -std=c++17 -lpthread -Wl,-no-as-needed
