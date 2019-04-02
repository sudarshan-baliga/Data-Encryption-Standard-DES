#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"
#include "./lib/boxes/boxes.h"

#define STDKEY 1383827165325090801
#define endl "\n";

using namespace std;

const unsigned long long key = 5634127856;


int main(int argc, char *argv[])
{   

    DES::modifySbox(112129);
    // cout << "Encypting..." << endl;
    DES::DesOut *enc = DES::DesMachine(argv[1], key, true);
    enc -> printState();

    // cout << "Decrypting..." << endl;
    DES::DesOut *dec = DES::DesMachine(
        enc -> txtForm, 
        key,
        false
    );
    // cout << Utils::getAvalanchePercentage(enc -> binForm, dec -> binForm, strlen(enc -> binForm)) << endl;
    dec -> printState();
}