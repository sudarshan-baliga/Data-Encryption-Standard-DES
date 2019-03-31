#include "utils.h"
#include <string.h>

char* Utils::numTobin(unsigned long long num, int count_) {
	int count = count_;
	char *binRep = new char[count_+1];
	while(count)
		binRep[--count] = (num&1 ? '1': '0'), num = num >> 1;
	binRep[count_] = '\0';
	return binRep;
}

unsigned long long Utils::binToint(const char *bin) {
    int len = strlen(bin);
    int iter = len-1;
    int ans = 0;
    while(iter > -1) {
        if(bin[iter] == '1')
            ans += (1 << (len-iter-1));
        --iter;
    }
    return ans;
}

char* Utils::substr(char* arr, int begin, int len) {
    char* res = new char[len];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = '\0';
    return res;
}

char* Utils::xorBlocks(char *arr1, char *arr2, int n) {
    char *ans = new char[n + 1];
    for (int idx = 0; idx < n; idx++)
        ans[idx] = ((arr1[idx] ^ arr2[idx]) != 0 ? '1' : '0');
    ans[n] = '\0';
    return ans;
}

char* Utils::strTobin(const char* message) {
    int msgLen = strlen(message);
    int numBits = msgLen * 8;
    char *bits = new char[numBits+1];
    for(int msgIdx = 0; msgIdx < msgLen; ++msgIdx) {
        for(int bitPos = 0; bitPos < 8; ++bitPos)
            bits[8*msgIdx + 7 - bitPos] = (
                ((message[msgIdx] & (1 << bitPos)) != 0) ? '1' : '0'
            );
    }
    bits[numBits] = '\0';
    return bits;
}