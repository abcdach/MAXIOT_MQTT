
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


	#define DEVICE_NAME				700
	#define DEVICE_DESCRIPTION		"Carbon Dioxide Sensor"
	#define SERVER_IP				"10.0.0.14"
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
						JSON_parse("N");
						if (JSON_STATUS == 1){
							switch(JSON_Long_Value) {

								//0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_
								case 0:
									printf("--> SocCli %s\n\r",Server_message);
									JSON_parse("S");
									if (JSON_STATUS == 1){
										char SLOT = JSON_Long_Value;
										char Buffer_1[300];

										JSON_s_parse("V");
										if (JSON_STATUS == 1){
											sprintf(Buffer_1, JSON_Value);
											switch(SLOT) {
												case 0: printf("--> SocCli IN0: %s\n\r",Buffer_1); break;
												case 1: printf("--> SocCli IN1: %s\n\r",Buffer_1); break;
												case 2: printf("--> SocCli IN2: %s\n\r",Buffer_1); break;
												case 3: printf("--> SocCli IN3: %s\n\r",Buffer_1); break;
												case 4: printf("--> SocCli IN4: %s\n\r",Buffer_1); break;
												case 5: printf("--> SocCli IN5: %s\n\r",Buffer_1); break;
												case 6: printf("--> SocCli IN6: %s\n\r",Buffer_1); break;
												case 7: printf("--> SocCli IN7: %s\n\r",Buffer_1); break;
												default :
													break;
											}
										}
									}
									break;

								//1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_
								case 1://"Welcome"
									printf("--> SocCli %s\n\r",Server_message);
									sprintf(client_message,"{\"N\":\"1\",\"D\":\"%ld\",\"V\":\"%s\"}"
											,(long)DEVICE_NAME,DEVICE_DESCRIPTION);
									printf("<-- SocCli %s\n\r",client_message);
									send(sock,client_message,strlen(client_message),0);
									break;

								//2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_2_
								case 2://"Device Registered"
									printf("--> SocCli %s\n\r",Server_message);
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

								//9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9_9
								case 9://"Error"
									printf("--> SocCli %s\n\r",Server_message);
									JSON_parse("E");
									if (JSON_STATUS == 1){
										switch(JSON_Long_Value) {
											case 1:
												break;
											case 2:
												break;
											default:
												break;
										}
									}
									break;

								default:
									break;
							}
						}
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
		//printf("SocCli(%d)>> thread created ***\n\r",sock);
	//##----------------------------------------------------------
	    while(1){
	    	long fff=0;
	    	while(1){
	    		fff ++;
	    		sprintf(client_message,"{\"N\":\"0\",\"S\":\"0\",\"V\":\"%ld\"}",fff);
	    		printf("<-- SocCli %s\n\r",client_message);
	    		send(sock , client_message , strlen(client_message) , 0);
	    		usleep(300000);
	    	}
	    	PING_COUNTER ++;
			switch(PING_COUNTER) {
				case 0:
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
					sprintf(client_message,"{\"N\":\"0\",\"S\":\"0\",\"V\":\"1\"}");
					printf("<-- SocCli %s\n\r",client_message);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 6:
					sprintf(client_message,"{\"N\":\"0\",\"S\":\"0\",\"V\":\"2\"}");
					printf("<-- SocCli %s\n\r",client_message);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 7:
					sprintf(client_message,"{\"N\":\"0\",\"S\":\"0\",\"V\":\"3\"}");
					printf("<-- SocCli %s\n\r",client_message);
					send(sock , client_message , strlen(client_message) , 0);
					break;
				case 8:
					sprintf(client_message,"{\"N\":\"0\",\"S\":\"0\",\"V\":\"4\"}");
					printf("<-- SocCli %s\n\r",client_message);
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



