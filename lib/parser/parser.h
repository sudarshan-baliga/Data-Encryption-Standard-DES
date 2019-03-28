#ifndef PARSER
#define PARSER

#include <iostream>

class Parser{
    public:
        int numBits;
        bool* bits;
        void toBits(std::string message);
};

#endif