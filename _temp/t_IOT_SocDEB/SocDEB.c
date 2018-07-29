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
	#include <sys/time.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	//#include "../IOT_DEBUG/SYS_INFO/SYS_INFO.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../TOOLS/json/JSON.h"
	#include "SocDEB.h"
//#------------------------------------------------
	void *SocDEB_pthread__DEVICE_handler(void *);
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  int	*SOCK;
	} _ABC5;
//#------------------------------------------------

void *SocDEB_Devices_server( void *arg )
{
		pthread_t self;
		self = pthread_self();
		//if(DE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self, 0,5,0,0);//debugger!!!

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
			printf("SDEB_SERVER >> Could not create socket\n\r");
		}
	//##-----------------------------------------------------------------------
    //## Prepare the sockaddr_in structure
	//##-----------------------------------------------------------------------
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( SocDEB_SERVER_Port );
	//##-----------------------------------------------------------------------
    //## Bind
	//##-----------------------------------------------------------------------
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
			printf("SDEB_SERVER >> bind failed !!!\n\r");
		} else {
			printf("SDEB_SERVER >> bind done\n\r");
			DE_STATUS = 1;
		}
	//##-----------------------------------------------------------------------
    //## Listen
	//##-----------------------------------------------------------------------
    	listen(socket_desc , 3);
    	//printf("DE_SERVER >> Waiting for incoming connections...\n\r");
    	SYS_BUSY = 0;
    	c = sizeof(struct sockaddr_in);
    //##-----------------------------------------------------------------------
    //## Accept and incoming connection
    //##-----------------------------------------------------------------------
		while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
			pthread_t _SocDEB_pthread__DEVICE_handler;
			new_sock = (int *)malloc(sizeof(int));
			*new_sock = new_socket;
			_ABC5 ABC;
			ABC.SOCK = new_sock;
			ABC.self = self;
			///////////////////////////////////////////////////////////////////////
			if( pthread_create( &_SocDEB_pthread__DEVICE_handler , &ATTR_STACK_SIZE ,  SocDEB_pthread__DEVICE_handler , (void*) &ABC) < 0){
				printf("SDEB_SERVER >> could not create thread\n\r");
			}
		}
		if (new_socket < 0){
			printf("SDEB_SERVER >> Accept failed\n\r");
		}
		//#######################################################
		printf("SDEB_SERVER >> Sockets client Server EXIT!!!\n\r");
		//if(DE_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
	    fflush(stdout);
	    pthread_detach(self);
	    return 0;
}


#define JSON_parse(x)	if ((JSON_Len = JSON_Parser(JSON_FRAME,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON_s_parse(x)	if ((JSON_Len = JSON_Parser(JSON_FRAME,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON2_parse(x)	if ((JSON_Len = JSON_Parser(Buffer_1,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON2_s_parse(x)	if ((JSON_Len = JSON_Parser(Buffer_1,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;


