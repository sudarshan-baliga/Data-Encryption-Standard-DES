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
    // steps:
    //generate the keys
    ull *keys = DESKeyGen::getKeys(1383827165325090801);
    // IP
    text = getPermutation(text, "initial");
    // 16 time fiestal round
    for (int i = 0; i < 15; i++)
    {
        text = DESround(text, Utils::numTobin(keys[i], 48), false);
        cout << "round" << i << "result" << text << endl;
    }
    //no left and right swap in final round

    // FP
    text = getPermutation(text, "final");
}