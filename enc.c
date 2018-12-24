#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enc.h"
#include "a4-util.h"

// global var
unsigned char key = 101;
unsigned char counter = 87;

/*
 Function:	encryptStr
 Purpose:	this function encrypts a string
 Parameters:
 in:		source (string to be encrypted), 
			destination (place to put encrypted string), 
			length of string
 return:	the encrypted string
 */
void encryptStr(char *src, char *dest, int len) {
	for (int i = 0; i < len; i++) {
		// counter is encrypted w/ key
		char tempChar = encrypt(counter, key);
		// counter is XOR-ed w/ plain text character
		dest[i] = tempChar ^ src[i];
		counter++;
	}
	dest[len] = '\0';
}
