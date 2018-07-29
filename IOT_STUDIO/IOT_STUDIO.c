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
//#------------------------------------------------
	#include "../IOT__config.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../IOT_FOBJECTS/FOBJECTS.h"


	#include "../SYSTEM/File/FILE_SYS.h"
//#------------------------------------------------
	#include "../TOOLS/sha1/SHA1_Calc.h"
	#include "../TOOLS/json/JSON.h"
	//#include "../TOOLS/base64/base64.h"
	#include "../TOOLS/base64_2/base64_2.h"
	#include "../TOOLS/AES/aes.h"
//#------------------------------------------------
	#include "IOT_STUDIO.h"
//#------------------------------------------------
	pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
//#------------------------------------------------
	pthread_mutex_t WebSocket_CLIENT_server_1_mutex;
	pthread_mutex_t WebSocket_CLIENT_server_2_mutex;
//#------------------------------------------------
	void WebSockets_RDATA_Processing( char *Output_Data, char *Input_Data );
	unsigned short WebSockets_TDATA_Processing( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data );
	void *IOT_STUDIO_SERVER_connection_handler(void *);
	void *WebSockets_Get_Sensor(void *arg);
	void inform_other_iot_studio_members(char *Frame, long USER_ID);
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  int	*SOCK;
	} _ABC;
//#------------------------------------------------
	#define DEB_STU_Sent(...)	if(DEB_IS==1)printf(__VA_ARGS__);
//#------------------------------------------------
void *IOT_STUDIO_SERVER( void *arg )
{
		pthread_t self;
		self = pthread_self();
		//if(STUDIO_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self, 0,1,0,0);//debugger!!!

		pthread_attr_init(&ATTR_STACK_SIZE);
		pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
	//#-----------------------------------------------------------------------
		pthread_mutex_init(&WebSocket_CLIENT_server_1_mutex, NULL);
		pthread_mutex_init(&WebSocket_CLIENT_server_2_mutex, NULL);
	//#-----------------------------------------------------------------------
    //# Starting WebSockets Server
	//#-----------------------------------------------------------------------
		int socket_desc , new_socket , c , *new_sock;
		struct sockaddr_in server , client;
		_ABC ABC;
	//#-----------------------------------------------------------------------
    //# Create socket
	//#-----------------------------------------------------------------------
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1){
			printf("IOT_STUDIO_SERVER >> Could not create socket\n\r");
		}
	//#-----------------------------------------------------------------------
    //# Prepare the sockaddr_in structure
	//#-----------------------------------------------------------------------
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( IS_SERVER_Port );
	//#-----------------------------------------------------------------------
    //# Bind
	//#-----------------------------------------------------------------------
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
			//printf("IOT_STUDIO_SERVER >> bind failed !!!\n\r");
			//return 1;
		} else {
			//printf("IOT_STUDIO_SERVER >> bind done\n\r");
			IS_STATUS = 1;
		}
	//#-----------------------------------------------------------------------
    //# Listen
	//#-----------------------------------------------------------------------
    	listen(socket_desc , 3);
    	//printf("IOT_STUDIO_SERVER >> Waiting for incoming connections...\n\r");
    	SYS_BUSY = 0;
    	c = sizeof(struct sockaddr_in);
    //#-----------------------------------------------------------------------
    //# Accept and incoming connection
    //#-----------------------------------------------------------------------
		while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
			DEB_STU_Sent("IOT_STUDIO_SERVER >> IOT_STU Connection accepted\n\r");
			pthread_t sniffer_thread;
			new_sock = (int *)malloc(sizeof(int));
			*new_sock = new_socket;


			pthread_mutex_lock(&WebSocket_CLIENT_server_1_mutex);
			ABC.SOCK = new_sock;
			ABC.self = self;
			///////////////////////////////////////////////////////////////////////
			if( pthread_create( &sniffer_thread , &ATTR_STACK_SIZE ,  IOT_STUDIO_SERVER_connection_handler , (void*) &ABC) < 0){
				DEB_STU_Sent("IOT_STUDIO_SERVER >> Could not create thread\n\r");
				//return 1;//???!!!!
			}
			///////////////////////////////////////////////////////////////////////
			DEB_STU_Sent("IOT_STUDIO_SERVER >> IOT_STU Handler assigned\n\r");
		}
		if (new_socket < 0){
			DEB_STU_Sent("IOT_STUDIO_SERVER >> IOT_STU Accept failed\n\r");
			//return 1;
		}
		//return 0;


		//#######################################################
		DEB_STU_Sent("IOT_STUDIO_SERVER >> WebSockets client Server EXIT!!!\n\r");
		//if(STUDIO_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
	    fflush(stdout);
	    //pthread_t self;
	    //self = pthread_self();
	    pthread_detach(self);
	    return 0;
}


