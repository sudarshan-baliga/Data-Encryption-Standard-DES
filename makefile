boxDir=./lib/boxes
parserDir=./lib/parser

output:   parser main 
	g++ main.o parser.o boxes.o -o output
box: $(boxDir)/boxes.cpp
	g++ -c $(boxDir)/boxes.cpp
parser: $(parserDir)/parser.cpp
	g++ -c $(parserDir)/parser.cpp
main: main.cpp
	g++ -c main.cpp