void *SocDEB_pthread__DEVICE_handler(void *arg)
{
	//##----------------------------------------------------------
		_ABC5* ABC = (_ABC5*)arg;
	//##----------------------------------------------------------
		int sock = *(int*)ABC->SOCK;
	//##----------------------------------------------------------
		//pthread_t parent_self;
		//parent_self = ABC->self;
	//##----------------------------------------------------------
		pthread_t self;
		self = pthread_self();
	//##----------------------------------------------------------
		if(1==1)printf("... SDEB_SERVER(%d) SENSOR CONNECTED !!!\n\r",sock);
    //###########################################################################################
		long i;
		long  read_size;
		int  STATUS = 0;
		//char START = 0;
		//char ERROR_EXIT = 0;
		//char JF_i = 0;
		//char JF = 0;
		///////////////////////////////
		//char N_Vel = 0;
		//char E_Vel = 0;
		//char S_Vel = 0;
		//char V_Vel[300];
		//char E_Vel_Text[100];
		///////////////////////////////
		char server_message[10240];
		char client_message[1024];
		//char JSON_FRAME[300];
		///////////////////////////////
		long DEVICE_NAME;
		long SLOT_INDEX;
    //###########################################################################################
		//char JSON_Value[300];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
    //###########################################################################################
		struct pollfd fd;
		int ret;
		fd.fd = sock;
		fd.events = POLLIN;
	//###############################################################################
		sprintf(server_message, "0,1,2,3,4,5,6,7,8,9" );
		if(1==1)printf("<-- SDEB(%d) %s\r",sock,server_message);
		write(sock, server_message, strlen(server_message));
    //###############################################################################
		while( 1 ){
			ret = poll(&fd, 1, 2000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					if(1==1)printf("... SDEB(%d)>> Sock recv Error !!!\n\r",sock);
					STATUS=-1;
					break;
				case 0:// Timeout
					//TimeOut_Counter ++;
					//if(DEB_DE==1)printf("... DE_SOC(%d) TimeOut_Counter: %ld\n\r",sock,TimeOut_Counter);
					//if(TimeOut_Counter > 10){
						//STATUS=-1;
					//}
					printf("... SDEB(%d) TimeOut_Counter\n\r",sock);
					break;
				default:
					//TimeOut_Counter = 0;
					read_size = recv(sock, client_message , 1024 , 0);
					client_message[read_size]=0;
					if( read_size == 0){
						STATUS=-1;
					} else {
						printf("--> SDEB(%d)(%ld) %s\n\r",sock,read_size,client_message);


						for( i = 0; i < 100; i ++ ){

							DEVICE_NAME = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(i);//d0
							SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);//d1

							//if(SLOT_INDEX != -1){
								sprintf(server_message,
										"1,%ld,%ld,%ld,%ld,%ld,%ld,%s,%ld,%ld,%ld,%s,"
										"_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_,"
										"_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_,"
										"_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_,"
										"_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_%ld_,"
										":"
										, i
										, DEVICE_NAME
										, SLOT_INDEX
										, (long)SLOT[SLOT_INDEX].DEVICE.TYPE
										, (long)SLOT[SLOT_INDEX].DEVICE.X
										, (long)SLOT[SLOT_INDEX].DEVICE.Y
										, SLOT[SLOT_INDEX].DEVICE.DESCRIPTION
										, (long)SLOT[SLOT_INDEX].DEVICE.ID
										, (long)SLOT[SLOT_INDEX].DEVICE.ROOM
										, (long)SLOT[SLOT_INDEX].DEVICE.DATA_STATUS
										, SLOT[SLOT_INDEX].DEVICE.DESCRIPTION

										, (long)SLOT[SLOT_INDEX].INPUT[0].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[1].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[2].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[3].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[4].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[5].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[6].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[7].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[8].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[9].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[10].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[11].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[12].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[13].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[14].STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[15].STATUS

										, (long)SLOT[SLOT_INDEX].INPUT[0].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[1].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[2].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[3].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[4].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[5].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[6].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[7].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[8].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[9].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[10].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[11].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[12].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[13].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[14].LISTEN_DEVICE_NAME
										, (long)SLOT[SLOT_INDEX].INPUT[15].LISTEN_DEVICE_NAME

										, (long)SLOT[SLOT_INDEX].INPUT[0].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[1].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[2].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[3].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[4].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[5].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[6].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[7].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[8].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[9].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[10].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[11].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[12].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[13].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[14].LISTEN_DEVICE_OUTPUT_INDEX
										, (long)SLOT[SLOT_INDEX].INPUT[15].LISTEN_DEVICE_OUTPUT_INDEX

										, (long)SLOT[SLOT_INDEX].INPUT[0].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[1].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[2].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[3].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[4].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[5].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[6].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[7].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[8].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[9].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[10].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[11].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[12].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[13].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[14].LISTEN_STATUS
										, (long)SLOT[SLOT_INDEX].INPUT[15].LISTEN_STATUS
										);



								//char 	STATUS;							// 1 - enable , 0 -disable
								//char	DESCRIPTION[INPUT_DESCRIPTION_LEN];
								//long	LISTEN_DEVICE_NAME; 			// mowyobilobis saxeli romesac usmens
								//char	LISTEN_DEVICE_OUTPUT_INDEX; 	// mowyobilobis gamosasvlelis indexi romesac usmens
								//char	LISTEN_STATUS; 					// 1 - ismineba / 0 - ar ismineba

							//} else {
						//	sprintf(server_message,"1,%ld,%ld,%ld,%ld,%ld,%ld,%ld,:"
							//			, i
							//			, (long)-1
							//			, (long)-1
							//			, (long)-1
							//			, (long)-1
							//			, (long)-1
							//			, (long)-1);
							//}

							write(sock, server_message, strlen(server_message));
							usleep(200000);
						}//SLOT[SLOT_INDEX].DEVICE.DATA_STATUS = STATUS;





					}break;
			}if (STATUS==-1)break;
		}

    //###############################################################################
    //#
    //###############################################################################
	if(1==1)printf("... SDEB_SERVER(%d) Server is disconnect Client!!!\n\r",sock);
    close(sock);
    fflush(stdout);
    pthread_detach(self);
    return 0;
}






