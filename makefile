boxDir=./lib/boxes
parserDir=./lib/parser
keygenDir=./lib/keygen
output: ./main.o $(parserDir)/parser.o $(boxDir)/boxes.o $(keygenDir)/keygen.o
	g++ main.o $(parserDir)/parser.o $(boxDir)/boxes.o $(keygenDir)/keygen.o -o output

keygen: $(keygenDir)/keygen.cpp
	g++ -c $(keygenDir)/keygen.o

box: $(boxDir)/boxes.cpp
	g++ -c $(boxDir)/boxes.cpp

parser: $(parserDir)/parser.cpp
	g++ -c $(parserDir)/parser.cpp

main: main.cpp
	g++ -c main.cpp

clean:
	find . -name '*.o' -delete