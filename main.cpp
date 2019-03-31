#include <iostream>
#include <string.h>
#include "./lib/keygen/keygen.h"
#include "./lib/parser/parser.h"
#include "./lib/DESfunctions/functions.h"
#define endl "\n";
using namespace std;
using namespace DES;

int main()
{
    // ull *keys = DESKeyGen::getKeysForDES(1383827165325090801); 
    // int i=0;
    // while(i < 16)
    //     cout << bin(keys[i++]) << "\n";
    // DES::getIP();

    // string msg = "sachinprabhu";
    // cout << toBits(msg) << "\n";

    char  *leftBlock, *rightBlock;
    char arr[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    cout << "arr :" << arr << "\n";
    cout << "ip " << getIP(arr) << "\n";
    leftBlock = substr(getIP(arr), 0, 32);
    rightBlock = substr(getIP(arr), 32, 32);
    cout << "expansion: " << expansionPermutation(rightBlock);
    
}