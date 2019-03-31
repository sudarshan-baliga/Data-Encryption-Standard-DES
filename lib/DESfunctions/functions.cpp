#include "functions.h"
#include "../boxes/boxes.h"
#include <iostream>
using namespace std;
char* DES::getIP(char *arr)  {
    // array is expected to be of len 64.
    char *ans = new char[65];
    int iter = 0;
    
    while(iter < 64)
        ans[iter] = arr[ip[iter]-1], ++iter;
           
    ans[64] = '\0';
    return ans;
}

char* DES::xorBlocks(char* arr1, char* arr2, int n)
{
    char *ans = new char[n + 1];
    for(int idx = 0; idx < n; idx++)
        ans[idx] = (char)(arr1[idx] ^ arr2[idx]);
    ans[n] = '\0';
    return ans;
}



