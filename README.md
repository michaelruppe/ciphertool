# Ciphertool
Some tools to encrypt and decrypt the Rotation (Caesar) Cipher and Substituion Cipher

Features:
 - Encrypt/decrypt a message using a key
 - Crack the Rotation Cipher (find the right key)

### To run the program
**Compile**: `gcc -o ciphertool main.c ciphertool.c`

**Run**: `./ciphertool`

**Or**, to compile and run in one command:
`gcc -o ciphertool main.c ciphertool.c && ./ciphertool`


### Files
 - **main.c**: User-interactive CLI program.
 - **ciphertool.c**: Functions to cipher/decipher
 - **ciphertool.h**: The C header file for the cipher functions.
 - **google-10000-english.txt**: The 10,000 most common English words in order of frequency, as determined by n-gram frequency analysis of the Google's Trillion Word Corpus.


### Why?
This program was made for a bit of fun. It's in no way robust and has loads of limitations eg. can only use CAPITAL letters.
Use and abuse as you see fit.
