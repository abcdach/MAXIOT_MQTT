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
	#include <mysql.h>
	#include <pthread.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	//#include "../IOT__structure.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	#include "SYS_INFO/SYS_INFO.h"
	#include "SYS_INFO/Linked_List.h"
	#include "IOT_DEBUG.h"
	#include "../TOOLS/sha1/SHA1_Calc.h"
	#include "../TOOLS/json/JSON.h"
	#include "../TOOLS/base64/base64.h"
//#------------------------------------------------
//	pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
//	pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
//#------------------------------------------------
	void WebSocket_SYS_INFO_RDATA_Processing( char *Output_Data, char *Input_Data );
	void WebSocket_SYS_INFO_TDATA_Processing( char *Output_Data, char *Input_Data );
	void *WebSocket_SYS_INFO_connection_handler(void *);
	//void *WebSocket_SYS_INFO_Get_Sensor(void *arg);
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  int	*SOCK;
	} _ABC;


void *WebSocket_SYS_INFO_server( void *arg )
{
	pthread_t self;
	self = pthread_self();
	//if(SYS_INFO_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self, 0,2,0,0);//debugger!!!

	pthread_attr_init(&ATTR_STACK_SIZE);
	pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
	//##-----------------------------------------------------------------------
    //## Starting WebSockets Server
	//##-----------------------------------------------------------------------
		int socket_desc , new_socket , c , *new_sock;
		struct sockaddr_in server , client;
	//##-----------------------------------------------------------------------
    //## Create socket
	//##-----------------------------------------------------------------------
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1){
			//printf("INFO>> Could not create socket\n\r");
		}
	//##-----------------------------------------------------------------------
    //## Prepare the sockaddr_in structure
	//##-----------------------------------------------------------------------
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( ID_SERVER_Port );
	//##-----------------------------------------------------------------------
    //## Bind
	//##-----------------------------------------------------------------------
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
			//printf("DEBUG_SERVER >> bind failed !!!\n\r");

		} else {
			//printf("DEBUG_SERVER >> bind done\n\r");
			ID_STATUS = 1;
		}
	//##-----------------------------------------------------------------------
    //## Listen
	//##-----------------------------------------------------------------------
    	listen(socket_desc , 3);
    	//printf("INFO>> Waiting for incoming connections...\n\r");
    	SYS_BUSY = 0;
    	c = sizeof(struct sockaddr_in);
    //##-----------------------------------------------------------------------
    //## Accept and incoming connection
    //##-----------------------------------------------------------------------
		while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
			//printf("DEBUG_SERVER >> Connection accepted\n\r");
			pthread_t sniffer_thread;
			new_sock = (int *)malloc(sizeof(int));
			*new_sock = new_socket;
			_ABC ABC;
			ABC.SOCK = new_sock;
			ABC.self = self;
			///////////////////////////////////////////////////////////////////////
			if( pthread_create( &sniffer_thread , &ATTR_STACK_SIZE ,  WebSocket_SYS_INFO_connection_handler , (void*) &ABC) < 0){
				//printf("DEBUG_SERVER >> could not create thread\n\r");
				//return 1;//???!!!!
			}
			///////////////////////////////////////////////////////////////////////
			//printf("INFO>> Handler assigned\n\r");
		}
		if (new_socket < 0){
			//printf("DE_SERVER >> Accept failed\n\r");
			//return 1;
		}
		//return 0;


		//#######################################################
		if(SYS_INFO_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
		//printf("WebSo>> WebSockets info Server EXIT!!!\n\r");
	    fflush(stdout);
	    //pthread_t self;
	    //self = pthread_self();
	    pthread_detach(self);
	    return 0;
}






#define WebSock_Sent(x)	sprintf(WebSocket_Server_message,"%s",x);\
		WebSocket_SYS_INFO_TDATA_Processing(Server_message,WebSocket_Server_message);\
		write(sock , Server_message , strlen(Server_message));

#define JSON_parse(x)	if ((JSON_Len = JSON_Parser(WebSocket_client_message,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON_s_parse(x)	if ((JSON_Len = JSON_Parser(WebSocket_client_message,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;


