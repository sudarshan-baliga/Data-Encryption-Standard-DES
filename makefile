boxDir=./lib/boxes
keygenDir=./lib/keygen
fns=./lib/DESfunctions
utils=./lib/utils

output: ./main.o $(boxDir)/boxes.o $(keygenDir)/keygen.o $(fns)/functions.o $(utils)/utils.o
	g++ main.o $(boxDir)/boxes.o $(keygenDir)/keygen.o $(fns)/functions.o $(utils)/utils.o -o output

utils: $(utils)/utils.cpp
	g++ -c $(utils)/utils.cpp

functions: $(fns)/functions.cpp
	g++ -c $(fns)/functions.cpp

keygen: $(keygenDir)/keygen.cpp
	g++ -c $(keygenDir)/keygen.cpp

box: $(boxDir)/boxes.cpp
	g++ -c $(boxDir)/boxes.cpp

main: main.cpp
	g++ -c main.cpp

clean:
	find . -name '*.o' -delete