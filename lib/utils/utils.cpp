#include "utils.h"
#include <string.h>

char* Utils::bin(unsigned long long num, int count_) {
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