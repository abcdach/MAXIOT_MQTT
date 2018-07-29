
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
	#include "PAYLOAD.h"
	#include "../MAXIOT/MAXIOT.h"
//#------------------------------------------------
	PAYLOAD_STRUCT PAYLOAD;
	char PAYLOAD_DATA[256];
	char PAYLOAD_DATA2[256];
	char PAY_DEB = 0;
//#------------------------------------------------
void *PAYLOAD_SYSTEM(void *arg){


	//

	while( 1 ){
		//###########################################################################################
			struct	sockaddr_in server;
			int		read_size;
			unsigned char STATUS = 0;
			unsigned char SOCK_STATUS = 0;
			PAYLOAD.CONNECTION_STATUS = 0;
		//###########################################################################################
			printf("\n\r\n\r\n\r");
			printf("-------------------------------------------\n\r");
			printf("... PAY : *** CONNECT TO PAYLOAD *** !!!\n\r");
			printf("-------------------------------------------\n\r");
			printf("... PAY : PAYLOAD.IP   : %s\n\r", PAYLOAD.IP   );
			printf("... PAY : PAYLOAD.PORT : %d\n\r", PAYLOAD.PORT );
			printf("... PAY : PAYLOAD.DEV  : %d\n\r", PAYLOAD.DEV  );
			printf("-------------------------------------------\n\r");
		//###########################################################################################
			PAYLOAD.SOCK = socket(AF_INET , SOCK_STREAM , 0);
			fcntl(PAYLOAD.SOCK, F_SETFL, O_NONBLOCK);// setup non blocking socket
			if (PAYLOAD.SOCK == -1){
				printf("Could not create socket");
			}
			printf("... PAY : socket created\n\r");
			server.sin_addr.s_addr = inet_addr(PAYLOAD.IP);
			server.sin_family = AF_INET;
			server.sin_port = htons(PAYLOAD.PORT);
		//###########################################################################################
			struct pollfd fd;
			int ret;
			fd.fd = PAYLOAD.SOCK; // your socket handler
			fd.events = POLLIN;
		//###########################################################################################
			while( 1 ){
				SOCK_STATUS=0;
				printf("... PAY : connect to server\n\r");
				if (connect(PAYLOAD.SOCK , (struct sockaddr *)&server , sizeof(server)) < 0)
				{
					printf("... PAY : connect error !!!\n\r");
					SOCK_STATUS = 1;
				}
				if(SOCK_STATUS==0)break;
				usleep(5000000);
			}
		//###########################################################################################
			PAYLOAD.CONNECTION_STATUS = 1;
			pthread_attr_t ATTR_STACK_SIZE;
			pthread_attr_init(&ATTR_STACK_SIZE);
			pthread_attr_setstacksize(&ATTR_STACK_SIZE, 128*1024);
			pthread_t _PAYLOAD_PING;
			if( pthread_create( &_PAYLOAD_PING , &ATTR_STACK_SIZE ,  PAYLOAD_PING , NULL) < 0){
				printf("... SYS : could not create thread\n\r");
				PAYLOAD.CONNECTION_STATUS = 0;
				STATUS=255;
			}
		//###########################################################################################
		PAYLOAD.TimeOUT = 0;
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					printf("... PAY : Sock recv Error !!!\n\r");
					STATUS=255;
					break;
				case 0:// Timeout
					PAYLOAD.TimeOUT ++;
					if(PAY_DEB==1)printf("... PAY : TimeOUT : %d\n\r",PAYLOAD.TimeOUT);
					if(PAYLOAD.TimeOUT==PAYLOAD.TimeOUT_MAX) STATUS=255;
					break;
				default:
					read_size = recv(PAYLOAD.SOCK, PAYLOAD.Server_message , 2048 , 0);
					PAYLOAD.TimeOUT = 0;
				    if( read_size == 0){
				    	printf("... PAY : Server Disconnected !!!\n\r");
				    	STATUS=255;
				    } else {
				    	PAYLOAD.Server_message[read_size]=0;
				    	//printf("--> PAY : %s\n\r",PAYLOAD.Server_message);

				    	if(PAYLOAD.Server_message[0] != 0x24){
				    		printf("--> PAY : FRAME    : ERROR !!!\n\r");
				    		break;
				    	}
				    	printf("-------------------------------------\n\r");
				    	printf("--> PAY : FRAME    : START\n\r");
				    	unsigned char PAYLOAD_DEVICE = (unsigned char )PAYLOAD.Server_message[1];
				    	printf("--> PAY : DEVICE   : 0x%02x\n\r",PAYLOAD_DEVICE);

				    	unsigned char PAYLOAD_COMMAND = (unsigned char )PAYLOAD.Server_message[2];
				    	printf("--> PAY : COMMAND  : 0x%02x\n\r",PAYLOAD_COMMAND);

				    	unsigned char PAYLOAD_DATA_LEN = (unsigned char )PAYLOAD.Server_message[3];
				    	printf("--> PAY : DATA_LEN : 0x%02x\n\r",PAYLOAD_DATA_LEN);
				    	switch(PAYLOAD_COMMAND){
							case 0://""
								break;
							case 1://""
								break;
							case 2://"PING"
								//printf("--> PAY : COMMAND  : PING\n\r");
								//char ret = 1;
								DATA_TO_IOT(0,"1");
								break;
							case 3://""
								break;
							case 4://"pasuxi baratis wakitxvaze"
								//printf("--> PAY : COMMAND  : RFID RESP\n\r");
								printf("--> PAY : TYPE     : ");
								unsigned char PAYLOAD_TYPE =(unsigned char)PAYLOAD.Server_message[4];
								switch(PAYLOAD_TYPE){
									case 1://"UFC"
										printf("UFC\n\r");
										break;
									case 2://"Barcode Reader"
										printf("Barcode Reader\n\r");
										break;
									default:
										printf("ERROR\n\r");
										break;
								}
								int PAYLOAD_id = ((int)PAYLOAD.Server_message[5] << 8) +
										  	  	  (int)PAYLOAD.Server_message[6];
								printf("--> PAY : ID       : 0x%04x\n\r",PAYLOAD_id);
								unsigned char PAYLOAD_turnstile_id = (unsigned char )PAYLOAD.Server_message[7];
								printf("--> PAY : TURNS_ID : 0x%02x\n\r",PAYLOAD_turnstile_id);
								unsigned char PAYLOAD_STATUS= (unsigned char )PAYLOAD.Server_message[8];
								printf("--> PAY : STATUS   : 0x%02x\n\r",PAYLOAD_STATUS);


								switch(PAYLOAD_STATUS){
									case 1://""
										DATA_TO_IOT(1,"1");
										break;
									case 2://""
										DATA_TO_IOT(1,"2");
										break;
									default:
										break;
								}

								break;
							default:
								break;
						}

				    }
					break;
			}if (STATUS==255)break;
		}
	//#------------------------------------------------
		PAYLOAD.CONNECTION_STATUS = 0;
		if(PAYLOAD.RECONNECT == 1){
			printf("... PAY : RECONNECTING\n\r");
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
void *PAYLOAD_PING(void *arg){
		pthread_t self;
		self = pthread_self();
	//##-----------------------------------
		printf("... PAY : PAYLOAD_PING START!!!\n\r");
	//##-----------------------------------
	    while(1){
	    	if(PAYLOAD.CONNECTION_STATUS == 0) break;

			PAYLOAD_DATA[0]=1;//COMMAND
			PAYLOAD_DATA[1]=0;//DATA_LEN
			DATA_TO_PAYLOAD(0x01,PAYLOAD_DATA);


			/**
	    	PAYLOAD_DATA[0]=0x03;
	    	PAYLOAD_DATA[1]=0x05;
	    	PAYLOAD_DATA[2]=0x02;
	    	PAYLOAD_DATA[3]=0x07;
	    	PAYLOAD_DATA[4]=0x70;
	    	PAYLOAD_DATA[5]=0x15;
	    	PAYLOAD_DATA[6]=0x2B;
	    	DATA_TO_PAYLOAD(0x01,PAYLOAD_DATA);
	    	//0x03 0x05 0x02 0x07 0x70 0x15 0x2B 0xCE 0x64
	    	 **/


	    	usleep(5000000);
	    }
	//###############################################################################
	printf("... PAY : PAYLOAD_PING EXIT!!!\n\r");
    fflush(stdout);
    pthread_detach(self);
    return 0;
}



//###############################################################################
//#
//###############################################################################

int DATA_TO_PAYLOAD(unsigned char DEVICE,char *DATA){
	if(PAYLOAD.CONNECTION_STATUS == 1){
		unsigned char i=0;
		unsigned char bias=0;
		unsigned char DATA_LEN=0;

    	PAYLOAD.client_message[bias]=0x24;bias++;
    	PAYLOAD.client_message[bias]=DEVICE;bias++;
    	PAYLOAD.client_message[bias]=DATA[0];bias++;
    	DATA_LEN = DATA[1];
    	PAYLOAD.client_message[bias]=DATA_LEN;bias++;
    	if(DATA_LEN!=0){
			for(i=2;i<DATA_LEN+2;i++){
				PAYLOAD.client_message[bias]=DATA[i];
				bias++;
			}
    	}
    	int CRC = PAYLOAD_CRC(DATA,DATA_LEN+2);
    	//printf("... PAY : CRC : 0x%04x\n\r",CRC);
    	PAYLOAD.client_message[bias]=CRC>>8;bias++;
    	PAYLOAD.client_message[bias]=CRC&0xFF;bias++;
    	for(i=0;i<bias;i++){
    		//printf("... PAY : i=%d : 0x%02x\n\r",i,PAYLOAD.client_message[i]);
    	}
    	send(PAYLOAD.SOCK,PAYLOAD.client_message,(bias+1),0);
		return 0;
	}return 1;
}

void PAYLOAD_INIT(char *IOT_IP,int IOT_PORT){
	//####################################################
	snprintf(PAYLOAD.DEV_DESCRIPTION,64,"X Sensor");
	snprintf(PAYLOAD.IP,64,"%s",IOT_IP);
	PAYLOAD.PORT = IOT_PORT;
	PAYLOAD.DEV  = 755;
	PAYLOAD.RECONNECT = 1;
	PAYLOAD.TimeOUT_MAX = 8;
	//####################################################
	pthread_attr_t ATTR_STACK_SIZE;
	pthread_attr_init(&ATTR_STACK_SIZE);
	pthread_attr_setstacksize(&ATTR_STACK_SIZE, 128*1024);

	pthread_t _PAYLOAD_SYSTEM;
	if( pthread_create( &_PAYLOAD_SYSTEM , &ATTR_STACK_SIZE ,  PAYLOAD_SYSTEM , NULL) < 0){
		printf("SocCli>> could not create thread\n\r");
	}
	//####################################################
}


 int PAYLOAD_CRC(char *data, int length){
	int crc = 0xFFFF;          // initial value
	int polynomial = 0x1021;   // 0001 0000 0010 0001  (0, 5, 12)
	if(length < 0) length = length;

	for (int k=0;k<length;k++){
		for (int i = 0; i < 8; i++) {
			char bit = ((data[k]   >> (7-i) & 1) == 1);
			char c15 = ((crc >> 15    & 1) == 1);
			crc <<= 1;
			if (c15 ^ bit) crc ^= polynomial;
		 }
	}
	crc &= 0xffff;
	return crc;
}

