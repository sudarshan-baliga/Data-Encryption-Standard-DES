#ifndef PARSER
#define PARSER

#include <iostream>

class Parser{
    public:
        int numBits;
        char* bits;
        void toBits(std::string message);
};

#endif