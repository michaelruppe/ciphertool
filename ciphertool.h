#ifndef CIPHERTOOL
#define CIPHERTOOL



// Swap elements in an array of integers
void swapInt(int *xp, int *yp);

// Swap elements in an array of chars
void swapChar(char *xp, char *yp);

// Substitution Cipher: Encrypts or decrypts a string using the supplied key
int substitutionCipher(char *str, char *key, char *strOut, _Bool encrypt);

// Rotation Cipher: Encrypts or decrypts a string using the supplied key
int rotationCipher(char *str, int key, char *strOut, _Bool encrypt);

#endif
