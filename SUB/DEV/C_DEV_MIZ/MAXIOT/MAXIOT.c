
//#------------------------------------------------
//#	export PS1='> '
//#	tar -cvf 002.tar iot/
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
	#include <fcntl.h>   /* open(), creat() - and fcntl() */
//#------------------------------------------------
	#include "../TOOLS/json/JSON.h"
	#include "MAXIOT.h"
	#include "../PAYLOAD/PAYLOAD.h"
//#------------------------------------------------
	MAXIOT_STRUCT MAXIOT;
//#------------------------------------------------
	#define SENT_TO_IOT(...)	sprintf(MAXIOT.client_message,__VA_ARGS__);\
								if(SYS_DEB==1)printf("<-- SYS : %s\n\r",MAXIOT.client_message);\
								send(MAXIOT.SOCK , MAXIOT.client_message , strlen(MAXIOT.client_message) , 0);

	#define JSON_parse(x)		if ((JSON_Len = JSON_Parser(MAXIOT.Server_message,x,JSON_Value))!=-1){\
								JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   	   }else JSON_STATUS = -3;

	#define JSON_s_parse(x)		if ((JSON_Len = JSON_Parser(MAXIOT.Server_message,x,JSON_Value))!=-1){\
								JSON_STATUS = 1;\
				    	   	   }else JSON_STATUS = -3;
//#------------------------------------------------
char SYS_DEB = 0;
void *MAXIOT_SYSTEM(void *arg){
	while( 1 ){
		//###########################################################################################
			struct	sockaddr_in server;
			int		read_size;
			unsigned char STATUS = 0;
			unsigned char SOCK_STATUS = 0;
			MAXIOT.CONNECTION_STATUS = 0;
		//###########################################################################################
			char JSON_Value[512];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
		//###########################################################################################
			printf("\n\r\n\r\n\r");
			printf("-------------------------------------------\n\r");
			printf("... SYS : *** CONNECT TO MAXIOT *** !!!\n\r");
			printf("-------------------------------------------\n\r");
			printf("... SYS : MAXIOT.IP   : %s\n\r", MAXIOT.IP   );
			printf("... SYS : MAXIOT.PORT : %d\n\r", MAXIOT.PORT );
			printf("... SYS : MAXIOT.DEV  : %d\n\r", MAXIOT.DEV  );
			printf("-------------------------------------------\n\r");
		//###########################################################################################
			MAXIOT.SOCK = socket(AF_INET , SOCK_STREAM , 0);
			fcntl(MAXIOT.SOCK, F_SETFL, O_NONBLOCK);// setup non blocking socket
			if (MAXIOT.SOCK == -1){
				printf("Could not create socket");
			}
			server.sin_addr.s_addr = inet_addr(MAXIOT.IP);
			server.sin_family = AF_INET;
			server.sin_port = htons(MAXIOT.PORT);
		//###########################################################################################
			struct pollfd fd;
			int ret;
			fd.fd = MAXIOT.SOCK; // your socket handler
			fd.events = POLLIN;
		//###########################################################################################
			while( 1 ){
				SOCK_STATUS=0;
				printf("... SYS : connect to server\n\r");
				if (connect(MAXIOT.SOCK , (struct sockaddr *)&server , sizeof(server)) < 0)
				{
					printf("... SYS : connect error !!!\n\r");
					SOCK_STATUS = 1;
				}
				if(SOCK_STATUS==0)break;
				usleep(5000000);
			}
		//###########################################################################################
		MAXIOT.TimeOUT = 0;
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					printf("... SYS : Sock recv Error !!!\n\r");
					STATUS=255;
					break;
				case 0:// Timeout
					MAXIOT.TimeOUT ++;
					if(SYS_DEB==1)printf("... SYS : TimeOUT : %d\n\r",MAXIOT.TimeOUT);
					if(MAXIOT.TimeOUT==MAXIOT.TimeOUT_MAX) STATUS=255;
					break;
				default:
					read_size = recv(MAXIOT.SOCK, MAXIOT.Server_message , 2048 , 0);
					MAXIOT.TimeOUT = 0;
				    if( read_size == 0){
				    	printf("... SYS : Server Disconnected !!!\n\r");
				    	STATUS=255;
				    } else {
				    	MAXIOT.Server_message[read_size]=0;
						JSON_parse("N");
						if (JSON_STATUS == 1){
							switch(JSON_Long_Value) {

								case 0://"Data"
									#include "case/Data.c"
									break;
								case 1://"Welcome"
									#include "case/Welcome.c"
									break;
								case 2://"Device_Registered"
									#include "case/Device_Registered.c"
									break;
								case 3:break;
								case 4:// bolo migebuli damaxsovrebuli imformacia
									if(SYS_DEB==1)printf("... SYS : case(4)\n\r");
									if(SYS_DEB==1)printf("--> SYS : %s\n\r",MAXIOT.Server_message);
									break;
								case 5:break;
								case 6:break;
								case 7:
									if(SYS_DEB==1)printf("--> SYS : %s\n\r",MAXIOT.Server_message);
									break;
								case 8:break;
								case 9://"Error"
									#include "case/Data.c"
									break;
								default:
									break;
							}
						}
				    }
					break;
			}if (STATUS==255)break;
		}
	//#------------------------------------------------
		MAXIOT.CONNECTION_STATUS = 0;
		if(MAXIOT.RECONNECT == 1){
			printf("... SYS : RECONNECTING\n\r");
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
void *MAXIOT_PING(void *arg){
		pthread_t self;
		self = pthread_self();
	//##-----------------------------------
		printf("... SYS : MAXIOT_PING START!!!\n\r");
	//##-----------------------------------
	    while(1){
	    	if(MAXIOT.CONNECTION_STATUS == 0) break;
	    	SENT_TO_IOT("{\"N\":\"8\",\"i\":\"PING\"}\n");
	    	usleep(5000000);
	    }
	//###############################################################################
	printf("... SYS : MAXIOT_PING EXIT!!!\n\r");
    fflush(stdout);
    pthread_detach(self);
    return 0;
}



//###############################################################################
//#
//###############################################################################

int DATA_TO_IOT(unsigned char SLOT, char *DATA){
	if(MAXIOT.CONNECTION_STATUS == 1){
		SENT_TO_IOT("{\"N\":\"0\",\"S\":\"%d\",\"V\":\"%s\"}",SLOT,DATA);
		return 0;
	}return 1;
}

void MAXIOT_INIT(char *IOT_IP,int IOT_PORT){
	//####################################################
	snprintf(MAXIOT.DEV_DESCRIPTION,64,"X SERVER");
	snprintf(MAXIOT.IP,64,"%s",IOT_IP);
	MAXIOT.PORT = IOT_PORT;
	MAXIOT.DEV  = 755;
	MAXIOT.RECONNECT = 1;
	MAXIOT.TimeOUT_MAX = 8;
	//####################################################
	pthread_attr_t ATTR_STACK_SIZE;
	pthread_attr_init(&ATTR_STACK_SIZE);
	pthread_attr_setstacksize(&ATTR_STACK_SIZE, 128*1024);

	pthread_t _MAXIOT_SYSTEM;
	if( pthread_create( &_MAXIOT_SYSTEM , &ATTR_STACK_SIZE ,  MAXIOT_SYSTEM , NULL) < 0){
		printf("SocCli>> could not create thread\n\r");
	}
	//####################################################
}



