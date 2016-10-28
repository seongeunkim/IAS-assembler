#ifndef _MISC_H
#define _MISC_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define FALSE -1
#define TRUE 1


int checkHexPattern(char tkn[]);
int checkHexadecimal(char tkn[]);
int checkDigit(char tkn[]);
int checkInterval(long long int min, long long int max, char num_char[]);
int obtainMultiple(int start, int val);
void twoComplement(long long int number, char complement_hex[]);
void append(char wrd[], char insert[], int pos);
void printMessage(FILE *fp, char error[]);

#endif