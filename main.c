/*******************************************************************************
A few simple cipher tools. Present functionality:
- Encrypt/Decrypt with Rotation(Caesar) and Substitution Ciphers
- Crack the Rotation Cipher using brute force with dictionary lookup

TODO: - use a portable string-compare(ignore case) in the dictionaryLookup
function. At the moment I think strcasecmp may work only on UNIX like
platforms

Michael Ruppe
April 2019

*******************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// File Paths
#define DICTIONARY "google-10000-english.txt"

// Define state handles
#define STATE_ROTATION 1
#define STATE_SUBST 2
#define STATE_CRACK_CAESAR 3
#define STATE_CRACK_SUBST 4


#define SUB1 "RCR VYE BGBX HBNX FHB FXNQBRV YM RNXFH IZNQEBCJ FHB PCJB? C FHYEQHF KYF. CF'J KYF N JFYXV FHB DBRC PYEZR FBZZ VYE. CF'J N JCFH ZBQBKR. RNXFH IZNQEBCJ PNJ N RNXA ZYXR YM FHB JCFH, JY IYPBXMEZ NKR JY PCJB HB LYEZR EJB FHB MYXLB FY CKMZEBKLB FHB OCRCLHZYXCNKJ FY LXBNFB ZCMB… HB HNR JELH N AKYPZBRQB YM FHB RNXA JCRB FHNF HB LYEZR BGBK ABBI FHB YKBJ HB LNXBR NWYEF MXYO RVCKQ. FHB RNXA JCRB YM FHB MYXLB CJ N INFHPNV FY ONKV NWCZCFCBJ JYOB LYKJCRBX FY WB EKKNFEXNZ. HB WBLNOB JY IYPBXMEZ… FHB YKZV FHCKQ HB PNJ NMXNCR YM PNJ ZYJCKQ HCJ IYPBX, PHCLH BGBKFENZZV, YM LYEXJB, HB RCR. EKMYXFEKNFBZV, HB FNEQHF HCJ NIIXBKFCLB BGBXVFHCKQ HB AKBP, FHBK HCJ NIIXBKFCLB ACZZBR HCO CK HCJ JZBBI. CXYKCL. HB LYEZR JNGB YFHBXJ MXYO RBNFH, WEF KYF HCOJBZM."
#define ROT1 "TVU TVAOTH: AOL KHAH IYVBNOA AV BZ IF AOL IVAOHU ZWPLZ WPUWVPUAZ AOL LEHJA SVJHAPVU VM AOL LTWLYVY'Z ULD IHAASL ZAHAPVU. DL HSZV RUVD AOHA AOL DLHWVU ZFZALTZ VM AOPZ KLHAO ZAHY HYL UVA FLA VWLYHAPVUHS. DPAO AOL PTWLYPHS MSLLA ZWYLHK AOYVBNOVBA AOL NHSHEF PU H CHPU LMMVYA AV LUNHNL BZ, PA PZ YLSHAPCLSF BUWYVALJALK. IBA TVZA PTWVYAHUA VM HSS, DL'CL SLHYULK AOHA AOL LTWLYVY OPTZLSM PZ WLYZVUHSSF VCLYZLLPUN AOL MPUHS ZAHNLZ VM AOL JVUZAYBJAPVU VM AOPZ KLHAO ZAHY. THUF IVAOHUZ KPLK AV IYPUN BZ AOPZ PUMVYTHAPVU."


// Global variables
const char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


//******************************************************************************
//* Function Definitions
//*
//******************************************************************************

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


// Substitution Cipher: Encrypts or decrypts a string using the supplied key
void substitution(void) {
  const int encrypt = 0;
  const int decrypt = 1;
  int mode;

  char text[1024], character;
  char encryptionKey[26];


  // Select encrypt/decrypt
  printf("\nEnter:\n0:Encrypt\n1:Decrypt\n ");
  scanf(" %d" ,&mode);

  if (mode == encrypt) {
    // Encryption Code

    printf("Enter plaintext message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter 26 character encryption key: ");
    scanf(" %s", encryptionKey);

    // Loop through plaintext message
    for(int i=0; i<strlen(text); i++){
      // Finding what letter
      for(int j=0; j<26; j++){
        if(text[i] == alphabet[j] ){
          //Replace letter with matching encryption key character
          text[i] = encryptionKey[j];
          break;
        }
      }
    }
    printf("Encrypted text: \n%s\n", text);

  } else if (mode == decrypt){
    // Decryption Code
    printf("Enter encrypted message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter 26 character encryption key: ");
    scanf(" %s", encryptionKey);

    // Loop through encrypted message
    for(int i=0; i<strlen(text); i++){
      // Finding what letter
      for(int j=0; j<26; j++){
        if(text[i] == encryptionKey[j] ){
          //Replace letter with matching alphabet character
          text[i] = alphabet[j];
          break;
        }
      }
    }
    printf("Decrypted text: \n%s\n", text);

  } else {
    printf("Invalid selection\n");
  }
}

// Rotation Cipher: Encrypts or decrypts a string using the supplied key
int rotationCipher(char *str, int key, char *strOut, _Bool encrypt) {
  // Check input parameters
  if (key < 0 || key > 25) {
    printf("Key for rotation cipher must be an integer between 0 and 25\n**** RESTARTING ****");
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
    // non-alphabetic characters pass through unaltered by the above logic
    strOut[i] = character;
  }
    return 0;

}


  void caesar(void){
    int mode;
    int encryptionKey = 0; // Amount to rotate the cipher
    char text[4096], *textOut;

    // Select encrypt/decrypt
    printf(" Select Mode:\n   0: Decrypt\n   1: Encrypt\n ");
    scanf(" %d" ,&mode);

    printf("Enter message to process: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter encryption key: ");
    scanf(" %d", &encryptionKey);

    textOut = calloc(strlen(text), sizeof(char)); // Initialise a block of memory to zero. Same size as input string.

    rotationCipher(text, encryptionKey, textOut, mode); // Mode: 1=Encrypt, 0=Decrypt

    printf("Processed message: %s \n", textOut);

    free(textOut);
  }

  void crackSubstitution(void){
    printf("*** WARNING - Function NOT working - Under Construction ***");

    int freqs[26]; // Frequencies of occurance
    for (int i=0; i < 26; i++) {freqs[i] = 0;} // Initialise array of zeros
    char seen[26];
    char text[2048] = SUB1;
    int lenSeen = 0;
    int len = strlen(text);

    // Step throught encrypted text and accumulate unlabelled frequencies

    // Step through every letter in the text
    for (int i = 0; i < len; i++) {
      if(text[i] >= 'A' && text[i] <= 'Z'){ // Is it a letter?
        //Has letter been seen before?
        for (int j = 0; j < 26; j++) {
          if(text[i] == seen[j]) {
            freqs[j]++;
            break;
          } else {  // If never seen, accumulate and add an occurance
            if (j >= lenSeen) {
              lenSeen++;
              seen[j] = text[i];
              freqs[j]++;
              break;
            }
          }
        }
      }

    }

    for (int i = 0; i < lenSeen; i++) {
      printf("  %c ", seen[i]);
    }
    printf("\n");
    for (int i = 0; i < lenSeen; i++) {
      printf(" %4d ", freqs[i]);
    }

    // Now, we have an array of unique, seen letters (seen), and a corresponding array of occurences (freqs)
    // Sort the array of occurences in descending order, and mirror that sorting in the array of letters
    int i, j;
    for (i = 0; i < lenSeen-1; i++){
      // Last i elements are already in place
      for (j = 0; j < lenSeen-i-1; j++)
      if (freqs[j] < freqs[j+1]) {
        swapInt(&freqs[j], &freqs[j+1]);
        swapChar(&seen[j], &seen[j+1]);
      }
    }

    printf("\n");
    for(int i = 0; i < lenSeen; i++) {
      printf("%c",seen[i]);
    }
    for(int i = 0; i < lenSeen; i++) {
      printf(" %d ",freqs[i]);
    }



    // Assume ideal freq. distribution
    const char letterDistIdeal[26] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};
    // Now perform substitution decryption
    // Loop through encrypted message
    for(int i=0; i<strlen(text); i++){
      // Finding what letter
      for(int j=0; j<lenSeen; j++){
        if(text[i] == seen[j] ){
          //Replace letter with matching alphabet character
          text[i] = letterDistIdeal[j];
          break;
        }
      }
    }
    printf("Decrypted text: \n%s\n", text);


  }

  // Return 0 if argument string is found in a dictionary file, else return 1
  int dictionaryLookup(char *word){
    // Open the dictionary file
    FILE *dictFile;
    dictFile = fopen(DICTIONARY,"r");
    char dictWord[30];  // A temporary holder for a dictionary word
    int test = 0;       // Holds the returned status of fscanf
    // printf("Checking %s ... ", word);
    // Compare a string against every entry in the dictionary
    while(test != EOF){
      test = fscanf(dictFile,"%s",dictWord); //get a word from the dictionary, store in dictWord array
      //if decrypted word matches a word in the dictionary, increment that key's score
      if (strcasecmp(word,dictWord) == 0) { // strcasecmp (UNIX systems) ignores case
        // if (strcicmp(word,dictWord) == 0) { // an attempt at a portable scring-compare that ignores case
        fclose(dictFile);
        // printf("Found %s\n", dictWord);
        return 0; // match found
      }
    }
    fclose(dictFile);
    // printf("No match found in dictionary\n");
    return 1; // No match found
  }

  void crackRotation(void) {

    char *text, *decipherText, character;
    int scores[26]; for(int i = 0; i < 26; i++) {scores[i]=0;} // Array to hold number of real words found for each dectyption key. Initialise with zeros.
    text = calloc(4096, sizeof(char));
    decipherText = calloc(4096, sizeof(char));
    // Prompt for cihpertext to decrypt. Store in array.
    printf("Enter cipher to crack: ");
    scanf(" %[^\n]s" , text);

    // Loop through all possible keys and count number of dictionary words found for each key
    for(int encryptionKey = 0; encryptionKey < 26; encryptionKey++) {
      // Step 1: Perform decryption with current key (offset)
      rotationCipher(text, encryptionKey, decipherText, 0); // Arg = 0 for decrypt

      // Step 2: Tokenise the deciphertext and count how many dictionary words appear. Increment that key's score for each match
      char * pch;
      pch = strtok (decipherText," ,.-:");
      while (pch != NULL)
      {
        int result = dictionaryLookup(pch); // TODO: increment score
        if (result == 0) {
          scores[encryptionKey]++;
        }
        pch = strtok (NULL, " ,.-:");
      }

    }

    // Step 3: Now have an array of scores to match the array of keys. Find the highest scoring key
    int maxScore = 0;
    int encryptionKey = 0;
    for(int i=0; i < 26; i++) {
      if(scores[i] > maxScore) {
        maxScore = scores[i];
        encryptionKey = i;
      }
    }

    printf("found key: %d\n", encryptionKey);

    // Step 4: Final decipher with the best key
    for(int i = 0; text[i] != '\0'; i++){
      character = text[i];

      if(character >= 'A' && character <= 'Z'){
        character = character - encryptionKey;

        if(character < 'A' && character != ' '){
          character = character + 'Z' - 'A' + 1;
        }
      }
      decipherText[i] = character;
    }

    // rotationCipher(text, encryptionKey, decipherText, 0); // Arg = 0 for decrypt

    // Step 5: Print deciphered text
    printf("Deciphered Text:\n%s\n",decipherText);

    free(text);
    free(decipherText);

  }


  //******************************************************************************
  //* Main Loop - State machine and menu prompt
  //*
  //******************************************************************************
  int main() {

    while(1) {
      // Prompt for cipher function
      printf("\n============================\n\tCipher Tools\n============================\n    Rotation Cipher: 1\nSubstitution Cipher: 2\n     Crack Rotation: 3\n Crack Substitution: 4\n               Quit: 0\n Select tool: ");
      int state; // Determines which program to run.
      scanf(" %d" ,&state);

      // The state-machine: jump to the user-selected cipher algorithm
      switch(state) {
        case STATE_ROTATION:
        caesar();
        break;

        case STATE_SUBST:
        substitution();
        break;

        case STATE_CRACK_SUBST:
        crackSubstitution();
        break;

        case STATE_CRACK_CAESAR:
        crackRotation();
        break;

        case 0: return 0;

        default: printf("Incorrect input, enter a number 1 - 4 to select a mode");

      }

    }


  }
