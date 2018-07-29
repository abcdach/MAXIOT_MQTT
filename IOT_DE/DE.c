//#------------------------------------------------
	#define _GNU_SOURCE
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
	#include <ctype.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../TOOLS/json/JSON.h"
	#include "../TOOLS/sha1/SHA1_Calc.h"
	#include "DE.h"
//#------------------------------------------------
	#define DEB_DEV(...)	if(DEB_DE==1)printf(__VA_ARGS__);
//#------------------------------------------------
	void *DE_pthread__DEVICE_handler(void *);
	void *DE_pthread__GET_OUTPUT_DATA(void *arg);
	unsigned short DE_WebSOC_TDATA_Processing( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data );


	#include "MQTT/Pthread__MQTT_Publish_Message_.c"


//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  int	*SOCK;
	} _ABC5;
//#------------------------------------------------

void *Socket_Devices_server( void *arg )
{
	pthread_t self;
	self = pthread_self();
//-----------------------------------------------------------------------
	pthread_attr_init(&ATTR_STACK_SIZE);
	pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
//-----------------------------------------------------------------------
	int socket_desc , new_socket , c , *new_sock;
	struct sockaddr_in server , client;
//-----------------------------------------------------------------------
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		DEB_DEV("DE_SERVER >> Could not create socket\n\r");
	}
//-----------------------------------------------------------------------
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( DE_SERVER_Port );
//-----------------------------------------------------------------------
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
		//DEB_DEV("DE_SERVER >> bind failed !!!\n\r");
	} else {
		//DEB_DEV("DE_SERVER >> bind done\n\r");
		DE_STATUS = 1;
	}
//-----------------------------------------------------------------------
	listen(socket_desc , 3);
	SYS_BUSY = 0;
	c = sizeof(struct sockaddr_in);
//-----------------------------------------------------------------------
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
		pthread_t _DE_pthread__DEVICE_handler;
		new_sock = (int *)malloc(sizeof(int));
		*new_sock = new_socket;
		_ABC5 ABC;
		ABC.SOCK = new_sock;
		ABC.self = self;
		///////////////////////////////////////////////////////////////////////
		if( pthread_create( &_DE_pthread__DEVICE_handler , &ATTR_STACK_SIZE ,  DE_pthread__DEVICE_handler , (void*) &ABC) < 0){
			DEB_DEV("DE_SERVER >> could not create thread\n\r");
		}
	}
	if (new_socket < 0){
		DEB_DEV("DE_SERVER >> Accept failed\n\r");
	}
//-----------------------------------------------------------------------
	DEB_DEV("DE_SERVER >> Sockets client Server EXIT!!!\n\r");
	//if(DE_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
	fflush(stdout);
	pthread_detach(self);
	return 0;
}










