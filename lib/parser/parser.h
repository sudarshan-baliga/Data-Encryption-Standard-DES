#ifndef PARSER
#define PARSER

#include <iostream>

class Parser{
    public:
        int numBits;
        bool* bits;
    private:
        void toBits(std::string message);
}