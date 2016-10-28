#include "misc.h"

#define HEX_SIZE 12

/**
 * Given a token, checks if it follows the pattern of a hexadecimal number
 * @param  	tkn 	token to be checked
 * @return	FALSE 	if it is not a valid hexadecimal
 * @return	TRUE	if it is a valid hexadecimal
 */
int checkHexPattern(char tkn[]) {
	if(strlen(tkn) == HEX_SIZE) {
		for(int i = 2; i < HEX_SIZE; i++) {
			if(!isdigit(tkn[i])) {
				if(!(tkn[i] - 'A' >= 0 && tkn[i] - 'A' <= 5) && !(tkn[i] - 'a' >= 0 && tkn[i] - 'a' <= 5)) {
					return FALSE;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
	
}


/**
 * Given a token, checks if it is expected to be a hexadecimal (if it starts with "0x")
 * @param  	tkn 	token to be checkd
 * @return	FALSE	if it does not start with "0x"
 * @return	TRUE	if it does start with "0x"
 */
int checkHexadecimal(char tkn[]) {
	if(tkn[0] == '0' && tkn[1] == 'x') {
		return TRUE;
	}
	return FALSE;
}

/**
 * Given a token, checks if it is a decimal number
 * @param  	tkn 	token to be checked
 * @return	FALSE 	if it is not a decimal number
 * @return	TRUE	if it is a decimal number
 */
int checkDigit(char tkn[]) {
	if(tkn[0] == '-' || isdigit(tkn[0])) {
		for(int i = 1; i < strlen(tkn); i++) {
			if(!isdigit(tkn[i])) {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}


/**
 * Given a number and an interval, checks if it is within the range
 * @param  min      interval minimum number
 * @param  max      interval maximum number
 * @param  num_char given number
 * @return	FALSE	if it is not within the range
 * @return	TRUE	if it is within the range
 */
int checkInterval(long long int min, long long int max, char num_char[]) {
	long long number = atol(num_char);
	if(number >= min && number <= max) {
		return TRUE;
	}
	return FALSE;
}


/**
 * Given a starting number and a value, finds the lowest multiple of the value
 * @param  start starting number
 * @param  val   value
 * @return       the lowest multiple
 */
int obtainMultiple(int start, int val) {
	while(start % val) {
		start++;
	} 
	return start;
}

/**
 * Calculates the two complement of a given negative number and turns it into hexadecimal form
 * @param number         negative number
 * @param complement_hex array where the two complement will be kept
 */
void twoComplement(long long int number, char complement_hex[]) {
	int complement_dec[10], digit;
	char hex[2], number_hex[11];

	number = number * -1;
	sprintf(number_hex, "%010X", (unsigned) number);

	for(int i = 0; i < 10; i++) {
		if(isdigit(number_hex[i])) {
			digit = number_hex[i] - '0';
			complement_dec[i] = 15 - digit;
		}
		else {
			complement_dec[i] = 15 - (10 + number_hex[i] - 'A');
		}
	}
	complement_dec[9] = complement_dec[9] + 1;
	for(int i = 9; i >= 1 && complement_dec[i] > 15; i--) {
		complement_dec[i-1] = complement_dec[i-1] + 1;
		complement_dec[i] = 0;
	}
	for(int i = 0; i < 10; i++) {
		sprintf(hex, "%1X", complement_dec[i]);
		complement_hex[i] = hex[0];
	}
	complement_hex[10] = '\0';
}

/**
 * Given a string, inserts a given character into a given position
 * @param wrd    string where the character will be added
 * @param insert the character to be added
 * @param pos    position where it will be added
 */
void append(char wrd[], char insert[], int pos) {
	char temp[14];
	strncpy(temp, wrd, pos);
	temp[pos] = '\0';
	int length = strlen(temp);
	strcpy(temp + length, insert);
	length = length + strlen(insert);
	strcpy(temp + length, wrd + pos);
	strcpy(wrd, temp);

}

/**
 * Given a FILE handle, writes the error message to the output stream to which it points
 * @param fp    FILE handle
 * @param error string with the error message
 */
void printMessage(FILE *fp, char error[]) {
	fprintf(fp, "%s", error);
}
