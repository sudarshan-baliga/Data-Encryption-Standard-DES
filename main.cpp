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
    
    const int pos = len - 1;
    char newPT[len+1];
    strcpy(newPT, plainText);

    newPT[pos] = (
        newPT[pos] == '1' ? '0' : '1'
    );

    DES::DesOut *obj = DES::DesMachine(newPT, key, true);
    char *newCT = obj -> binForm;
    
    int misMatchCount = 0, iter = 0;
    while(cipherText[iter] != '\0') {
        if(cipherText[iter] != newCT[iter])
            ++misMatchCount;
        ++iter;
    }
    return ((misMatchCount/(float)len)*100);
}

bool isTextPassed(int argc, bool f1, bool f2) {
    if(f1 && f2) {
        if(argc <= 3) return false;
        return true;
    }else if(f1 || f2) {
        if(argc <= 2) return false;
        return true;
    }else 
        return (argc >= 2);
}

int main(int argc, char *argv[])
{   

    bool hideDetails = false;
    srand(time(NULL));

    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-e") == 0)
            enhance = true;
        if(strcmp(argv[i], "-h") == 0)
            hideDetails = true;
    }

    if(!isTextPassed(argc, enhance, hideDetails)) {
        cout << 0 << endl;
        exit(0);
    }

    // Encryption
    DES::DesOut *enc = DES::DesMachine(argv[1], key, true);
    if(hideDetails == false)
        enc -> printState();



    // Decryption
    DES::DesOut *dec = DES::DesMachine(enc -> txtForm, key, false);
    if(hideDetails == false)
        dec -> printState();


    // Avalance percentage
    cout << getAvalanchePercentage(
        Utils::strTobin(enc -> in), 
        enc -> binForm, 
        strlen(enc -> binForm)
    ) << endl;

}