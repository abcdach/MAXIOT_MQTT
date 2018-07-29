
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
	#include "TOOLS/json/JSON.h"
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	#define STACK_SIZE_32	32*1024
	#define STACK_SIZE_64	64*1024
	#define STACK_SIZE_128	128*1024
	#define STACK_SIZE_256	256*1024
//#------------------------------------------------
	void *Socket_Get_Sensor(void *arg);
//#------------------------------------------------
	typedef struct {
	  int	SOCK;
	} _SATELIT;
	_SATELIT	SATELIT;
//#------------------------------------------------
	char client_message[2000];
	char Server_message[2000];
	char SATELIT_STATUS = 0;


	#define DEVICE_NAME				500
	#define DEVICE_DESCRIPTION		"Carbon Dioxide Sensor"
	#define SERVER_IP				"10.0.0.100"
	#define SERVER_PORT				3004
	#define RECONNECT				1				// 1 - kavshiris gawyvetisas gadakoneqteba


#define JSON_parse(x)	if ((JSON_Len = JSON_Parser(Server_message,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON_s_parse(x)	if ((JSON_Len = JSON_Parser(Server_message,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;




//temp + 1443

int main(int argc , char *argv[])
{
	while( 1 ){

			//#------------------------------------------------
				int sock;
				struct sockaddr_in server;
			//#------------------------------------------------
				int  read_size;
				int  STATUS = 0;
				int  sock_STATUS = 0;
			//###########################################################################################
				char JSON_Value[300];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
			//###########################################################################################
				printf("\n\r\n\r\n\r");
				printf("-------------------------------------------\n\r");
			//#------------------------------------------------
				sock = socket(AF_INET , SOCK_STREAM , 0);
				if (sock == -1)
				{
					printf("Could not create socket");
				}

				server.sin_addr.s_addr = inet_addr(SERVER_IP);
				server.sin_family = AF_INET;
				server.sin_port = htons(SERVER_PORT);
			//#------------------------------------------------
				struct pollfd fd;
				int ret;
				fd.fd = sock; // your socket handler
				fd.events = POLLIN;
			//#------------------------------------------------
			while( 1 ){
				sock_STATUS=0;
				if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
				{
					puts("connect error");
					sock_STATUS = 1;
					//return 1;
				}
				if(sock_STATUS==0)break;
				usleep(5000000);
			}
			puts("Connected\n");
		//#------------------------------------------------
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					printf("SocCli()>> Sock recv Error !!!\n\r");
					STATUS=-1;
					break;
				case 0:// Timeout
						//printf("SocCli()>> Sock recv Timeout !!!\n\r");
					break;
				default:
					read_size = recv(sock, Server_message , 2000 , 0);
				    if( read_size == 0)
				    {
				    	printf("## Server Disconnected !!!\n\r");
				    	STATUS=-1;
				    } else {
				    	Server_message[read_size]=0;
				    //#------------------------------------------------
				    	JSON_parse("C");
				    	if (JSON_STATUS == 1){
				    		////////////////////////////////////////////
				    		if(JSON_Long_Value == 1){// C = 0
				    			printf("-> %s\n\r",Server_message);
				    			JSON_parse("N");
				    			if (JSON_STATUS == 1){
									switch(JSON_Long_Value) {

										case 0:
											break;
										case 1://"Welcome"
											sprintf(client_message,"{\"C\":\"1\",\"N\":\"1\",\"D\":\"%ld\",\"i\":\"Sign me up\"}"
													,(long)DEVICE_NAME);
											printf("<- %s\n\r",client_message);
											send(sock,client_message,strlen(client_message),0);
											break;
										case 6://"Device Registered"
											//####################################################
											SATELIT_STATUS = 1;
											pthread_attr_init(&ATTR_STACK_SIZE);
											pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
											SATELIT.SOCK = sock;
											pthread_t _Socket_Get_Sensor;
											if( pthread_create( &_Socket_Get_Sensor , &ATTR_STACK_SIZE ,  Socket_Get_Sensor , (void*) &SATELIT) < 0){
												printf("SocCli>> could not create thread\n\r");
												SATELIT_STATUS = 0;
											}
											//####################################################
											break;
										case 100://"Error"
											JSON_parse("E");
											if (JSON_STATUS == 1){
												switch(JSON_Long_Value) {
													case 1://"C value not found"
														break;
													case 2://"D value not found"
														break;
													case 3://"Device not found"
														break;
													case 4://"Device type is wrong"
														break;
													case 5://"Device is already in system"
														break;
													case 6://"Could not create thread"
														break;
													case 7://"Device was deleted from system"
														break;
													default:
														break;
												}
											}
											//STATUS=-1;
											break;
										case 255://"PONG"
											break;;
										default:
											break;
									}
				    			}
				    		}
				    		////////////////////////////////////////////
				    		if(JSON_Long_Value == 0){// C = 1
				    			JSON_parse("IN");
				    			if (JSON_STATUS == 1){
				    				char IN_Value = JSON_Long_Value;
				    				char Buffer_1[300];

									JSON_s_parse("V");
									if (JSON_STATUS == 1){
										sprintf(Buffer_1, JSON_Value);
										switch(IN_Value) {

											case 0: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 1: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 2: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 3: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 4: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 5: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 6: printf("-> IN0: %s\n\r",Buffer_1); break;
											case 7: printf("-> IN0: %s\n\r",Buffer_1); break;

											default :
												break;
										}
									}
				    			}
				    		}
				    		////////////////////////////////////////////
				    	}
				    //#------------------------------------------------
				    }
					break;
			}if (STATUS==-1)break;
		}
	//#------------------------------------------------
		if(RECONNECT == 1){
			SATELIT_STATUS = 0;
			printf("## RECONNECTING\n\r");
			usleep(5000000);
		} else {
			return 0;
		}
	//#------------------------------------------------
	}
	return 0;
}

