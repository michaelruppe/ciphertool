#include "ciphertool.h"
#include <string.h>
#include <stdio.h>

// Global variables
const char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


// Swap elements in an array of integers
void swapInt(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// Swap elements in an array of chars
void swapChar(char *xp, char *yp) {
  char temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int substitutionCipher(char *str, char *key, char *strOut, _Bool encrypt) {
  char character;
  // Loop through input message
  for(int i=0; i<strlen(str); i++){
    character = str[i];
    // Only process UPPER-case alphabetical characters.
    if (character >= 'A' && character <= 'Z'){

      // Find the assigned key/letter for encrypt/decrypt
      for(int j=0; j<26; j++){ // For each letter in the alphabet
        if( encrypt && str[i] == alphabet[j] ){ // Encryption
          //Replace letter with matching encryption key character
          strOut[i] = key[j];
          break;
        } else if( !encrypt && str[i] == key[j]) { // Decryption
          //Replace letter with matching alphabet character
          strOut[i] = alphabet[j];
          break;
        }
      }
    } else {
      // Pass non-alphabet characters unchanged
      strOut[i] = str[i];
    }
  }
}

// Rotation Cipher: Encrypts or decrypts a string using the supplied key
int rotationCipher(char *str, int key, char *strOut, _Bool encrypt) {
  // Check input parameters
  if (key < 0 || key > 25) {
    printf("Warning: Key for rotation cipher should be an integer between 0 and 25\n");
    return 1;
  }

  char character;
  // Perform the rotation cipher / decipher
  for(int i = 0; str[i] != '\0'; i++){
    character = str[i];

    // Only En/Decrypt alphabet characters
    if (character >= 'a' && character <= 'z'){ character -= 32; } // convert to upper case
    if(character >= 'A' && character <= 'Z'){
      if(encrypt){
        // *** ENCRYPT a character
        character = character + key;
        if(character > 'Z'){
          character = character - 'Z' + 'A' - 1;
        }
      } else {
        // *** DECRYPT a character
        character = character - key;
        if(character > 'Z'){
          character = character + 'Z' - 'A' - 1;
        }
      }
    }
    // Once a character has been en/decrypted, save it to the output array
    // non-alphabetic characters pass through the above logic unaltered
    strOut[i] = character;
  }
  return 0;
}
