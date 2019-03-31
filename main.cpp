#include <iostream>
#include <string.h>
#include <string>
#include "./lib/keygen/keygen.h"
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"
#define endl "\n";
#define STDKEY 1383827165325090801

using namespace std;
using namespace DES;

char* DesMachine(char *inText, bool decipher)
{
    // steps:
    //generate the keys
    ull *keys = DESKeyGen::getKeys(STDKEY);

    // if deciphering reverse the keys
    if(decipher)
        reverseKeys(keys);
    
    // IP
    char *text = getPermutation(inText, "initial");
    
    // 16 time fiestal round
    for (int i = 0; i < 16; i++)
    {
        text = DESround(text, Utils::numTobin(keys[i], 48));
        // cout << "round " << i + 1 << " result " << text << endl;
    }
    
    // swapping left and right part at the end(nullifying last swap)
    char *leftPart = Utils::substr(text, 0, 32);
    char *rightPart = Utils::substr(text, 32, 32);
    strcpy(text, rightPart);
    strcpy(text+32, leftPart);

    // FP
    text = getPermutation(text, "final");

    return text;
}

int main()
{   
    // assuming userinput won't exceed 100 chars
    char userInput[100];
    string temp;
    cout << "Enter text: ";
    
    getline(cin, temp);
    strcpy(userInput, temp.c_str());
    int inpLen = strlen(userInput);
    if(inpLen%8) {
        int start = inpLen;
        inpLen = (inpLen/8+1)*8;
        for(int i=start;i<inpLen;++i) userInput[i] = 'X';
        userInput[inpLen] = '\0';
    }
    cout << userInput << " " << inpLen << "\n";

    char *fullPlainText, *cipherText, *decipheredText, finalRes[100];
    int iter = 0;

    fullPlainText = Utils::strTobin(userInput);
    cout << "-----------------------------------------" << endl;
    while(iter < inpLen) {
        cout << "Block no.: " << iter/8+1 << endl;

        char *plainText = Utils::substr(fullPlainText, iter*8, 64);
        cout << "->plain text:     " << plainText << endl;
        
        cipherText = DesMachine(plainText, false);
        cout << "->cipher text:    " << cipherText << endl;

        decipheredText = DesMachine(cipherText, true);
        cout << "->decipher text:  " << decipheredText << endl;

        strcpy(finalRes+iter, Utils::binTostr(decipheredText));
        
        iter += 8;
        cout << "-----------------------------------------" << endl;
    }
    finalRes[iter] = '\0';
    cout << "decrypted msg: " << finalRes << endl;
    
}