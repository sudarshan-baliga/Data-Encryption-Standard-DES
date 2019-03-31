#include <iostream>
#include <string.h>
#include "./lib/keygen/keygen.h"
#include "./lib/parser/parser.h"
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"
#define endl "\n";
using namespace std;
using namespace DES;

char* DesMachine(char *plainText, bool decipher)
{
    // steps:
    //generate the keys
    ull *keys = DESKeyGen::getKeys(1383827165325090801);
    // if deciphering reverse the keys
    if(decipher)
        reverseKeys(keys);
    // IP
    char *text = getPermutation(plainText, "initial");
    // 16 time fiestal round
    for (int i = 0; i < 15; i++)
    {
        text = DESround(text, Utils::numTobin(keys[i], 48), false);
        cout << "round " << i + 1 << " result " << text << endl;
    }
    //no left and right swap in final round
    text = DESround(text, Utils::numTobin(keys[15], 48), false);
    // FP
    text = getPermutation(text, "final");
    cout << "round 16 result " << text << endl;
    return text;
}

int main()
{
    char *plainText, *cipherText, *decipheredText;
    plainText = Utils::strTobin("sachinpr");
    cipherText = DesMachine(plainText, false);
    cout << "Deciphering" << endl;
    decipheredText = DesMachine(plainText, true);
    cout << decipheredText << endl;
}