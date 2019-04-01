#include <stdio.h>
#include <string.h>
#include <string>

#include "../boxes/boxes.h"
#include "functions.h"
#include "../utils/utils.h"
#include "../keygen/keygen.h"


using namespace Utils;

char *DES::getPermutation(char *arr, const char *type)
{
    // array is expected to be of len 64.
    const int *permBox = ipBox;
    if (strcmp(type, "final") == 0)
        permBox = fpBox;

    char *ans = new char[65];
    int iter = 0;

    while (iter < 64)
    {
        ans[iter] = arr[permBox[iter] - 1];
        ++iter;
    }

    ans[64] = '\0';
    return ans;
}

char *DES::sBoxFunction(char *str)
{
    if (strlen(str) != 48)
        return NULL;
    std::string ans;
    int sBoxIter = 0;
    char row[3], col[5];
    for (int i = 0; i < 48; i += 6)
    {
        row[0] = str[i];
        row[1] = str[i + 5];
        row[2] = '\0';

        col[0] = str[i + 1];
        col[1] = str[i + 2];
        col[2] = str[i + 3];
        col[3] = str[i + 4];
        col[4] = '\0';
        ans.append(
            numTobin(
                sBox[sBoxIter++][binToint(row)][binToint(col)], 4));
    }
    char *_ans = new char[33];
    strcpy(_ans, ans.c_str());
    return _ans;
}

void DES::reverseKeys(unsigned long long *keys)
{
    int start = 0, end = 15;
    unsigned long long temp;
    while(start < end)
    {
        temp = keys[start];
        keys[start] = keys[end];
        keys[end] = temp;
        start++;
        end--;
    }
}

char *DES::expansionPermutation(char *rightBlock)
{
    char *ans = new char[49];
    for (int itr = 0; itr < 48; itr++)
        ans[itr] = rightBlock[expansionBox[itr] - 1];
    ans[49] = '\0';
    return ans;
}

char *DES::FFfinalPermuatation(char *str)
{
    char *ans = new char[33];
    int iter = 0;
    while (iter < 32)
    {
        ans[iter] = str[permutationBox[iter] - 1];
        ++iter;
    }
    str[32] = '\0';
    return ans;
}

// FF(32bit)
// expansion to 48bit
// xor with key
// to sBoxes and get 32bit
// permutation using dbox
char *DES::feistalFn(char *str, char *key)
{
    // str should be 32 bit in size
    return FFfinalPermuatation(
        sBoxFunction(
            Utils::xorBlocks(
                expansionPermutation(str),
                key,
                48)));
}

// 16 time fiestal round
// A single fiestal Round has
// 64 bit input
// splitting into two 32 bit parts
// newLeft = Right (if not 16th round)
// newRight = left xor FF(right)

char *DES::DESround(char *str, char *key)
{
    // str should be 64bit in size
    char *newStr = new char[65];
    char *leftBlock = Utils::substr(str, 0, 32);
    char *rightBlock = Utils::substr(str, 32, 32);
    char *temp;

    temp = rightBlock;
    rightBlock = Utils::xorBlocks(leftBlock, feistalFn(rightBlock, key), 32);
    leftBlock = temp;
 
    strcpy(newStr, leftBlock);
    strcpy(newStr + 32, rightBlock);
    newStr[64] = '\0';

    return newStr;
}

char* DES::Des_64_Machine(char *inText, unsigned long long key, bool decipher)
{
    // steps:
    //generate the keys
    ull *keys = DESKeyGen::getKeys(key);

    // if deciphering reverse the keys
    if(decipher)
        reverseKeys(keys);
    
    // IP
    char *text = getPermutation(inText, "initial");
    
    // 16 time fiestal round
    for (int i = 0; i < 16; i++)
    {
        text = DESround(text, numTobin(keys[i], 48));
        // cout << "round " << i + 1 << " result " << text << endl;
    }
    
    // swapping left and right part at the end(nullifying last swap)
    char *leftPart = substr(text, 0, 32);
    char *rightPart = substr(text, 32, 32);
    strcpy(text, rightPart);
    strcpy(text+32, leftPart);

    // FP
    text = getPermutation(text, "final");

    return text;
}


DES::DesOut* DES::DesMachine(char *msg, unsigned long long key, bool enc) {
    DES::DesOut *ans = new DES::DesOut();
    
    int inpLen = strlen(msg);
    if(enc)
        if(inpLen%8) {
            int start = inpLen;
            inpLen = (inpLen/8+1)*8;
            for(int i=start;i<inpLen;++i) msg[i] = 'X';
            msg[inpLen] = '\0';
        }
    

    char *finalEncStr, *plainTextBin, *encBin;
    char *fullPlainTextBin = strTobin(msg);
    char *finalEncBin= new char[inpLen*8+1];

    ans -> blockCount = (inpLen/8);
    ans -> blockIP = new char*[inpLen/8];
    ans -> blockOP = new char*[inpLen/8];

    int iter = 0;
    while(iter < inpLen) {

        plainTextBin = substr(fullPlainTextBin, iter*8, 64);
        ans -> blockIP[iter/8] = plainTextBin;

        encBin = Des_64_Machine(plainTextBin, key, !enc);
        ans -> blockOP[iter/8] = encBin;

        strcpy(finalEncBin+iter*8, encBin);

        iter += 8;
    }      
    finalEncBin[inpLen*8] = '\0';
    ans -> binForm = finalEncBin;
    ans -> txtForm = binTostr(finalEncBin);
    ans -> in = msg;
    return ans;
}

void DES::DesOut::printState(void) {
    // blockCount int
   // char *in, *binForm, *txtForm, **blockOP, **blockIP;
    
    printf("%-15s| %s\n\n", "Input: ", this -> in);
    int iter = 0;
    while(iter < this -> blockCount) {
        printf("Block %d\n", iter+1);
        printf("%-15s| %s\n", "-->Input", this -> blockIP[iter]);
        printf("%-15s| %s\n", "-->Output", this -> blockOP[iter]);
        ++iter;
    }  
    printf("\n%-15s| %s\n", "Text form", this -> txtForm);
    printf("%-15s| %s\n", "Binary form", this -> binForm);


    char *dashes = new char[101];
    memset(dashes, '-', sizeof(char)*100);
    printf("%s\n", dashes);
    delete dashes;

}


void DES::modifySbox(int key) {
    for(int i=0;i<8;++i) {
        for(int r=0;r<4;++r)
            for(int c=0;c<16;++c)
                sBox[i][r][c] = (
                    (sBox[i][r][c]^key)^(sBox[i][r][c]^key^(c+1))
                );
    }
}