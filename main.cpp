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
    // ull *keys = DESKeyGen::getKeysForDES(1383827165325090801); 
    // int i=0;
    // while(i < 16)
    //     cout << bin(keys[i++]) << "\n";
    // DES::getIP();

    // string msg = "sachinprabhu";
    // cout << toBits(msg) << "\n";

    // char arr[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    // char arr2[65] = "000000010010001101000101011001111000100110101011110011011110000";
    // cout << arr << "\n";
    // cout << getPermutation(arr, "initial") << "\n";
    // cout << xorBlocks(arr, arr2, 64) << endl;


    char sin[49] = "011000010001011110111010100001100110010100100111";
    // cout << sin << "\n";
    char *sout = sBoxFunction(sin);
    cout << sout << "\n";
    
    
    char arr3[65] = "0000101001001100110110011001010101000011010000100011001000110100";
    cout << getPermutation(arr3, "final") << "\n";
    char  *leftBlock, *rightBlock;
    char arr[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    cout << "arr :" << arr << "\n";
    cout << "ip " << getPermutation(arr, "initial") << "\n";
    leftBlock = substr(getPermutation(arr, "initial"), 0, 32);
    rightBlock = substr(getPermutation(arr, "initial"), 32, 32);
    cout << "expansion: " << expansionPermutation(rightBlock);
    
}