#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"

#define STDKEY 1383827165325090801
#define endl "\n";

using namespace std;

const unsigned long long key = 12345607891;


int main(int argc, char *argv[])
{   

    cout << "Encypting..." << endl;
    DES::DesOut *enc = DES::DesMachine(argv[1], key, true);
    enc -> printState();

    cout << "Decrypting..." << endl;
    DES::DesOut *dec = DES::DesMachine(
        enc -> txtForm, 
        key,
        false
    );
    dec -> printState();

 
}