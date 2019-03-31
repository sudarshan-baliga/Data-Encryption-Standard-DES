#include "parser.h"
#include <iostream>
#include <string>
using namespace std;

char* toBits(string message)
{
    int msgLen = message.length();
    int numBits = msgLen * 8;
    char *bits = new char[numBits+1];
    for(int msgIdx = 0; msgIdx < msgLen; ++msgIdx) {
        for(int bitPos = 0; bitPos < 8; ++bitPos)
            bits[8*msgIdx + 7 - bitPos] = (
                ((message[msgIdx] & (1 << bitPos)) != 0) ? '1' : '0'
            );
    }
    bits[numBits] = '\0';
    return bits;
}