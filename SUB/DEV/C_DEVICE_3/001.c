//#------------------------------------------------
	#define _GNU_SOURCE
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/time.h>
//#------------------------------------------------
	#include "MAXIOT/MAXIOT.h"
//#------------------------------------------------


int main(int argc , char *argv[])
{
	MAXIOT_INIT("127.0.0.1",3004);

	int COUNTER=0;
	char COUNTER_DATA[128];
	while( 1 ){
		COUNTER++;
		sprintf(COUNTER_DATA,"%d",COUNTER);
		DATA_TO_IOT(0,COUNTER_DATA);
		usleep(300000);
	}
	return 0;
}



