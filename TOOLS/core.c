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
	#include "IOT__config.h"
	#include "IOT__definition.h"
	#include "SYSTEM/SYSTEM.h"
	#include "core.h"
	#include "IOT_STUDIO/IOT_STUDIO.h"
	//#include "IOT_DEBUG/IOT_DEBUG.h"
	#include "IOT_WE/WE.h"
	#include "IOT_DE/DE.h"
	#include "IOT_ME/ME.h"
	//#include "IOT_DEBUG/SYS_INFO/SYS_INFO.h"
	#include "IOT_STATISTICS/EVENT_COUNTER.h"
	//#include "MySQL/MySQL.h"
	//#include "IOT_SocDEB/SocDEB.h"
	#include "IOT_MENU/MENU.h"
	//#include "IOT_FILE_DEBUG/FILE_DEBUG.h"
	#include "IOT_FOBJECTS/FOBJECTS.h"
//#------------------------------------------------
	char Momxede_Me; // !!!!!!!!!!!!! SAGANGEBO MARKERI - amis washlit amoyris im adgilebs rolebic yuradgebas itxovs
//#------------------------------------------------
	int	 SYS_BUSY = 0;
	int  MyPID = 0;
//#------------------------------------------------
	void *Time_server( void *arg );
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#----------------------------------------------------
	long IOT_STUDIO_CHANNEL_INDEX	= 0;
	long IOT_WE_CHANNEL_INDEX		= 0;
//#----------------------------------------------------
	char DEB_ID						= 0; //Debug__IOT_DEBUG
	char DEB_IS						= 0; //Debug__IOT_STUDIO
	char DEB_ME						= 0; //Debug__DEVICE_MEDIATOR
	char DEB_DE						= 0; //Debug__DEVICE_SOCKET
	char DEB_WE						= 0; //Debug__DEVICE_WEB
//#------------------------------------------------------
	char ID_STATUS					= 0;
	char IS_STATUS					= 0;
	char ME_STATUS					= 0;
	char DE_STATUS					= 0;
	char WE_STATUS					= 0;
//#-------------------------------------------------------
	char Enable___Time_Counter 		= 1;
	char Enable___Virtula_Debug		= 1;
	char Enable___STUDIO_Server		= 1;
	char Enable___DE_Server			= 1;
	char Enable___WE_Server			= 1;
	char Enable___ME_Server			= 1;
	char Enable___SocDEB_Server		= 1;
//#-------------------------------------------------------
	char DE_virtual_debugger		= 0;
	char ME_virtual_debugger		= 0;
	char WE_virtual_debugger		= 1;
	char STUDIO_virtual_debugger	= 0;
	char SYS_INFO_virtual_debugger	= 0;
//#-------------------------------------------------------
	int main(int argc , char *argv[])
	{//FOBJECTS_init();return 0;
/**

		char TDATA[128];


		sprintf(TDATA,"555/ragac rugaca");
		int TDATA_len = strlen(TDATA);


		int i;

		char Device_Name_String[16];
		char Device_Description[64];
		unsigned long Device_Name =0;

		unsigned char Triger   = 0;
		unsigned char Cont_A   = 0;
		unsigned char Cont_B   = 0;
		unsigned char isError  = 0;

		for( i = 0; i < TDATA_len; i++ ){
			if( Triger == 0 ){
				if(isdigit(TDATA[i])!=0){
					if(Cont_A>15){ isError=1; break; }
					Device_Name_String[Cont_A] = TDATA[i];
					Cont_A ++;
				}else{ Triger = 1; continue;}
			}
			if( Triger == 1 ){
				if(Cont_B>63){ isError=1; break; }
				Device_Description[Cont_B] = TDATA[i];
				Cont_B ++;
			}
		}
		Device_Name_String[Cont_A]=0;
		if(Cont_A!=0)Device_Name=atol(Device_Name_String);
		Device_Description[Cont_B] = 0;

		if(isError == 0){
			printf("Device_Name:%ld\n\r",Device_Name);
			printf("Device_Description:%s\n\r",Device_Description);
		} else printf("isError !!!\n\r");





		return 0;

**/





		//#-----------------------------------------------
			MyPID = (int)getpid();
		//#-----------------------------------------------
			Print_Line();
			printf("Welcome to MAXIOT\n\r");
			Print_Line();
		//#-----------------------------------------------
			//#include "IOT_CORE/Init_File_DEBUG.c"
			#include "IOT_CORE/Init_Timer.c"
			#include "IOT_CORE/Init_Python.c"
			#include "IOT_CORE/Init_SYS_API.c"
			//#include "IOT_CORE/Init_SYS_INFO.c"
			#include "IOT_CORE/Init_Virtual_devices.c"


			FOBJECTS_init();
			FOBJECTS__Load_Objects();
			//#include "IOT_CORE/Init_MySQL.c"



			#include "IOT_CORE/Init_Server_treads.c"
		//#------------------------------------------------



			IOT_MENU_INIT();
			while(1){
				usleep(100000);
				if(IOT_MENU_LOOP()==1)break;
			}
		//#------------------------------------------------
			#include "IOT_CORE/DeInit_Python.c"
		//#------------------------------------------------
			Print_Line(); printf("exit !!!\n");
			return 0;
	}
//#-------------------------------------------------------
	void *Time_server( void *arg ){
		pthread_t self = pthread_self();
		struct timeval tv;
		while(1){
			gettimeofday(&tv, NULL);
			SYS_TIME_SEC = tv.tv_sec;
			//printf("Seconds since Jan. 1, 1970: %ld\n\r", SYS_TIME_SEC);
			usleep(500000);
		}
		fflush(stdout);pthread_detach(self);
		return 0;
	}
//#-------------------------------------------------------
	void Print_Line(void){
		printf("-------------------------------------------------------------------\n\r");
	}


