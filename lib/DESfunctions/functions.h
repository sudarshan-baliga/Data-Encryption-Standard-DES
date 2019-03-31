#ifndef DESfunctions

#define DESfunctions

namespace DES {
  
    // type is either initial or final
    // default to initial
    char* getPermutation(char *arr, const char *type);
    
    char* xorBlocks(char* arr1, char* arr2, int n);
  
    // str is expected to be of length 48
    // output is of size 32
    char* sBoxFunction(char *str);

    char* expansionPermutation(char *righBlock);

    char* substr(char *arr, int begin, int len);

} // DES



#endif

