namespace Utils {

    // count = number of bits in binary rep.
    char* numTobin(unsigned long long num, int count);

    char* strTobin(const char *message);
    
    unsigned long long binToint(const char *str);

    char* substr(char *arr, int begin, int len);

    char* xorBlocks(char* arr1, char* arr2, int n);


} // Utils
