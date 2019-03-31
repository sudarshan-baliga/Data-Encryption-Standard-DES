#include <iostream>
#include <string>
#include "./lib/keygen/keygen.h"
#include "./lib/parser/parser.h"
#include "./lib/DESfunctions/functions.h"

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

    char arr[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    cout << arr << "\n";
    cout << getIP(arr) << "\n";
}