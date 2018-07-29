// export PS1='> '
// tar -cvf 002.tar iot/
//#------------------------------------------------
	#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
	#include <stdlib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>    //strlen
	//#include <sys/socket.h>
	//#include <arpa/inet.h> //inet_addr
	#include <poll.h>
	#include <sys/types.h>
	#include <unistd.h>
	//#include <mysql.h>
	//#include <pthread.h>
	//#include <Python.h>
	//#include <sys/time.h>
//#------------------------------------------------
	//#include "../IOT__config.h"
	////#include "../IOT__structure.h"
	//#include "../IOT__definition.h"
	//#include "../SYSTEM/SYSTEM.h"
	//#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	//#include "../core.h"
//#------------------------------------------------
	//#include "MEDIATOR.h"
	//#include "../TOOLS/json/JSON.h"
	//#include "../TOOLS/base64_2/base64_2.h"
//#------------------------------------------------
	//#include "../IOT_INFO/SYS_INFO/SYS_INFO.h"
	//#include "../IOT_INFO/SYS_INFO/Linked_List.h"
//#------------------------------------------------
#include "EVENT_COUNTER.h"
//#include "../IOT_STATISTICS/EVENT_COUNTER.h"


//#------------------------------------------------
//#	IOT_STUDIO
//#------------------------------------------------

long	EVENT_COUNTER__CREATE_DEVICE = 0;		//OK,PRINT
long	EVENT_COUNTER__CREATE_DEVICE__De = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_DEVICE__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_DEVICE__We = 0;	//OK,PRINT

long	EVENT_COUNTER__UPDATE_DEVICE = 0;		//OK,PRINT
long	EVENT_COUNTER__UPDATE_DEVICE__De = 0;	//OK,PRINT
long	EVENT_COUNTER__UPDATE_DEVICE__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__UPDATE_DEVICE__We = 0;	//OK,PRINT

long	EVENT_COUNTER__DELETE_DEVICE = 0;		//OK,PRINT
long	EVENT_COUNTER__DELETE_DEVICE__De = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_DEVICE__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_DEVICE__We = 0;	//OK,PRINT

long	EVENT_COUNTER__CREATE_OUTPUT = 0;		//OK,PRINT
long	EVENT_COUNTER__CREATE_OUTPUT__De = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_OUTPUT__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_OUTPUT__We = 0;	//OK,PRINT

long	EVENT_COUNTER__DELETE_OUTPUT = 0;		//OK,PRINT
long	EVENT_COUNTER__DELETE_OUTPUT__De = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_OUTPUT__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_OUTPUT__We = 0;	//OK,PRINT

long	EVENT_COUNTER__CREATE_INPUT = 0;		//OK,PRINT
long	EVENT_COUNTER__CREATE_INPUT__De = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_INPUT__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_INPUT__We = 0;	//OK,PRINT

long	EVENT_COUNTER__DELETE_INPUT = 0;		//OK,PRINT
long	EVENT_COUNTER__DELETE_INPUT__De = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_INPUT__Me = 0;	//OK,PRINT
long	EVENT_COUNTER__DELETE_INPUT__We = 0;	//OK,PRINT

long	EVENT_COUNTER__CREATE_INTERCONN = 0;	//OK,PRINT
long	EVENT_COUNTER__CREATE_INTERCONN__De = 0;//OK,PRINT
long	EVENT_COUNTER__CREATE_INTERCONN__Me = 0;//OK,PRINT
long	EVENT_COUNTER__CREATE_INTERCONN__We = 0;//OK,PRINT

long	EVENT_COUNTER__DELETE_INTERCONN = 0;
long	EVENT_COUNTER__DELETE_INTERCONN__De = 0;//OK,PRINT
long	EVENT_COUNTER__DELETE_INTERCONN__Me = 0;//OK,PRINT
long	EVENT_COUNTER__DELETE_INTERCONN__We = 0;//OK,PRINT

long	EVENT_COUNTER__READ_MeCODE = 0;
long	EVENT_COUNTER__WRITE_MeCODE = 0;
long	EVENT_COUNTER__READ_InOut_Config = 0;
long	EVENT_COUNTER__SAVE_InOut_Config = 0;
long	EVENT_COUNTER__START_STREAMING = 0;
long	EVENT_COUNTER__STOP_STREAMING = 0;


