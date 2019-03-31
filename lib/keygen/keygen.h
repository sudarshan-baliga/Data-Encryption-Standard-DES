#ifndef KEYGEN

#define KEYGEN

typedef unsigned long long ull;


class DESKeyGen {
    static const int pc1[56];
    static const int pc2[48];
    static void leftRotate(ull *n, unsigned int d);
    static bool isNthBitSet(ull *num, int n);
    static void setNthBit(ull *num, int n);
    static ull compressAndpermute(ull key, const int *box, int boxSize, int inputBitSize);
public:
    static ull* getKeys(ull key);
};

#endif