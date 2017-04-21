CFLAGS=-ggdb -std=c++11 -Wall

all: directoryEntry.x

directoryEntry.x: main.o lex.o directoryEntry.o token.o directoryNode.o
	g++ $(CFLAGS) main.o lex.o directoryEntry.o token.o directoryNode.o -o directoryEntry.x

main.o: main.cpp lex.o token.o directoryNode.o directoryEntry.o
	g++ $(CFLAGS) -c main.cpp -o main.o

lex.o: lex.cpp lex.hpp
	g++ $(CFLAGS) -c lex.cpp -o lex.o

directoryEntry.o: directoryEntry.cpp directoryEntry.hpp directoryNode.hpp
	g++ $(CFLAGS) -c directoryEntry.cpp -o directoryEntry.o

directoryNode.o: directoryNode.cpp directoryNode.hpp
	g++ $(CFLAGS) -c directoryNode.cpp -o directoryNode.o

token.o: token.cpp token.hpp
	g++ $(CFLAGS) -c token.cpp -o token.o

run:
	make all
	./directoryEntry.x
