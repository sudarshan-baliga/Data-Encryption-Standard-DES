#ifndef DESfunctions

#define DESfunctions

namespace DES {
  
    char* getIP(char *arr);
    char* xorBlocks(char* arr1, char* arr2, int n);
    char* expansionPermutation(char *righBlock);
    char* substr(char *arr, int begin, int len);
} // DES


#endif