void *WebSocket_SYS_INFO_connection_handler(void *arg)
{
	//##----------------------------------------------------------
		_ABC* ABC = (_ABC*)arg;
	//##----------------------------------------------------------
		int sock = *(int*)ABC->SOCK;
	//##----------------------------------------------------------
		pthread_t parent_self;
		parent_self = ABC->self;
	//##----------------------------------------------------------
		pthread_t self;
		self = pthread_self();
	//##----------------------------------------------------------
		//if(SYS_INFO_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,22,sock,0);//debugger!!!
	//##----------------------------------------------------------
		long i;
		int  read_size;
		int  STATUS = 0;
		///////////////////////////////
		char client_message[2000];
		char Server_message[2000];
		///////////////////////////////
		char WebSocket_client_message[300];
		char WebSocket_Server_message[300];
		///////////////////////////////
		long DEVICE_NAME;
		long SLOT_INDEX;
		char data[255];
    //###########################################################################################
		char JSON_Value[300];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
    //###########################################################################################
		struct pollfd fd;
		int ret;
		fd.fd = sock; // your socket handler
		fd.events = POLLIN;
		///////////////////////////////
		//pthread_t self;
		//self = pthread_self();
		//!!!- printf("INFO(%d)>> thread created ***\n\r",sock);
	//##-----------------------------------------------------------------------
	//##		WebSocket Client Handshake ...
	//##-----------------------------------------------------------------------
		#include "function/websock/hand_shake.c"
    //###############################################################################
    //##
    //##
    //##
    //##
    //###############################################################################
	if (STATUS==0){
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					//!!!- printf("INFO(%d)>> Sock recv Error !!!\n\r",sock);
					STATUS=-1;
					break;
				case 0:// Timeout
					//printf("WebSo(%d)>> Sock recv Timeout !!!\n\r",sock);
					break;
				default:
					read_size = recv(sock, client_message , 2000 , 0);
					client_message[read_size]=0;
					if (client_message[0]!=0x81){
						//printf("INFO(%d)<<<< (0x%x) !!!\n\r",sock,client_message[0]);
						STATUS=-1;
					}
					else
					{
						//##-----------------------------------------------------------------------
							WebSocket_SYS_INFO_RDATA_Processing( WebSocket_client_message, client_message);
							//printf("WebSo(%d)<<<< %s\n\r",sock,WebSocket_client_message);
						//##-----------------------------------------------------------------------
							JSON_parse("COMM");
							if (JSON_STATUS == 1){

								switch (JSON_Long_Value) {
									case 1:
										#include "function/command/COMM_1.c"
										break;
									case 2:
										#include "function/command/COMM_2.c"
										break;
									case 3:
										#include "function/command/COMM_3.c"
										break;
									case 4:
										#include "function/command/COMM_4.c"
										break;
									case 5:
										#include "function/command/COMM_5.c"
										break;
									case 6:
										#include "function/command/COMM_6.c"
										break;
									case 7:
										break;
									default:
										break;
								}
							}
					   //##-----------------------------------------------------------------------
					}break;
			}if (STATUS==-1)break;
		}
	}
    //###############################################################################
    //#
    //###############################################################################
	//!!!- printf("INFO(%d)>> Server is disconnect Client!!!\n\r",sock);
	if(SYS_INFO_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
    close(sock);
    fflush(stdout);
    //free(socket_desc);
    pthread_detach(self);
    return 0;
}
//###############################################################################
//#
//###############################################################################
void WebSocket_SYS_INFO_TDATA_Processing( char *Output_Data, char *Input_Data )
{
	sprintf(Output_Data, "..%s",Input_Data);
	Output_Data[0]=0x81;
	Output_Data[1]=strlen(Input_Data);
}
//###############################################################################
//#
//###############################################################################
void WebSocket_SYS_INFO_RDATA_Processing( char *Output_Data, char *Input_Data )
{
	unsigned char WebSockets_Frame_Payload_len = Input_Data[1] & 0x7F;
	unsigned char WebSockets_Frame_Masking_key[4];
	long i;
	for( i=0; i<4; i++){
		WebSockets_Frame_Masking_key[i] = Input_Data[2 + i] ;
	}
	for( i=0; i<WebSockets_Frame_Payload_len; i++){
		Output_Data[i] = Input_Data[6 + i] ;
	}
	Output_Data[ WebSockets_Frame_Payload_len ] = 0x00;
	for (i = 0; i < WebSockets_Frame_Payload_len; i++){
		Output_Data[i] = Output_Data[i] ^ WebSockets_Frame_Masking_key[i % 4];
	}
}