//###############################################################################
//#
//###############################################################################

void *Socket_Get_Sensor(void *arg)
{
	//##----------------------------------------------------------
		_SATELIT* SATE = (_SATELIT*)arg;
		int sock = SATE->SOCK;
		int PING_COUNTER = 0;
	//##----------------------------------------------------------
		pthread_t self;
		self = pthread_self();
	//##----------------------------------------------------------
		printf("SocCli(%d)>> thread created ***\n\r",sock);
	//##----------------------------------------------------------

//		sprintf(client_message,"{\"C\":\"1\",\"N\":\"20\",\"i\":\"Device Description\",\"V\":\"%s\"}",DEVICE_DESCRIPTION);
//		printf("<- %s\n\r",client_message);send(sock , client_message , strlen(client_message) , 0);
//		usleep(100000);
		//sprintf(client_message,"{\"C\":\"0\",\"D\":\"%d\",\"S\":\"0\",\"T\":\"10\",\"V\":\"%s\"}",DEVICE_NAME,DEVICE_DESCRIPTION);
		//printf("<- %s\n\r",client_message);send(sock , client_message , strlen(client_message) , 0);
	//##----------------------------------------------------------
	    while(1){
	    	PING_COUNTER ++;
			switch(PING_COUNTER) {
				case 0:
					break;
				case 1:
					sprintf(client_message,"{\"C\":\"1\",\"N\":\"255\",\"i\":\"PING\"}");
					printf("<- %s\n\r",client_message);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 2:
					sprintf(client_message,"{\"C\":\"1\",\"N\":\"20\",\"i\":\"Device Description\",\"V\":\"%s\"}",DEVICE_DESCRIPTION);
							printf("<- %s\n\r",client_message);send(sock , client_message , strlen(client_message) , 0);
							//usleep(100000);
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					sprintf(client_message,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"0\",\"T\":\"0\",\"V\":\"1\"}",(long)DEVICE_NAME);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 6:
					sprintf(client_message,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"0\",\"T\":\"0\",\"V\":\"2\"}",(long)DEVICE_NAME);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 7:
					sprintf(client_message,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"0\",\"T\":\"0\",\"V\":\"3\"}",(long)DEVICE_NAME);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 8:
					sprintf(client_message,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"0\",\"T\":\"0\",\"V\":\"4\"}",(long)DEVICE_NAME);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 9:
					PING_COUNTER = 0;
					break;
				default:
					break;
			}
			usleep(1000000);
			if(SATELIT_STATUS == 0){
				break;
			}
	   }
	//###############################################################################
	printf("SATELIT EXIT!!!\n\r");
    fflush(stdout);
    pthread_detach(self);
    return 0;
}



