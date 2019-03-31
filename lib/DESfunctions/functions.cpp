#include <string.h>
#include <string>
#include <iostream>
#include "../boxes/boxes.h"
#include "functions.h"
#include "../utils/utils.h"

using namespace Utils;

char* DES::getPermutation(char *arr, const char *type)  {
    // array is expected to be of len 64.
    int *permBox = ip;
    if(strcmp(type, "final") == 0)
        permBox = fp;

    char *ans = new char[65];
    int iter = 0;
    
    while(iter < 64) {
        ans[iter] = arr[permBox[iter]-1];
        ++iter;
    }
           
    ans[64] = '\0';
    return ans;
}
  

char* DES::xorBlocks(char* arr1, char* arr2, int n) {
    char *ans = new char[n + 1];
    for(int idx = 0; idx < n; ++idx)
        ans[idx] = ((arr1[idx] ^ arr2[idx]) != 0 ? '1': '0');
    ans[n] = '\0';
    return ans;
}

char* DES::sBox(char *str) {
    if(strlen(str) != 48)
        return NULL;
    std::string ans;
    int sBoxIter = 0;
    char row[3], col[5];
    for(int i=0;i<48;i+=6) {
        row[0] = str[i];
        row[1] = str[i+5];
        row[2] = '\0';

        col[0] = str[i+1];
        col[1] = str[i+2];
        col[2] = str[i+3];
        col[3] = str[i+4];
        col[4] = '\0'; 
        ans.append(
            bin(
                s[sBoxIter++][binToint(row)][binToint(col)]
                , 4
            )
        ); 
    }
    char *_ans = new char[33];
    strcpy(_ans, ans.c_str());
    return _ans;
}

