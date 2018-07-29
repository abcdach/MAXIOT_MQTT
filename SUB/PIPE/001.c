
//#------------------------------------------------
//#	export PS1='> '
//#	tar -cvf 002.tar iot/
//#------------------------------------------------
	#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
	#include <stdlib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <poll.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <sys/time.h>
//#------------------------------------------------
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>
//#------------------------------------------------
	#include "pipe/pipe_X1.h" // change !!!
	#include "pipe/pipe_X2.h" // change !!!


int main(int argc , char *argv[])
{
	//####################################################
	Pipe_X1_init();
	Pipe_X2_init();
	//####################################################
	int fff=0;
	char My_Buff[1024];
	while( 1 ){
		usleep(1000000);
		sprintf(My_Buff,"Cou X1: %d\n\r",fff);
		Pipe_write_to_X1(My_Buff);
		sprintf(My_Buff,"Cou X2: %d\n\r",fff);
		Pipe_write_to_X2(My_Buff);
		fff ++;
	}
	//####################################################
	return 0;
}

