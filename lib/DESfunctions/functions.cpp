
#include <string.h>
#include <string>
#include "../boxes/boxes.h"
#include "functions.h"
#include "../utils/utils.h"

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

