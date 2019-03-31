boxDir=./lib/boxes
parserDir=./lib/parser
keygenDir=./lib/keygen
fns=./lib/DESfunctions

output: ./main.o $(parserDir)/parser.o $(boxDir)/boxes.o $(keygenDir)/keygen.o $(fns)/functions.o
	g++ main.o $(parserDir)/parser.o $(boxDir)/boxes.o $(keygenDir)/keygen.o $(fns)/functions.o -o output

functions: $(fns)/functions.cpp
	g++ -c $(fns)/functions.cpp

keygen: $(keygenDir)/keygen.cpp
	g++ -c $(keygenDir)/keygen.cpp

box: $(boxDir)/boxes.cpp
	g++ -c $(boxDir)/boxes.cpp

parser: $(parserDir)/parser.cpp
	g++ -c $(parserDir)/parser.cpp

main: main.cpp
	g++ -c main.cpp

clean:
	find . -name '*.o' -delete