#define STU_Sent(...)		snprintf(WebSocket_Server_message,WebSocket_Server_message_LEN,__VA_ARGS__);\
							DEB_STU_Sent("<-- IOT_STU(%d) %s\n\r",sock,WebSocket_Server_message);\
							Server_message_Len = WebSockets_TDATA_Processing( WebSocket_Server_message, strlen(WebSocket_Server_message), Server_message );\
							write(sock , Server_message , Server_message_Len);

#define JSON_parse(x)		if ((JSON_Len = JSON_Parser(WebSocket_client_message,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
							}else JSON_STATUS = -3;

#define JSON_s_parse(x)		if ((JSON_Len = JSON_Parser(WebSocket_client_message,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
							}else JSON_STATUS = -3;

#define Sent_Error(X,Y,Z)	STU_Sent("{\"F\":\"10\",\"V\":\"ERROR\",\"N\":\""Y"\",\"G\":\""Z"\"}");\
							DEB_STU_Sent("<-- IOT_STU(%d) %s\n\r",sock,Server_message);\
							DEB_STU_Sent("... IOT_STU(%d) "X" : ERROR("Y") : "Z"\n\r",sock);

#define Sent_OK(X)			STU_Sent("{\"F\":\"10\",\"V\":\"OK\"}");\
							DEB_STU_Sent("<-- IOT_STU(%d) %s\n\r",sock,"{\"F\":\"10\",\"V\":\"OK\"}");\
							DEB_STU_Sent("... IOT_STU(%d) "X" : OK\n\r",sock);usleep(2000);\

typedef struct {
  long USER_ID;
  pthread_t self;
  int	STATUS;
  int	INDEX;
  int	SOCK;
  long	DEVICE_NAME;
  struct timeval tv;
  struct timespec ts;
} _SATELIT;



#define SATELIT_NUMBER 100


#define client_message_LEN				4096
#define Server_message_LEN				4096
#define WebSocket_client_message_LEN	4096
#define WebSocket_Server_message_LEN	4096
#define CODE_IN_LEN						4096

