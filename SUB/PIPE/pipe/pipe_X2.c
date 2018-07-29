
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
	#include "pipe_X2.h" // change !!!
//#------------------------------------------------
	#define OUT_Pipe  "X2_OUT" // change !!!
	#define IN_Pipe   "X2_IN"  // change !!!
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	#define STACK_SIZE_32	32*1024
	#define STACK_SIZE_64	64*1024
	#define STACK_SIZE_128	128*1024
	#define STACK_SIZE_256	256*1024
	#define My_pthread_signal(x,y)	pthread_mutex_lock(x);pthread_cond_signal(y);pthread_mutex_unlock(x);
	#define My_pthread_wait(x,y)	pthread_mutex_lock(x);pthread_cond_wait(y,x);pthread_mutex_unlock(x);
//#------------------------------------------------
	void *Pipe_write_tread(void *arg);
//#------------------------------------------------
	struct Pipes{
		pthread_mutex_t	mutex;
		pthread_cond_t  wait;
		char * Buff;
	} PIPE;
//###############################################################################
//#
//###############################################################################
void Pipe_write_to_X2(char *Data_Buff) // change !!!
{
	printf("###: %s",Data_Buff);

	PIPE.Buff = Data_Buff;
	My_pthread_signal(&PIPE.mutex,&PIPE.wait);
}
void Pipe_X2_init(void) // change !!!
{
	pthread_attr_init(&ATTR_STACK_SIZE);
	pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
	pthread_mutex_init(&PIPE.mutex, NULL);

	pthread_t _Pipe_write_tread;
	if( pthread_create( &_Pipe_write_tread ,&ATTR_STACK_SIZE ,Pipe_write_tread ,(void*) &PIPE) < 0){
		printf("SYS >> could not create Pipe_write_tread\n\r");
	}
}

void *Pipe_write_tread(void *arg)
{
	//## tail -n1 -f x1
	//##----------------------------------------------------------
		pthread_t self;
		self = pthread_self();
	//##----------------------------------------------------------
		while(1){
			printf("pth: %s",PIPE.Buff);

			My_pthread_wait(&PIPE.mutex,&PIPE.wait);
			int fd = open(OUT_Pipe, O_WRONLY);
			write(fd, PIPE.Buff, strlen(PIPE.Buff));
			close(fd);
	   }
	//##----------------------------------------------------------
		fflush(stdout);
		pthread_detach(self);
		return 0;
}



