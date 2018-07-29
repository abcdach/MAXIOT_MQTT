
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

//#include "apue.h"
#include <sys/wait.h>

int MAXLINE = 30;
//char *cmd = "/home/maxiot/TEMP_MQTT_FileConfig/SUB/POPEN/Test_Stream/test ";
char *cmd = "ls";

int
main(void)
{
    char    line[MAXLINE];
    FILE    *fpin;

    if ((fpin = popen(cmd, "r")) == NULL)
        printf("popen error");
    for ( ; ; ) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) /* read from pipe */
            break;
        if (fputs(line, stdout) == EOF)
        	printf("fputs error to pipe");
    }
    if (pclose(fpin) == -1)
    	printf("pclose error");
    putchar('\n');
    exit(0);
}

