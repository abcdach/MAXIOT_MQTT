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
	#include <Python.h>
//#------------------------------------------------
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../core.h"
	#include "MENU.h"
//#------------------------------------------------

char ch;

int IOT_MENU_LOOP( void ){
	scanf("%c", &ch);
	if (ch=='q') return 1;
	switch(ch){
		case '\n':
			IOT_MENU(0);
			break;
		case '1'://START Debug - IOT STUDIO
			if(DEB_IS == 0) DEB_IS=1; else DEB_IS=0;
			IOT_MENU(0);
			break;
		case '2':
			if(DEB_ME == 0) DEB_ME=1; else DEB_ME=0;
			IOT_MENU(0);
			break;
		case '3':
			if(DEB_DE == 0) DEB_DE=1; else DEB_DE=0;
			IOT_MENU(0);
			break;
		case '4':
			if(DEB_WE == 0) DEB_WE=1; else DEB_WE=0;
			IOT_MENU(0);
			break;
		case 's':
			PRINT_ALL_EVENT_COUNTERS();
			break;
		default:
			break;
	}
	return 0;
}
void IOT_MENU_INIT( void ){
	IOT_MENU_STOP_ALL();
	IOT_MENU(0);

}

void IOT_MENU_STOP_ALL( void ){
	DEB_ID = 0; //Debug__IOT_DEBUG
	DEB_IS = 0; //Debug__IOT_STUDIO
	DEB_ME = 0; //Debug__DEVICE_MEDIATOR
	DEB_DE = 0; //Debug__DEVICE_SOCKET
	DEB_WE = 0; //Debug__DEVICE_WEB
}
void IOT_MENU( char state ){
	switch(state){
		case 0:
			//printf("\n\r\n\r\n\r\n\r\n\r\n\r");
			Print_Line();
			printf("PID:%d   IS(%d) DE(%d) WE(%d)\n\r"
				,MyPID
				,IS_STATUS
				,DE_STATUS
				,WE_STATUS );
			Print_Line();
			printf("\n\r\n\r");

			printf("\t1) (%d)Debug IOT_STUDIO\n\r",DEB_IS);
			printf("\t2) (%d)Debug ME\n\r",DEB_ME);
			printf("\t3) (%d)Debug DE\n\r",DEB_DE);
			printf("\t4) (%d)Debug WE\n\r",DEB_WE);
			printf("\n\r\tq) EXIT MAXIOT\n\r");
			printf("\n\r\n\r");
			Print_Line();
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
	}
}
