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
#define UPPER_LOWER_DIFF 32 // Difference between uppercase and lowercase characters in the ASCII table


int strgLen(char *s){
    if (s == NULL) return -1;
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void strgCopy(char *s,char *d ){
    if (s == NULL || d == NULL) return;
    const unsigned int S_LEN = strgLen(s), D_LEN = strgLen(d),
                       LIMIT = S_LEN > D_LEN ? D_LEN : S_LEN;
    unsigned int i;
    for (i = 0; i < LIMIT; i++) d[i] = s[i];
    if (LIMIT == S_LEN) d[S_LEN] = '\0';
}

void strgChangeCase(char *s){
    if (s == NULL || strgLen(s) == 0) return;
    int i = 0;
    for (i = 0; s[i] != '\0'; i++)
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            s[i] ^= UPPER_LOWER_DIFF;
}

int strgDiff(char *s1,char *s2 ){
    if (s1 == NULL || s2 == NULL) return -2;
    const int S1_LEN = strgLen(s1), S2_LEN = strgLen(s2),
              LIMIT = S1_LEN > S2_LEN ? S2_LEN : S1_LEN;
    int i;
    for (i = 0; i < LIMIT; i++) if (s1[i] != s2[i]) return i;
    return S1_LEN == S2_LEN ? -1 : i;
}

void strgInterleave(char *s1, char *s2, char *d ){
    if (s1 == NULL || s2 == NULL || d == NULL) return;
    const unsigned int D_LEN = (unsigned int) strgLen(d);
    unsigned int i = 0;
    while (*s1 != '\0' && *s2 != '\0' && i < D_LEN){
        if(!(i%2)) d[i++] = *s1++;
        else d[i++] = *s2++;
    }
    if (*s1 == '\0' && i < D_LEN) while (*s2 != '\0') d[i++] = *s2++;
    if (*s2 == '\0' && i < D_LEN) while (*s1 != '\0') d[i++] = *s1++;
    d[i] = '\0';
}
