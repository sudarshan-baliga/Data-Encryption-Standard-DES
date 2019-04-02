#include "keygen.h"
#include "../boxes/boxes.h"
#include <iostream>
using namespace std;

void DESKeyGen::leftRotate(ull *n, unsigned int d) {
    *n = ((*n) << d)|((*n) >> (28 - d)); 
}

bool DESKeyGen::isNthBitSet(ull *num, int n) {
    ull one = 1;
    return ((*num)&(one << n)) != 0;
}

void DESKeyGen::setNthBit(ull *num, int n) {
    ull one = 1;
    (*num) = (*num)|(one << n);
}

ull DESKeyGen::compressAndpermute(ull key, const int *box, int boxSize, int inputBitSize) {
	ull ans = 0, one_ = 1;
	int ignIndices[8] = {56, 48, 40, 32, 24, 16, 8, 0};
	short tempArr[8];
	for(int i=0;i<8;++i)
		tempArr[i] = ( (key & (one_ << ignIndices[i])) != 0 ? 1 : 0);
	int one= 1, two = 2;
	bool visited[4] = {0};
	for(int i=0;i<8;i+=2) {
		one = tempArr[i] & one;
		two = (tempArr[i + 1] + tempArr[i + 1]) &  two;
		if(!visited[one + two]){
			transpositionOrder[i / 2] = one + two;
			visited[one + two] = true;
		}
		else
		{
			int idx = one + two;
			while(visited[idx])
				idx = (idx + 1) % 4;
			transpositionOrder[i / 2] = idx;
			visited[idx] = true;
		}
		
	}
	cout << "transposition" << endl;
	for(int i = 0; i < 4; i++)
        cout << transpositionOrder[i] << " ";
	cout << endl;

	for(int i=0;i<boxSize;++i)
		if(isNthBitSet(&key, inputBitSize-box[i]) == true)
			setNthBit(&ans, boxSize-1-i);
	return ans;
}

ull* DESKeyGen::getKeys(ull key) {
      // initial parity drop (64bit -> 56bit)
	ull afterParityDrop = compressAndpermute(key, pc1 ,56, 64);

	// preparig masks for extracting halves(left and right)
	ull one = 1;
	ull maskForLeft = ((one << 56) - (one << 28));
	ull maskForRight = (one << 28) - 1;

	// extracting left and right half.  
	ull left = (afterParityDrop & maskForLeft) >> 28;
	ull right = afterParityDrop & maskForRight;

	//Array of keys for DES
	ull *keys = new ull[16];
	
	ull toCompressionBox;

	// getting keys
	for(int i=1;i<=16;++i) {
	if(i == 1 || i == 2 || i == 9 || i == 16) {
		leftRotate(&left, 1);
		leftRotate(&right, 1);
	}else {
		leftRotate(&left, 2);
		leftRotate(&right, 2);
	}
	// following two steps are needed(since we want to operate just
	// on first 28 bits and we want to ignore rest of them)
	left = (left&maskForRight);
	right = (right&maskForRight);

	toCompressionBox = (left << 28) + right;
	keys[i-1] = compressAndpermute(toCompressionBox, pc2, 48, 56);
	}
	
	return keys;
}

const int DESKeyGen::pc1[56] = {
  57, 49, 41, 33, 25, 17, 9, 1,
  58, 50, 42, 34, 26, 18, 10, 2,
  59, 51, 43, 35, 27, 19, 11, 3,
  60, 52, 44, 36, 63, 55, 47, 39,
  31, 23, 15, 7, 62, 54, 46, 38,
  30, 22, 14, 6, 61, 53, 45, 37,
  29, 21, 13, 5, 28, 20, 12, 4
};

const int DESKeyGen::pc2[48] = {
  14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
  23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 
};