//#------------------------------------------------
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <pthread.h>
	//#include <mysql.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <malloc.h>
	//#include <Python.h>
//#------------------------------------------------
#include "MySHA1.h"
#include "MyBase64.h"
#include "SHA1_Calc.h"


char SHA1_InPut[64];
char SHA1_TEMP[60];
char SHA1_OutPut[128];


char SHA1_INX[60] = "________________________258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

int MySHA1_CALCULATOR(void){

	SHA1Context sha;
	int i;
	uint32_t number;
	char sha1Key[20];
	char *acceptKey = NULL;

    for ( i = 0; i < 128; i++) SHA1_OutPut[i] = 0;
    for ( i = 0; i < 60;  i++) SHA1_TEMP[i] = SHA1_INX[i];
    for ( i = 0; i < 24; i++)  SHA1_TEMP[i] = SHA1_InPut[i];

    //sprintf(keyx,"dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	//for ( i = 0; i < 24; i++)  sha1_Temp[i] = sha1_InPut[i];

	//printf("SHA1_TEMP:%s\n\r",SHA1_TEMP);

	SHA1Reset(&sha);
	SHA1Input(&sha,(const unsigned char*)SHA1_TEMP,60);
	SHA1Result(&sha);

	for(i = 0; i < 5; i++) {
		number = ntohl(sha.Message_Digest[i]);
		memcpy(sha1Key+(4*i), (unsigned char *) &number, 4);
	}
	base64_encode_alloc((const char *) sha1Key, 20, &acceptKey);

	sprintf(SHA1_OutPut,"%s",acceptKey);

	//printf("SHA1_OutPut:%s\n\r",SHA1_OutPut);
	//printf("\n\rttt---------------------------\n\r");

	return 0;

}


int MySHA1_CALCULATOR_2(char * isSHA1_InPut, char * isSHA1_OutPut){

	SHA1Context sha;
	int i;
	uint32_t number;
	char sha1Key[20];
	char *acceptKey = NULL;



	SHA1Reset(&sha);
	SHA1Input(&sha,(const unsigned char*)SHA1_InPut,16);
	SHA1Result(&sha);

	for(i = 0; i < 5; i++) {
		number = ntohl(sha.Message_Digest[i]);
		memcpy(sha1Key+(4*i), (unsigned char *) &number, 4);
	}
	base64_encode_alloc((const char *) sha1Key, 20, &acceptKey);

	sprintf(isSHA1_OutPut,"%s",acceptKey);


	return 0;

}
