/*
 * Name: Luciano Adam
 * ID: 115157187
 * Class: CSE 220.01
 * Prof.: Abid M. Malik
 * Recitation: R03
 * Assignment: HW3
 * Due Date: 10/11/2023 23:59 EST
 */


#include "../include/global.h"

#define EOM_SIZE 7U // Size of "__EOM__"
#define EOM "__EOM__"
#define UNDEFINED_SIZE 9 // Size of "undefined"
#define UNDEFINED "undefined"
#define SIZE_OF_ALPHABET 26 // Number of letters in the alphabet
#define SIZE_OF_NUMS 10 // Total numbers in ASCII table


// Copied and pasted the function from strPtr.c to avoid grading issues
int strgLen(char *s){
    if (s == NULL) return -1;
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

int encrypt(const char *plaintext, char *ciphertext, int key){
    if (plaintext == NULL || ciphertext == NULL) return -2;
    const unsigned int PT_LEN = (unsigned int)strgLen((char*) plaintext), CT_LEN = (unsigned int) strgLen(ciphertext);
    if (CT_LEN < PT_LEN + EOM_SIZE) return -1;
    while (key < 0) key += SIZE_OF_ALPHABET; // Dealing with negative inputs
    while (key > SIZE_OF_ALPHABET) key %= SIZE_OF_ALPHABET;
    unsigned int i, j = 0;
    for (i = 0; i < PT_LEN; i++){
        const char CUR_CHAR = plaintext[i];
        if (CUR_CHAR >= 'a' && CUR_CHAR <= 'z'){
            ciphertext[i] = (CUR_CHAR - 'a' + key) % SIZE_OF_ALPHABET + 'a';
            j++;
        }
        else if (CUR_CHAR >= 'A' && CUR_CHAR <= 'Z'){
            ciphertext[i] = (CUR_CHAR - 'A' + key) % SIZE_OF_ALPHABET + 'A';
            j++;
        }
        else if (CUR_CHAR >= '0' && CUR_CHAR <= '9'){
            ciphertext[i] = (CUR_CHAR - '0' + key) % SIZE_OF_NUMS + '0';
            j++;
        }
        else ciphertext[i] = plaintext[i];
    }
    if (j == 0){
        if (CT_LEN > UNDEFINED_SIZE + EOM_SIZE){
            for (i = 0; i < UNDEFINED_SIZE; i++)
                ciphertext[i] = UNDEFINED[i];
            for (i = UNDEFINED_SIZE; i < UNDEFINED_SIZE + EOM_SIZE; i++)
                ciphertext[i] = EOM[i - UNDEFINED_SIZE];
        }
        else return -1;
    }
    else for (i = PT_LEN; i < PT_LEN + EOM_SIZE; i++) ciphertext[i] = EOM[i - PT_LEN];
    ciphertext[i] = '\0'; // Adding null terminator
    return (int) j;
}

int decrypt(const char *ciphertext, char *plaintext, int key){
    if (plaintext == NULL || ciphertext == NULL) return -2;
    const unsigned int CT_LEN = (unsigned int) strgLen((char*) ciphertext), PT_LEN = (unsigned int) strgLen(plaintext);
    if (PT_LEN == 0 || CT_LEN == 0) return -2;
    while (key < 0) key += SIZE_OF_ALPHABET; // Dealing with negative inputs
    while (key > SIZE_OF_ALPHABET) key %= SIZE_OF_ALPHABET;
    unsigned int i, j, k = 0;
    unsigned char flag = 1; // 1 by default, turns to 0 if portion of text is not equivalent to EOM
    for (i = 0; i < CT_LEN; i++){ // Finding EOM
        const char CUR_CHAR = ciphertext[i];
        if (CUR_CHAR == EOM[0]){
            for (j = 0; j < EOM_SIZE && i + j < CT_LEN; j++){
                if (EOM[j] != ciphertext[i + j]){
                    flag = 0;
                    break;
                }
            }
            if (flag){
                j -= (EOM_SIZE - 1);
                break;
            }
        }
    }
    if (flag == 0) return -1;
    for (i = 0; i < CT_LEN && i < PT_LEN && i < j; i++){
        const char CUR_CHAR = ciphertext[i];
        if (CUR_CHAR >= 'a' && CUR_CHAR <= 'z'){
            plaintext[i] = (CUR_CHAR - 'a' - key + SIZE_OF_ALPHABET) % SIZE_OF_ALPHABET + 'a';
            k++;
        }
        else if (CUR_CHAR >= 'A' && CUR_CHAR <= 'Z'){
            plaintext[i] = (CUR_CHAR - 'A' - key + SIZE_OF_ALPHABET) % SIZE_OF_ALPHABET + 'A';
            k++;
        }
        else if (CUR_CHAR >= '0' && CUR_CHAR <= '9'){
            plaintext[i] = (CUR_CHAR - '0' - key + SIZE_OF_NUMS) % SIZE_OF_NUMS + '0';
            k++;
        }
        else plaintext[i] = ciphertext[i];
    }
    if (k == 0){
        if (PT_LEN >= UNDEFINED_SIZE) for (i = 0; i < UNDEFINED_SIZE; i++) plaintext[i] = UNDEFINED[i];
        else return -1;
    }
    plaintext[i] = '\0'; // Adding null terminator
    return (int) k;
}
