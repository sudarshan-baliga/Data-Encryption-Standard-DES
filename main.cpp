#include <iostream>
#include <string.h>
#include "./lib/keygen/keygen.h"
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"
#define endl "\n";
using namespace std;
using namespace DES;

char* DesMachine(char *inText, bool decipher)
{
    // steps:
    //generate the keys
    ull *keys = DESKeyGen::getKeys(1383827165325090801);
    // if deciphering reverse the keys
    if(decipher)
        reverseKeys(keys);
    // IP
    char *text = getPermutation(inText, "initial");
    // 16 time fiestal round
    for (int i = 0; i < 16; i++)
    {
        text = DESround(text, Utils::numTobin(keys[i], 48));
        cout << "round " << i + 1 << " result " << text << endl;
    }
    // swapping left and right part
    char *leftPart = Utils::substr(text, 0, 32);
    char *rightPart = Utils::substr(text, 32, 32);
    strcpy(text, rightPart);
    strcpy(text+32, leftPart);

    // FP
    text = getPermutation(text, "final");
    cout << "round 16 result " << text << endl;
    return text;
}

int main()
{
    char *plainText, *cipherText, *decipheredText;
    // plainText = Utils::strTobin("sachinpr");
    plainText = (char*)"0000000100100011010001010110011110001001101010111100110111101111";
    cout << "Plain text: " << plainText << endl;

    cipherText = DesMachine(plainText, false);
    cout << "cipher text: " << cipherText << endl;

    cout << "\n\nDeciphering" << endl;

    decipheredText = DesMachine(cipherText, true);
    cout << "decipher text: " << decipheredText << endl;

    

















}