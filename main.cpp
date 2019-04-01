#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include "./lib/DESfunctions/functions.h"
#include "./lib/utils/utils.h"

#define endl "\n";

using namespace std;
using namespace DES;


const unsigned long long key = 1383827165325090801;

float getPercentageChange(char *expected, char *actual, int len) {
    int count = 0, iter = 0;
    while(expected[iter] != '\0') {
        if(expected[iter] != actual[iter])
            ++count;
        ++iter;
    }
    return ((count/(float)len)*100);
}

int main(int argc, char *argv[])
{   
    DesOut *ans = DesMachine(argv[1], key, true);
    
    DesOut *dec = DesMachine(
        ans -> txtForm, 
        key,
        false
    );
    cout << dec -> txtForm << endl;

 
}