void *IOT_STUDIO_SERVER_connection_handler(void *arg)
{
	//#----------------------------------------------------------
		_ABC* ABC = (_ABC*)arg;
	//#----------------------------------------------------------
		int sock = *(int*)ABC->SOCK;
	//#----------------------------------------------------------
		//pthread_t parent_self;
		//parent_self = ABC->self;
	//#----------------------------------------------------------
		pthread_t self;
		self = pthread_self();
	//#----------------------------------------------------------
		//if(STUDIO_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,11,sock,0);//debugger!!!
		pthread_mutex_unlock(&WebSocket_CLIENT_server_1_mutex);
	//#----------------------------------------------------------
		DEB_STU_Sent("... IOT_STU(%d) thread created \n\r",sock);
    //###########################################################################################
		unsigned short Server_message_Len=0;
		unsigned long i;
		unsigned long ii;
		int  read_size;
		unsigned char TA_STATUS = 0;
		///////////////////////////////
		char CODE_IN[CODE_IN_LEN];
		long CODE_LEN = 0;
		///////////////////////////////
		char client_message[client_message_LEN];
		char Server_message[Server_message_LEN];
		///////////////////////////////
		char WebSocket_client_message[WebSocket_client_message_LEN];
		char WebSocket_Server_message[WebSocket_Server_message_LEN];
		///////////////////////////////
		unsigned long DEVICE_ID;
		long SLOT_INDEX;
		unsigned char OUTPUT_ID;
		unsigned char INPUT_ID;
		unsigned long DEVICE_1_ID;
		unsigned long DEVICE_2_ID;
		long SLOT_1_INDEX;
		long SLOT_2_INDEX;
		unsigned char DEVICE_TYPE;
		unsigned char DEVICE_ROOM;
		unsigned short DEVICE_X;
		unsigned short DEVICE_Y;
		unsigned long USER_ID = 1;
		char FILE_PATH[128];
		unsigned long JSON_Long_X;
		unsigned long JSON_Long_Y;

		char AES_Temp[17];
		unsigned char AES_KEY[64];
		unsigned char AES_IN[16];
		char AES_SHA1_OutPut[64];
		char AES_SHA1_InPut[64];
		unsigned char AES_IV[16];
		unsigned char SECURITY_HAND_SHAKE = 0;

		unsigned short Time_OUT = 0;
    //###########################################################################################
		long SATELIT_COUNTER=0;
		_SATELIT SATELIT[SATELIT_NUMBER];
		for (i = 0; i < SATELIT_NUMBER; i++){
				SATELIT[i].USER_ID	= 0;
				SATELIT[i].self	    = 0;
				SATELIT[i].STATUS	= 0;
				SATELIT[i].INDEX    = 0;
				SATELIT[i].SOCK     = 0;
				SATELIT[i].DEVICE_NAME = 0;
			 }
    //###########################################################################################
		char JSON_Value[4096];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
    //###########################################################################################
		struct pollfd fd;
		int ret;
		fd.fd = sock; // your socket handler
		fd.events = POLLIN;
	//###############################################################################
		#include "function/HAND_SHAKE.c"

    //###############################################################################
    //##
    //##
    //###############################################################################
	if ( TA_STATUS == 0 ){
		#include "function/SECURITY_HAND_SHAKE.c"
		Time_OUT = 3;
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					DEB_STU_Sent("... WebSo(%d) Sock recv Error !!!\n\r",sock);
					TA_STATUS=255;
					break;
				case 0:// Timeout
					if( SECURITY_HAND_SHAKE == 1){
						STU_Sent("{\"F\":\"16\",\"I\":\"%ld\"}",SYS_TIME_SEC);
					}
					if( SECURITY_HAND_SHAKE == 2){
						TA_STATUS=255;
					}
					//DEB_STU_Sent("... WebSo(%d) Time_OUT : %d\n\r",sock,Time_OUT);
					Time_OUT --;
					if ( Time_OUT == 0 ) TA_STATUS=255;
					break;
				default:
					read_size = recv(sock, client_message, client_message_LEN, 0);
					client_message[read_size]=0;
					if ((unsigned char)client_message[0]!=0x81){
						DEB_STU_Sent("--> IOT_STU(%d) (0x%x) !!!\n\r",sock,client_message[0]);
						TA_STATUS=255;
					}
					else
					{
						WebSockets_RDATA_Processing( WebSocket_client_message, client_message);
						DEB_STU_Sent("--> IOT_STU(%d) %s\n\r",sock,WebSocket_client_message);
					//##-----------------------------------------------------------------------
						JSON_parse("F");
						if (JSON_STATUS == 1){

							if( SECURITY_HAND_SHAKE == 0 ){
								if( JSON_Long_Value != 0 ){
									break;
								}
							}
							Time_OUT = 60000;
							switch(JSON_Long_Value){
								case 0://SECURITY_HAND_SHAKE
									JSON_s_parse("X");
									if (JSON_STATUS == 1){
										if( strlen(JSON_Value) > 0 ){

											for (i = 0; i < 32; ++i){
												if(JSON_Value[i] != AES_Temp[i]){ SECURITY_HAND_SHAKE = 2; TA_STATUS = 255; break; }
											}

											if(TA_STATUS==0){
												SECURITY_HAND_SHAKE = 1;
												#include "function/GET_COMPONENT_LIST.c"
												#include "function/SELF_LISTENING.c"
											}
										} else { TA_STATUS = 255; break; }
									} else { TA_STATUS = 255; break; }
									break;
								case 1://CREATE DEVICE //ERROR
									#include "function/command/CREATE_DEVICE.c"
									break;
								case 2://UPDATE DEVICE //ERROR
									#include "function/command/UPDATE_DEVICE.c"
									break;
								case 3://DELETE DEVICE //ERROR
									#include "function/command/DELETE_DEVICE.c"
									break;
								case 4://CREATE OUTPUT //ERROR
									#include "function/command/CREATE_OUTPUT.c"
									break;
								case 5://DELETE_OUTPUT //ERROR
									#include "function/command/DELETE_OUTPUT.c"
									break;
								case 6://CREATE_INPUT //ERROR
									#include "function/command/CREATE_INPUT.c"
									break;
								case 7://DELETE_INPUT //ERROR
									#include "function/command/DELETE_INPUT.c"
									break;
								case 8://CREATE_INTERCONN //ERROR
									#include "function/command/CREATE_INTERCONN.c"
									break;
								case 9://DELETE_INTERCONN //ERROR
									#include "function/command/DELETE_INTERCONN.c"
									break;
								case 10://READ_MeCODE //ERROR
									#include "function/command/READ_Me_DATA.c"
									break;
								case 11://WRITE_MeCODE
									#include "function/command/WRITE_Me_DATA.c"
									break;
								case 12://READ_InOut_Config
									//#include "function/command/READ_InOut_DATA.c"
									break;
								case 13://SAVE_InOut_Config
									//#include "function/command/WRITE_InOut_DATA.c"
									break;
								case 14://START_STREAMING
									#include "function/command/START_STREAMING.c"
									break;
								case 15://STOP_STREAMING ( gasaketebelia !!! )
									//#include "function/command/STOP_STREAMING.c"
									break;
								case 16://SYS_TIME_SEC ( gasaketebelia !!! )
									//#include "function/command/STOP_STREAMING.c"
									break;
								case 20://READ_FILE_DATA
									#include "function/command/READ_FILE_DATA.c"
									break;
								default:
									break;
							}if(TA_STATUS!=0)break;
						}if(TA_STATUS!=0)break;
					//##-----------------------------------------------------------------------
					}if(TA_STATUS!=0)break;
			}if (TA_STATUS!=0)break;
		}
		//##-----------------------------------------------------------------------
		//##	EXIT ALL SATELITES !!!
		//##-----------------------------------------------------------------------
			for (i = 0; i < SATELIT_COUNTER; i++) SATELIT[i].STATUS=0;
			usleep(2000000);
	}
    //###############################################################################
    //#
    //###############################################################################
	DEB_STU_Sent("... IOT_STU(%d) Server is disconnect Client!!!\n\r",sock);
	//if(STUDIO_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
    close(sock);
    fflush(stdout);
    pthread_detach(self);
    return 0;
}
//###############################################################################
//#
//###############################################################################