void PRINT_ALL_EVENT_COUNTERS( void ){

	printf("\n\r\n\rALL_EVENT_COUNTERS:\n\r");
	printf("EVENT_COUNTER__CREATE_DEVICE - %ld\n\r",EVENT_COUNTER__CREATE_DEVICE);
	printf("EVENT_COUNTER__CREATE_DEVICE__De - %ld\n\r",EVENT_COUNTER__CREATE_DEVICE__De);
	printf("EVENT_COUNTER__CREATE_DEVICE__Me - %ld\n\r",EVENT_COUNTER__CREATE_DEVICE__Me);
	printf("EVENT_COUNTER__CREATE_DEVICE__We - %ld\n\r",EVENT_COUNTER__CREATE_DEVICE__We);
	printf("\n\r");
	printf("EVENT_COUNTER__UPDATE_DEVICE - %ld\n\r",EVENT_COUNTER__UPDATE_DEVICE);
	printf("EVENT_COUNTER__UPDATE_DEVICE__De - %ld\n\r",EVENT_COUNTER__UPDATE_DEVICE__De);
	printf("EVENT_COUNTER__UPDATE_DEVICE__Me - %ld\n\r",EVENT_COUNTER__UPDATE_DEVICE__Me);
	printf("EVENT_COUNTER__UPDATE_DEVICE__We - %ld\n\r",EVENT_COUNTER__UPDATE_DEVICE__We);
	printf("\n\r");
	printf("EVENT_COUNTER__DELETE_DEVICE - %ld\n\r",EVENT_COUNTER__DELETE_DEVICE);
	printf("EVENT_COUNTER__DELETE_DEVICE__De - %ld\n\r",EVENT_COUNTER__DELETE_DEVICE__De);
	printf("EVENT_COUNTER__DELETE_DEVICE__Me - %ld\n\r",EVENT_COUNTER__DELETE_DEVICE__Me);
	printf("EVENT_COUNTER__DELETE_DEVICE__We - %ld\n\r",EVENT_COUNTER__DELETE_DEVICE__We);
	printf("\n\r");
	printf("EVENT_COUNTER__CREATE_OUTPUT - %ld\n\r",EVENT_COUNTER__CREATE_OUTPUT);
	printf("EVENT_COUNTER__CREATE_OUTPUT__De - %ld\n\r",EVENT_COUNTER__CREATE_OUTPUT__De);
	printf("EVENT_COUNTER__CREATE_OUTPUT__Me - %ld\n\r",EVENT_COUNTER__CREATE_OUTPUT__Me);
	printf("EVENT_COUNTER__CREATE_OUTPUT__We - %ld\n\r",EVENT_COUNTER__CREATE_OUTPUT__We);
	printf("\n\r");
	printf("EVENT_COUNTER__DELETE_OUTPUT - %ld\n\r",EVENT_COUNTER__DELETE_OUTPUT);
	printf("EVENT_COUNTER__DELETE_OUTPUT__De - %ld\n\r",EVENT_COUNTER__DELETE_OUTPUT__De);
	printf("EVENT_COUNTER__DELETE_OUTPUT__Me - %ld\n\r",EVENT_COUNTER__DELETE_OUTPUT__Me);
	printf("EVENT_COUNTER__DELETE_OUTPUT__We - %ld\n\r",EVENT_COUNTER__DELETE_OUTPUT__We);
	printf("\n\r");
	printf("EVENT_COUNTER__CREATE_INPUT - %ld\n\r",EVENT_COUNTER__CREATE_INPUT);
	printf("EVENT_COUNTER__CREATE_INPUT__De - %ld\n\r",EVENT_COUNTER__CREATE_INPUT__De);
	printf("EVENT_COUNTER__CREATE_INPUT__Me - %ld\n\r",EVENT_COUNTER__CREATE_INPUT__Me);
	printf("EVENT_COUNTER__CREATE_INPUT__We - %ld\n\r",EVENT_COUNTER__CREATE_INPUT__We);
	printf("\n\r");
	printf("EVENT_COUNTER__DELETE_INPUT - %ld\n\r",EVENT_COUNTER__DELETE_INPUT);
	printf("EVENT_COUNTER__DELETE_INPUT__De - %ld\n\r",EVENT_COUNTER__DELETE_INPUT__De);
	printf("EVENT_COUNTER__DELETE_INPUT__Me - %ld\n\r",EVENT_COUNTER__DELETE_INPUT__Me);
	printf("EVENT_COUNTER__DELETE_INPUT__We - %ld\n\r",EVENT_COUNTER__DELETE_INPUT__We);
	printf("\n\r");
	printf("EVENT_COUNTER__CREATE_INTERCONN - %ld\n\r",EVENT_COUNTER__CREATE_INTERCONN);
	printf("EVENT_COUNTER__CREATE_INTERCONN__De - %ld\n\r",EVENT_COUNTER__CREATE_INTERCONN__De);
	printf("EVENT_COUNTER__CREATE_INTERCONN__Me - %ld\n\r",EVENT_COUNTER__CREATE_INTERCONN__Me);
	printf("EVENT_COUNTER__CREATE_INTERCONN__We - %ld\n\r",EVENT_COUNTER__CREATE_INTERCONN__We);
	printf("\n\r");
	printf("EVENT_COUNTER__DELETE_INTERCONN - %ld\n\r",EVENT_COUNTER__DELETE_INTERCONN);
	printf("EVENT_COUNTER__DELETE_INTERCONN__De - %ld\n\r",EVENT_COUNTER__DELETE_INTERCONN__De);
	printf("EVENT_COUNTER__DELETE_INTERCONN__Me - %ld\n\r",EVENT_COUNTER__DELETE_INTERCONN__Me);
	printf("EVENT_COUNTER__DELETE_INTERCONN__We - %ld\n\r",EVENT_COUNTER__DELETE_INTERCONN__We);
	printf("\n\r");
}













