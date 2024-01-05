/* DO NOT ADD CODE TO THIS FILE. IT WILL BE REPLACED DURING GRADING. */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int strgLen(char* s);
void strgCopy(char* s,char* d);
void strgChangeCase(char* s);
int strgDiff(char* s1,char* s2);
void strgInterleave(char* s1,char* s2,char* d);
int encrypt(const char *plaintext, char *ciphertext, int key);
int decrypt(const char *ciphertext, char *plaintext, int key);
