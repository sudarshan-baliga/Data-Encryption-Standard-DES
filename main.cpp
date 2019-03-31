#include <iostream>
#include "./lib/boxes/boxes.h"
#include "./lib/keygen/keygen.h"

using namespace std;


int main()
{
    ull *keys = DESKeyGen::getKeysForDES(1383827165325090801); 
    int i=0;
    while(i < 16)
        cout << bin(keys[i++]) << "\n";
}