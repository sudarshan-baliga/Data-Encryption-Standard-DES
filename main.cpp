#include <iostream>
#include <string.h>
#include "./lib/keygen/keygen.h"
#include "./lib/parser/parser.h"
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"
#define endl "\n";
using namespace std;
using namespace DES;

int main()
{
    char *text = Utils::strTobin("sachinpr");
    text = getPermutation(text, "initial");


    int i=0;
    ull *keys = DESKeyGen::getKeys(1383827165325090801);
    while(i < 16) {
        text = DESround(text, Utils::numTobin(keys[i], 48));
        cout << text << "\n";
        ++i;
    }   
    text = getPermutation(text, "final");
    cout << text << "\n";
    // char  *leftBlock, *rightBlock;
    // char arr[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    // cout << "arr :" << arr << "\n";
    // cout << "ip " << getPermutation(arr, "initial") << "\n";
    // leftBlock = Utils::substr(getPermutation(arr, "initial"), 0, 32);
    // rightBlock = Utils::substr(getPermutation(arr, "initial"), 32, 32);
    // cout << "expansion: " << expansionPermutation(rightBlock);

    
    

    

    // steps:   
        // IP

        // 16 time fiestal round
        // A single fiestal Round has
            // 64 bit input
            // splitting into two 32 bit parts
            // newLeft = Right
            // newRight = left xort FF(right)
            
        // FP
    
}