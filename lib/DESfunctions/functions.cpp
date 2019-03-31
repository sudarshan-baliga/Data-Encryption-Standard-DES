#include "functions.h"
#include "../boxes/boxes.h"
#include <iostream>

char* DES::getIP(char *arr)  {
    // array is expected to be of len 64.
    char *ans = new char[65];
    int iter = 0;
    
    while(iter < 64)
        ans[iter] = arr[ip[iter]-1], ++iter;
           
    ans[64] = '\0';
    return ans;
}