void *WebSockets_Get_Sensor(void *arg)
{
		_SATELIT* SATELIT = (_SATELIT*)arg;
	//#----------------------------------------------------------
		pthread_t  self = pthread_self();
	//#----------------------------------------------------------
		long DEVICE_NAME = SATELIT->DEVICE_NAME;
	//#----------------------------------------------------------
		char Server_message[300];
		char WebSocket_Server_message[300];
	//###############################################################################
		long SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);
		if(SLOT_INDEX != -1){
			while(1){
				//###########################################################################
				if (SATELIT->STATUS == 0) break;
				if (SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME) == -1)break;
				//###########################################################################
				gettimeofday(&SATELIT->tv, NULL);
				SATELIT->ts.tv_sec = SATELIT->tv.tv_sec;
				SATELIT->ts.tv_nsec = SATELIT->tv.tv_usec*1000;
				SATELIT->ts.tv_sec += 3;

				pthread_mutex_lock(&SLOT[SLOT_INDEX].Device_cond_mutex);
				int cond = pthread_cond_timedwait(&SLOT[SLOT_INDEX].Device_condition,&SLOT[SLOT_INDEX].Device_cond_mutex, &SATELIT->ts);
				pthread_mutex_unlock(&SLOT[SLOT_INDEX].Device_cond_mutex);

				if(cond == 0){
					SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX, WebSocket_Server_message);
					if (strlen(WebSocket_Server_message)>1){
						if(SATELIT->STATUS==2){
							//printf("... IOT_STU(%d) >> %s\n\r",SATELIT->SOCK,WebSocket_Server_message);
							unsigned short Server_message_Len = WebSockets_TDATA_Processing( WebSocket_Server_message, strlen(WebSocket_Server_message), Server_message );
							write(SATELIT->SOCK , Server_message , Server_message_Len);
						}
					}
				} else {
					/// TimeOUT !!! ///
				}
		   }
		}
	//###############################################################################
	DEB_STU_Sent("... IOT_STU(%d) SATELIT(%d) EXIT!!!\n\r",SATELIT->SOCK,SATELIT->INDEX);
    fflush(stdout);
    pthread_detach(self);
    return 0;
}


















//###############################################################################
//#
//###############################################################################
void WebSockets_RDATA_Processing( char *Output_Data, char *Input_Data )
{
	unsigned short WebSoc_Payload_Len = (unsigned char)Input_Data[1] & 0x7F;
	unsigned char  WebSoc_MaskIndex = 2;
	unsigned char  WebSoc_Masking_key[4];
	if(WebSoc_Payload_Len==126){
		WebSoc_MaskIndex = 4;
		WebSoc_Payload_Len = (unsigned char)Input_Data[2];
		WebSoc_Payload_Len = (WebSoc_Payload_Len << 8)+(unsigned char)Input_Data[3];
	}
	else if(WebSoc_Payload_Len==127){
		WebSoc_MaskIndex = 6;
		WebSoc_Payload_Len = 0;
	}
	unsigned short i;
	for( i=0; i<4; i++){
		WebSoc_Masking_key[i] = (unsigned char)Input_Data[WebSoc_MaskIndex + i] ;
	}
	unsigned char WebSoc_DataStart = WebSoc_MaskIndex + 4;
	for( i=0; i<WebSoc_Payload_Len; i++){
		Output_Data[i] = (unsigned char)Input_Data[WebSoc_DataStart + i] ;
	}
	Output_Data[ WebSoc_Payload_Len ] = 0x00;
	for (i = 0; i < WebSoc_Payload_Len; i++){
		Output_Data[i] = Output_Data[i] ^ WebSoc_Masking_key[i % 4];
	}
}
//###############################################################################
//#
//###############################################################################
unsigned short WebSockets_TDATA_Processing( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data )
{
    unsigned short DATA_Cou  = 0;
    unsigned  char DATA[10];
    DATA[0] = 0x81;

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












