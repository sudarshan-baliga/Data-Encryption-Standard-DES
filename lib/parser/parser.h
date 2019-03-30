#ifndef PARSER
#define PARSER
#include <string>
class Parser{
    public:
        int numBits;
        char* bits;
        void toBits(std::string message);
};

#endif