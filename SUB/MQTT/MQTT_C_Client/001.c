
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
	unsigned char Server_message[2000];
	char SATELIT_STATUS = 0;

	#define SERVER_IP				"198.41.30.241"
	#define SERVER_PORT				1883

	unsigned char  Frame[2048];
	unsigned short Frame_Len;
	unsigned short MQTT__Subscribe_Request( unsigned char * Frame, char * Topic );
	unsigned short MQTT__Connect_Command( unsigned char * Frame);
	unsigned short MQTT__Publish_Message(char * Topic , char * Message );



int main(int argc , char *argv[])
{
	unsigned short i = 0;


	//Frame_Len = MQTT__Publish_Message("dach_dach/x","12345");
	//for( i = 0; i < Frame_Len; i++ ) printf("0x%02X\n",Frame[i]);
	//return 0;




	while( 1 ){

			//#------------------------------------------------
				int sock;
				struct sockaddr_in server;
			//#------------------------------------------------
				int  read_size;
				int  STATUS = 0;
				//int  sock_STATUS = 0;
			//###########################################################################################
				printf("\n\r\n\r\n\r");
				printf("1-------------------------------------------\n\r");
			//#------------------------------------------------
				printf("Create socket ...\n\r");
				sock = socket(AF_INET , SOCK_STREAM , 0);
				if (sock == -1)
				{
					printf("Could not create socket\n\r");
				}else{printf("Create socket ok\n\r");}

				server.sin_addr.s_addr = inet_addr(SERVER_IP);
				server.sin_family = AF_INET;
				server.sin_port = htons(SERVER_PORT);
			//#------------------------------------------------
				struct pollfd fd;
				int ret;
				fd.fd = sock; // your socket handler
				fd.events = POLLIN;
			//#------------------------------------------------
			//while( 1 ){
				//sock_STATUS=0;
				printf("connect... \n\r");
				if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
				{
					printf("connect error\n\r");
					//sock_STATUS = 1;
					return 1;
				} else {printf("connect ok\n\r");}
				//if(sock_STATUS==0)break;
				//usleep(5000000);
			//}



			printf("Connected\n");


		//#------------------------------------------------
			Frame_Len = MQTT__Connect_Command(Frame);
			printf("Connect_Command\n");printf("C -> S  ");for( i = 0; i < Frame_Len; i++ ) printf("%02X ",Frame[i]);printf("\n");
			send(sock , Frame , Frame_Len , 0);
		//#------------------------------------------------
		    int STEP = 0;

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
				    	printf("S -> C  ");for( i = 0; i < read_size; i++ ) printf("%02X ",Server_message[i]);printf("\n");
						switch (STEP){
							case 0: //Subscribe Request
								Frame_Len = MQTT__Subscribe_Request(Frame,"dach_dach/x");
								printf("Subscribe_Request\n");printf("C -> S  ");for( i = 0; i < Frame_Len; i++ ) printf("%02X ",Frame[i]);printf("\n");
								send(sock , Frame , Frame_Len , 0);
								STEP ++;
								break;
							case 1:
								Frame_Len = MQTT__Publish_Message("dach_dach/x","12345");
								printf("Publish_Message\n");printf("C -> S  ");for( i = 0; i < Frame_Len; i++ ) printf("%02X ",Frame[i]);printf("\n");
								send(sock , Frame , Frame_Len , 0);
								STEP ++;
								break;
							case 2:
								break;
							default:
								break;
						}
				    }
					break;
			}if (STATUS==-1)break;
		}
	//#------------------------------------------------
		//if(RECONNECT == 1){
		//	SATELIT_STATUS = 0;
		//	printf("## RECONNECTING\n\r");
		//	usleep(5000000);
		//} else {
		//	return 0;
		//
		//}
	//#------------------------------------------------
	}
	return 0;
}

unsigned short MQTT__Connect_Command( unsigned char * Frame){

	unsigned  short  i                     = 0;
	unsigned  short  FC                    = 0;
	static const char Protocol_Name[]      = "MQTT";
	unsigned  short   Protocol_Name_Length = strlen(Protocol_Name);
	static const char Client_ID[]          = "";
	unsigned  short   Client_ID_Length     = strlen(Client_ID);
	unsigned  char   Header_Flags          = 0x10;
	unsigned  char   Msg_Len               = Protocol_Name_Length + 8 + Client_ID_Length;
	unsigned  char   Version               = 0x04; //MQTT v3.1.1 (4)
	unsigned  char   Connect_Flags         = 0x02;
	unsigned  short  Keep_Alive            = 20;


	Frame[FC++] = Header_Flags;
	Frame[FC++] = Msg_Len;
	Frame[FC++] = (char)(Protocol_Name_Length & 0xFF00)>>8;
	Frame[FC++] = (char)(Protocol_Name_Length & 0x00FF);
	for( i = 0; i < Protocol_Name_Length; i++ ) Frame[FC++] = Protocol_Name[i];
	Frame[FC++] = Version;
	Frame[FC++] = Connect_Flags;
	Frame[FC++] = (char)(Keep_Alive & 0xFF00)>>8;
	Frame[FC++] = (char)(Keep_Alive & 0x00FF);
	Frame[FC++] = (char)(Client_ID_Length & 0xFF00)>>8;
	Frame[FC++] = (char)(Client_ID_Length & 0x00FF);
	for( i = 0; i < Client_ID_Length; i++ ) Frame[FC++] = Protocol_Name[i];

	return FC;
}
unsigned short MQTT__Subscribe_Request( unsigned char * Frame, char * Topic ){

	unsigned  short  i                  = 0;
	unsigned  short  Topic_Length       = strlen(Topic);
	unsigned  char   Header_Flags       = 0x82;
	unsigned  char   Msg_Len            = (char)Topic_Length + 5;
	unsigned  short  Message_Identifier = 0x0001;
	unsigned  short  FC                 = 0;

	Frame[FC++] = Header_Flags;
	Frame[FC++] = Msg_Len;
	Frame[FC++] = (char)(Message_Identifier & 0xFF00)>>8;
	Frame[FC++] = (char)(Message_Identifier & 0x00FF);
	Frame[FC++] = (char)(Topic_Length & 0xFF00)>>8;
	Frame[FC++] = (char)(Topic_Length & 0x00FF);
	for( i = 0; i < Topic_Length; i++ ) Frame[FC++] = Topic[i];
	Frame[FC++] = 0x00;
	return FC;
}
unsigned short MQTT__Publish_Message(char * Topic , char * Message ){

	unsigned  short  i                  = 0;
	unsigned  short  Topic_Length       = strlen(Topic);
	unsigned  short  Message_Length     = strlen(Message);
	unsigned  char   Header_Flags       = 0x30;
	unsigned  char   Msg_Len            = (char)Topic_Length + (char)Message_Length + 2;
	unsigned  short  FC                 = 0;

	Frame[FC++] = Header_Flags;
	Frame[FC++] = Msg_Len;
	Frame[FC++] = (char)(Topic_Length & 0xFF00)>>8;
	Frame[FC++] = (char)(Topic_Length & 0x00FF);
	for( i = 0; i < Topic_Length; i++ ) Frame[FC++] = Topic[i];
	for( i = 0; i < Message_Length; i++ ) Frame[FC++] = Message[i];
	return FC;
}




