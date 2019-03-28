#include "parser.h"
using namespace std;

void Parser::toBits(string message)
{
    int msgLen = message.length();
    numBits = msgLen * 8;
    bits = (bool *)malloc(numBits * sizeof(bool));
    for(int msgIdx = 0; msgIdx < msgLen; msgIdx++)
    {
        for(int bitPos = 0; bitPos < 8; bitPos++)
            bits[msgIdx + bitPos] = message[msgIdx] & (1 << bitPos);
    }
}