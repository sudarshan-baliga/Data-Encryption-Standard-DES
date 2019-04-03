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

const unsigned long long key = STDKEY;


float getAvalanchePercentage(char *plainText, char *cipherText, int len) {
    
    const int pos = rand()%len;
    int count = 0;
    char newPT[len+1];
    strcpy(newPT, plainText);

    newPT[pos] = (
        newPT[pos] == '1' ? '0' : '1'
    );

    DES::DesOut *obj = DES::DesMachine(newPT, key, true);
    char *newCT = obj -> binForm;
    
    int iter = 0;
    while(cipherText[iter] != '\0') {
        if(cipherText[iter] != newCT[iter])
            ++count;
        ++iter;
    }
    return ((count/(float)len)*100);
}

int main(int argc, char *argv[])
{   

    srand(time(NULL));
    // cout << "Encypting..." << endl;
    DES::DesOut *enc = DES::DesMachine(argv[1], key, true);
    // enc -> printState();

    // cout << "Decrypting..." << endl;
    DES::DesOut *dec = DES::DesMachine(
        enc -> txtForm, 
        key,
        false
    );
    cout << getAvalanchePercentage(
        Utils::strTobin(enc -> in), 
        enc -> binForm, 
        strlen(enc -> binForm)
    ) << endl;
    // dec -> printState();

}