void *DE_pthread__DEVICE_handler(void *arg)
{
	//-----------------------------------------------------
		typedef struct {
			unsigned char	TimeOut;
			unsigned short  TimeOut_MAX;
					 char   RxFRAME[4096];
			unsigned short  FRAME_LEN;
					 char   TxFRAME[4096];
					 int	Sock;
		} _TCPSoc; _TCPSoc	TCPSoc;

		TCPSoc.TimeOut     = 0;
		TCPSoc.TimeOut_MAX = 10;
		TCPSoc.RxFRAME[0]  = 0;
		TCPSoc.TxFRAME[0]  = 0;
		TCPSoc.FRAME_LEN   = 0;
	//-----------------------------------------------------



	//-----------------------------------------------------
		_ABC5* ABC = (_ABC5*)arg;
		TCPSoc.Sock = *(int*)ABC->SOCK;
		pthread_t self = pthread_self();
	//-----------------------------------------------------
		long i;
		unsigned char TA_STATUS = 0;

		#include "MQTT/Variables.c"
		#include "WebSoc/Variables.c"
	//-----------------------------------------------------
		struct pollfd fd;fd.fd = TCPSoc.Sock;fd.events = POLLIN;
		while( 1 ){
			switch (poll(&fd, 1, 1000)) {
				case -1: TA_STATUS = 255; break;
				case  0: TCPSoc.TimeOut ++;if( TCPSoc.TimeOut > (TCPSoc.TimeOut_MAX + 4) )TA_STATUS=255;
					//DEB_DEV("... DE_SOC(%d) TCPSoc.TimeOut: %d\n\r",TCPSoc.Sock,TCPSoc.TimeOut);
					break;
				default:
				//-------------------------------------------------------
					TCPSoc.FRAME_LEN = recv(TCPSoc.Sock, TCPSoc.RxFRAME , 4096 , 0);
					if( TCPSoc.FRAME_LEN == 0 )  { TA_STATUS = 255; break; }
					if( TCPSoc.FRAME_LEN > 4096 ){ TA_STATUS = 255; break; }
					TCPSoc.RxFRAME[TCPSoc.FRAME_LEN] = 0;
					DEB_DEV("... DE_SOC(%d) ***** TCPSoc.FRAME_LEN = %d \n\r",TCPSoc.Sock,TCPSoc.FRAME_LEN);
				//-------------------------------------------------------

					if( WSoc.Protocol_Scanner == 0 ){ WSoc.Protocol_Scanner = 1;
						#include "WebSoc/Protocol_Scanner.c"
						if( WSoc.Enable == 1 ) break;
					}

					if( WSoc.Enable == 1 ){
						#include "WebSoc/FRAME_PROCESSOR.c"
						if( TA_STATUS != 0 ) break;
						if(WSoc.Data_Ready == 1 ) WSoc.Data_Ready = 0; else break;
						MQTT_InData_Len = WSoc.Payload_Len;
						for( WSoc.i = 0; WSoc.i < WSoc.Payload_Len; WSoc.i ++ ) MQTT_InData[WSoc.i]  =  WSoc_OutData[WSoc.i];
					}

					#include "MQTT/FRAME_PROCESSOR.c"
					if( TA_STATUS == 255 ) break;

					if(MQTT.TxStatus == 1){ MQTT.TxStatus = 0;
						if( WSoc.Enable == 0) write(TCPSoc.Sock , MQTT_OutData , MQTT.OutData_Len);
						if( WSoc.Enable == 1){
							#include "WebSoc/TxDATA_Processing.c"
							write(TCPSoc.Sock , MQTT_InData , Len);
						}
					}

					break;
			}if( TA_STATUS != 0 ) break;
		//-----------------------------------------------
			if(DEV.START == 1){
				DEV.SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEV.ID);
				if(DEV.SLOT_INDEX == -1) {
					DEB_DEV("... DE_SOC(%d) DEV.SLOT_INDEX == -1 !!!\n\r",TCPSoc.Sock);
					break;
				}
			}
		//-----------------------------------------------
	}
    //###############################################################################
	for (DEV.InID = 0; DEV.InID < INPUT_LEN; DEV.InID++ ){
		SYS_API__PUT__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.InID, IS_NOT_SUBSCRIBE);
	}
	//###############################################################################
	if(DEV.START == 1){DEB_DEV("... DE_SOC(%d) START == 1\n\r",TCPSoc.Sock);
		DEV.SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEV.ID);
		if(DEV.SLOT_INDEX != -1){

			if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX) == IS_RUN){
				SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX, IS_NOT_RUN);
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld RUN_STATUS IS == IS_NOT_RUN  !!!\n\r",TCPSoc.Sock, DEV.ID);
			}

			//#---IOT STUDIO---------------------------------------------
				sprintf(MQTT_OutData, "{\"C\":\"5\",\"D\":\"%ld\",\"V\":\"0\"}",DEV.ID );
				DEB_DEV("... DE_SOC(%d) %s\n\r",TCPSoc.Sock,MQTT_OutData);
			//#------------------------------------------------
				SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(DEV.SLOT_INDEX,MQTT_OutData);
				pthread_mutex_lock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
				pthread_cond_broadcast( &SLOT[DEV.SLOT_INDEX].Device_condition );
				pthread_mutex_unlock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
			//#------------------------------------------------
		}
	}

    //###############################################################################
	DEB_DEV("... DE_SOC(%d) Server - Client(%ld) is disconnected !!!\n\r",TCPSoc.Sock,DEV.ID);

    close(TCPSoc.Sock);
    fflush(stdout);
    //free(sock); ????????????????
    pthread_detach(self);
    return 0;
}


#include "MQTT/Pthread__MQTT_Publish_Message.c"



















/**
unsigned short DE_WebSOC_TDATA_Processing( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data )
{
    unsigned short DATA_Cou  = 0;
    unsigned  char DATA[10];
    //DATA[0] = 0x81;
    DATA[0] = 0x82; // binaruli

    if(Input_Data_Len <= 125){
        DATA[1] = (unsigned char) Input_Data_Len;
        DATA_Cou = 2;
    }else if(Input_Data_Len >= 126 && Input_Data_Len <= 65535){
        DATA[1] =  126;
        DATA[2] = (unsigned char)(Input_Data_Len >> 8);
        DATA[3] = (unsigned char)(Input_Data_Len & 0x00FF);
        DATA_Cou = 4;
    }else{
        return 0;
    }
    unsigned short i = 0;
    unsigned short b = 0;
    for(i=0; i<DATA_Cou;i++){
        Output_Data[b] = DATA[i]; b++;
    }
    for(i=0; i<Input_Data_Len;i++){
        Output_Data[b] = Input_Data[i]; b++;
    }
    return DATA_Cou + Input_Data_Len;
}
**/
