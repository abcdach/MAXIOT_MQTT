
//#------------------------------------------------
//#	export PS1='> '
//#	tar -cvf 002.tar iot/
//#------------------------------------------------
	#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
	#include <stdlib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>    //strlen
	#include <sys/socket.h>
	#include <arpa/inet.h> //inet_addr
	#include <poll.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <sys/time.h>
//#------------------------------------------------


int main(void) {

	printf("dai dai dai \n\r ");
	//return 0;

	int i = 0;
    while (1) {
      usleep(1000000);
       printf("COUNTER : %d\n\r ", i++);
       if (i==10) break;
    }


    return 0;
}
