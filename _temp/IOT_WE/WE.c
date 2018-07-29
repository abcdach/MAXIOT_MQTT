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
	//#include <mysql.h>
	#include <pthread.h>
	#include <sys/time.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	//#include "../IOT_DEBUG/SYS_INFO/SYS_INFO.h"
	#include "../TOOLS/sha1/SHA1_Calc.h"
	#include "../TOOLS/json/JSON.h"
	#include "../TOOLS/base64/base64.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "WE.h"
//#------------------------------------------------
	int Temp_DB = 1;
	pthread_attr_t ATTR_STACK_SIZE;
	pthread_mutex_t WebSocket_SENSOR_server_1_mutex;
//#------------------------------------------------
	unsigned short WebSOC_TDATA_Processing_2( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data );
	unsigned short WebSOC_RDATA_Processing( char *Input_Data,char *Output_Data );
	void WebSOC_TDATA_Processing( char *Output_Data, char *Input_Data );
	void *WE_pthread__DEVICE_handler(void *);
	void *WE_pthread__GET_OUTPUT_DATA(void *arg);
//#------------------------------------------------
//#
//#------------------------------------------------
	#define WE_DEVICE_NUMBER 1000
	pthread_mutex_t WE_DEVICE_mutex;
//#------------------------------------------------
	typedef struct {
	  char  WE_DEVICE__BUSY_STATUS;	// 0 - Free, 1 - Busy
	  char  INPUT[16];
	} _WE_DEVICE;
	_WE_DEVICE	WE_DEVICE[WE_DEVICE_NUMBER];
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  int	*SOCK;
	} _ABC;
//#------------------------------------------------
void *WE_pthread__Prossesor( void *arg )
{
	//#-----------------------------------------------------------------------
		long i = 0;long ii = 0;
	//#-----------------------------------------------------------------------
		for (i = 0; i < WE_DEVICE_NUMBER; i++){
			WE_DEVICE[i].WE_DEVICE__BUSY_STATUS = 0;
			for (ii = 0; ii < 16; ii++){
				WE_DEVICE[i].INPUT[ii] = 0;
			}
		}
	//#-----------------------------------------------------------------------
		pthread_t self = pthread_self();
	//#-----------------------------------------------------------------------
		//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self, 0,7,0,0);//debugger!!!
		//if(Temp_DB==1)printf("... WE_SOC(  ) -->%d\n\r",(int)self);
	//#-----------------------------------------------------------------------
		pthread_attr_init(&ATTR_STACK_SIZE);
		pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
	//#-----------------------------------------------------------------------
		pthread_mutex_init(&WebSocket_SENSOR_server_1_mutex, NULL);
		pthread_mutex_init(&WE_DEVICE_mutex, NULL);
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
			printf("WE_SERVER >>  Could not create socket\n\r");
		}
	//#-----------------------------------------------------------------------
    //# Prepare the sockaddr_in structure
	//#-----------------------------------------------------------------------
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( WE_SERVER_Port );
	//#-----------------------------------------------------------------------
    //# Bind
	//#-----------------------------------------------------------------------
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
			//printf("WE_SERVER >> bind failed !!!\n\r");
			//return 1;
		} else {
			WE_STATUS = 1;
			//printf("WE_SERVER >> bind done\n\r");
		}
	//#-----------------------------------------------------------------------
    //# Waiting for incoming connections
	//#-----------------------------------------------------------------------
    	listen(socket_desc , 3);
    	SYS_BUSY = 0;
    	c = sizeof(struct sockaddr_in);
    //#-----------------------------------------------------------------------
    //# Accept and incoming connection
    //#-----------------------------------------------------------------------
		while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
			pthread_t sniffer_thread;
			new_sock = (int *)malloc(sizeof(int));
			*new_sock = new_socket;

			pthread_mutex_lock(&WebSocket_SENSOR_server_1_mutex);
			ABC.SOCK = new_sock;
			ABC.self = self;

			if( pthread_create( &sniffer_thread , &ATTR_STACK_SIZE ,  WE_pthread__DEVICE_handler , (void*) &ABC) < 0){
				printf("WE_SERVER >> could not create thread\n\r");
				//return 1;
			}
		}
		if (new_socket < 0){
			//printf("WE_SERVER >> Accept failed\n\r");
			//return 1;
		}
		//#######################################################
		printf("WE_SERVER >> WebSockets client Server EXIT!!!\n\r");
		//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
		//if(Temp_DB==1)printf("... WE_SOC(  ) <--%d\n\r",(int)self);
	    fflush(stdout);
	    pthread_detach(self);
	    return 0;
}



#define DEB_WE_Sent(...)	if(DEB_WE==1)printf(__VA_ARGS__);

#define WE_Sent(...)		snprintf(WE_Server_Message,WE_Server_Message_LEN,__VA_ARGS__);\
							DEB_WE_Sent("<-- WE_SOC(%d) %s\n\r",sock,WE_Server_Message);\
							WebSOC_TDATA_Processing(Server_message,WE_Server_Message);\
							write(sock , Server_message , strlen(Server_message));

#define JSON_parse(x)	if ((JSON_Len = JSON_Parser(WE_Client_Message,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON_s_parse(x)	if ((JSON_Len = JSON_Parser(WE_Client_Message,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;



#define JSON2_parse(x)	if ((JSON_Len = JSON_Parser(Buffer_0,x,JSON_Value))!=-1){\
							JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;

#define JSON2_s_parse(x)	if ((JSON_Len = JSON_Parser(Buffer_0,x,JSON_Value))!=-1){\
							JSON_STATUS = 1;\
				    	   }else JSON_STATUS = -3;






typedef struct {
	pthread_t self;
	int		SOCK;
	unsigned long	MY_WE_DEVICE;
	unsigned char  	IN_DEV__INPUT;
	unsigned long	IN_DEV__SLOT_INDEX;
	unsigned long	IN_DEV__NAME;
	unsigned long  	OUT_DEV__NAME;
	unsigned char  	OUT_DEV__OUTPUT;
	char	BUSY;
} _WE_ARG;
_WE_ARG	WE_ARG;

#define client_message_LEN			1024*4
#define Server_message_LEN			1024*4
#define WE_Client_Message_LEN		1024*4
#define WE_Server_Message_LEN		1024*4
#define V_Vel_LEN					512
#define E_Vel_Text_LEN				128
void *WE_pthread__DEVICE_handler(void *arg)
{
	//##----------------------------------------------------------
		_ABC* ABC = (_ABC*)arg;
	//##----------------------------------------------------------
		int sock = *(int*)ABC->SOCK;
	//##----------------------------------------------------------
		//pthread_t parent_self = ABC->self;
		pthread_t self = pthread_self();
	//##----------------------------------------------------------
		pthread_mutex_unlock(&WebSocket_SENSOR_server_1_mutex);
    //###########################################################################################
		unsigned long MY_WE_DEVICE = 0;
		long i;
		int  read_size;
		unsigned char TA_STATUS = 0;
		long My_EVENT_COUNTER__CREATE_INTERCONN__We = 9999;
		long My_EVENT_COUNTER__DELETE_INTERCONN__We = 9999;
		///////////////////////////////
		char client_message[client_message_LEN];
		char Server_message[Server_message_LEN];
		///////////////////////////////
		char WE_Client_Message[WE_Client_Message_LEN];
		char WE_Server_Message[WE_Server_Message_LEN];
		///////////////////////////////
		unsigned char N_Vel = 0;
		unsigned char E_Vel = 0;
		unsigned char S_Vel = 0;
		char V_Vel[V_Vel_LEN];
		char E_Vel_Text[E_Vel_Text_LEN];
		///////////////////////////////
		unsigned long DEVICE_NAME=0;
		long SLOT_INDEX=0;
    //###########################################################################################
		char JSON_Value[1024];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
    //###########################################################################################
		struct pollfd fd;
		int ret;
		fd.fd = sock; // your socket handler
		fd.events = POLLIN;
	//##-----------------------------------------------------------------------
		#include "hand_shake.c"
	//##-----------------------------------------------------------------------
		//WE_Sent("{\"N\":\"1\",\"i\":\"Welcome\"}");
	//###############################################################################
	//#
	//###############################################################################
	long TimeOut_Counter = 0;
	char START = 0;


	typedef struct {
		unsigned char  Byte   ;
		unsigned char  Enable ;
		unsigned char  Step   ;
		unsigned short i      ;
		unsigned char  Error  ;
		unsigned char  Data_Ready;
		unsigned short DataCou;
		unsigned short InPUT_Frame_Len ;
		unsigned short Payload_Len;
		unsigned char  MaskIndex;
		unsigned char  Masking_key[4];
	} WebSoc_Stream;
	WebSoc_Stream	WSoc;


	WSoc.Enable     = 1;
	WSoc.Step       = 0;
	WSoc.Data_Ready = 0;
	#define WSoc_InData		 client_message
	#define WSoc_OutData	 WE_Client_Message

	if ((unsigned char)TA_STATUS==0){
		while( 1 ){
			ret = poll(&fd, 1, 1000); // 1 second for timeout
			switch (ret) {
				case -1:// Error
					TA_STATUS=255;
					break;
				case 0:// Timeout
					TimeOut_Counter ++;
					break;
				default:





					read_size = recv(sock, client_message , 4096 , 0);

					printf("read_size = %d\n\r",read_size );
					if( read_size == 0){TA_STATUS=255;break;}


					printf("\n\r---------------------------------\n\r");
					//unsigned short WeLen = WebSOC_RDATA_Processing(client_message,WE_Client_Message);
					//WE_Client_Message[WeLen]=0;
					//printf("WeLen = %d %s\n\r",WeLen,WE_Client_Message);
					//printf("\n\r---------------------------------\n\r");
					//break;


					printf("Byte  = %d\n\r", (unsigned char)client_message[0] );



					if( WSoc.Enable == 1 ){ WSoc.InPUT_Frame_Len = read_size;
						//#include "WebSoc_Stream_Processing.c"
						//------------------------------------------------
							WSoc.Error = 0;
							for( WSoc.i = 0; WSoc.i < WSoc.InPUT_Frame_Len; WSoc.i++ ){
								WSoc.Byte = WSoc_InData[WSoc.i];
								switch (WSoc.Step) {
									case 0:
										printf("S_Byte  = %d\n\r", WSoc.Byte );
										if(WSoc.Byte == 129){TA_STATUS=0;}
										else if(WSoc.Byte == 130){TA_STATUS=0;} //binaruli
										else {TA_STATUS=255;break;}
										WSoc.Step++;
										break;
									case 1:
										printf("P_Byte  = %d\n\r", WSoc.Byte );
										WSoc.Payload_Len = WSoc.Byte & 0x7F;
										if( WSoc.Payload_Len <= 125 ){WSoc.MaskIndex = 2; WSoc.Step = 4;}
										else if( WSoc.Payload_Len == 126 ){WSoc.MaskIndex = 2; WSoc.Step++;}
										else {TA_STATUS=255;break;}
										break;
									case 2: WSoc.Payload_Len = WSoc.Byte; WSoc.Step++; break;
									case 3: WSoc.Payload_Len = (WSoc.Payload_Len << 8) + WSoc.Byte; WSoc.Step++;break;
									case 4: WSoc.Masking_key[0] = WSoc.Byte; WSoc.Step++; break;
									case 5: WSoc.Masking_key[1] = WSoc.Byte; WSoc.Step++; break;
									case 6: WSoc.Masking_key[2] = WSoc.Byte; WSoc.Step++; break;
									case 7: WSoc.Masking_key[3] = WSoc.Byte; WSoc.Step++;
										printf("Payload_Len = %d\n\r",WSoc.Payload_Len);
										if( WSoc.Payload_Len == 0 ){TA_STATUS=255;break;}
										WSoc.DataCou = 0;
										break;
									case 8:
										WSoc_OutData[WSoc.DataCou] = WSoc.Byte ^ WSoc.Masking_key[WSoc.DataCou % 4];
										printf("0x%02X ",WSoc_OutData[WSoc.DataCou]);
										WSoc.DataCou ++;
										if( WSoc.DataCou==WSoc.Payload_Len ){
											WSoc.Data_Ready = 1;
											WSoc.Step = 0;
											printf("\n\rOUT\n\r");
											break;
										}
										break;
									default:
										break;
								}if(TA_STATUS!=0)break;
							}
					//------------------------------------------------
					}




					printf("case 000\n\r");

					if( WSoc.Enable == 1 ){printf("case 111\n\r");
						if( WSoc.Data_Ready == 0 ) break;

						printf("case 222\n\r");
						 WSoc.Data_Ready = 0;

						 read_size = WSoc.Payload_Len;

					}

					printf("case 333\n\r");

					WE_Client_Message[read_size]=0;
					printf("read_size:%d\n\r%s",read_size, WE_Client_Message);
					printf("case 444\n\r");
					break;















					//read_size = strlen(WE_Client_Message);

					printf("\n\r---------------------------------\n\r");
					WE_Client_Message[read_size]=0;
					printf("%s",WE_Client_Message);
					break;






					unsigned short WebSOC_Len = WebSOC_TDATA_Processing_2( WE_Client_Message,strlen(WE_Client_Message)+1,Server_message);
					write(sock , Server_message , WebSOC_Len);
					break;



					if ((unsigned char)client_message[0]!=0x81){
						DEB_WE_Sent("... WE_SOC(%d) (0x%x) !!!\n\r",sock,client_message[0]);
						TA_STATUS=255;
					}
					else
					{
						WebSOC_RDATA_Processing( WE_Client_Message, client_message);
						read_size = strlen(WE_Client_Message);
					    if( read_size == 0){
					    	TA_STATUS=255;
					    } else {
					    	if( read_size < 300 ){
								#include "WE_FRAME_PROCESSOR.c"
					    	} else {
					    		WE_Sent("{\"N\":\"9\",\"E\":\"20\",\"i\":\"Error(Data too large)\"}");
					    	}
					    }
					}break;
			}printf("TA_STATUS:%d\n\r",TA_STATUS);if(TA_STATUS!=0)break;
			//###########################################################################
			//# INTERCONNECTION DYNAMIC CONTROL !!!
			//###########################################################################
			if(START == 1){
				if(EVENT_COUNTER__CREATE_INTERCONN__We != My_EVENT_COUNTER__CREATE_INTERCONN__We){
					My_EVENT_COUNTER__CREATE_INTERCONN__We = EVENT_COUNTER__CREATE_INTERCONN__We;
					DEB_WE_Sent("... WE_SOC(%d) DEV(%ld) scanning CREATE_INTERCONN connections\n\r",sock,DEVICE_NAME);
					for (i = 0; i < INPUT_LEN; i++){
						if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i) == ENABLE){
							unsigned long OUT_DEV__NAME   = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)i);
							unsigned char OUT_DEV__OUTPUT = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)i);
							if(OUT_DEV__NAME != 0){
								if(WE_DEVICE[MY_WE_DEVICE].INPUT[i] == 0){
									 	WE_DEVICE[MY_WE_DEVICE].INPUT[i] = 1;
									 	DEB_WE_Sent("... WE_SOC(%d) ENABLE:%ld MY_WE_DEVICE:%ld\n\r",sock,i,MY_WE_DEVICE);
									//#-----------------------------------------------------------------
										WE_ARG.BUSY 				= 1;
										WE_ARG.SOCK 				= sock;
										WE_ARG.self 				= self;
										WE_ARG.MY_WE_DEVICE 		= (unsigned long)MY_WE_DEVICE;
										WE_ARG.IN_DEV__INPUT  		= (unsigned char)i;
										WE_ARG.IN_DEV__SLOT_INDEX   = (unsigned long)SLOT_INDEX;
										WE_ARG.IN_DEV__NAME 		= (unsigned long)DEVICE_NAME;
										WE_ARG.OUT_DEV__NAME 		= (unsigned long)OUT_DEV__NAME;
										WE_ARG.OUT_DEV__OUTPUT 		= (unsigned char)OUT_DEV__OUTPUT;
									//#-----------------------------------------------------------------
										pthread_t _WE_pthread__GET_OUTPUT_DATA;
										if( pthread_create( &_WE_pthread__GET_OUTPUT_DATA , &ATTR_STACK_SIZE ,  WE_pthread__GET_OUTPUT_DATA , (void*) &WE_ARG) < 0){
											printf("... WE_SOC(%d) could not create thread\n\r",sock);
											TA_STATUS = 255;
										}
									//#-----------------------------------------------------------------
										while(WE_ARG.BUSY) usleep(1000);
								}
							}
						}
					}
				}
				if(EVENT_COUNTER__DELETE_INTERCONN__We != My_EVENT_COUNTER__DELETE_INTERCONN__We){
					My_EVENT_COUNTER__DELETE_INTERCONN__We = EVENT_COUNTER__DELETE_INTERCONN__We;
					DEB_WE_Sent("... WE_SOC(%d) DEV(%ld) scanning DELETE_INTERCONN connections\n\r"
							,sock,(unsigned long)DEVICE_NAME);
					for (i = 0; i < INPUT_LEN; i++){
						if(WE_DEVICE[MY_WE_DEVICE].INPUT[i] == 1){
							if(SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)i)==0){
								WE_DEVICE[MY_WE_DEVICE].INPUT[i] = 0;
							}
						}
					}
				}
			}
		}
	}
    //###############################################################################
    //# EXIT !!!!
    //###############################################################################
		if(START == 1){
			snprintf(Server_message,Server_message_LEN,"{\"C\":\"5\",\"D\":\"%ld\"}",(unsigned long)DEVICE_NAME);
			SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,Server_message);
			pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
			pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
			pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
		//#------------------------------------------------
			WE_DEVICE[MY_WE_DEVICE].WE_DEVICE__BUSY_STATUS = 0;
			for (i = 0; i < 16; i++){
				WE_DEVICE[MY_WE_DEVICE].INPUT[i] = 0;
			}
		//#------------------------------------------------
			//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
			//if(Temp_DB==1)printf("... WE_SOC(%d) -------------------(%d)STOP !!!\n\r",sock,(int)DEVICE_NAME);
		}
	//#-----------------------------------------------------------------
		printf("... WE_SOC(%d) Server is disconnect Client!!!\n\r",sock);

    //#-----------------------------------------------------------------
		close(sock);
		fflush(stdout);
		pthread_detach(self);
		return 0;
	}
//###############################################################################
//#
//###############################################################################
#define Buffer_0_LEN		512
#define Buffer_1_LEN		512
void *WE_pthread__GET_OUTPUT_DATA(void *arg)
{
		_WE_ARG* ARG = (_WE_ARG*)arg;
	//#----------------------------------------------------------
		int sock = ARG->SOCK;
		unsigned long MY_WE_DEVICE		= ARG->MY_WE_DEVICE;
		unsigned char IN_DEV__INPUT 	= ARG->IN_DEV__INPUT;
		unsigned long IN_DEV__NAME		= ARG->IN_DEV__NAME;
		unsigned long OUT_DEV__NAME		= ARG->OUT_DEV__NAME;
		unsigned char OUT_DEV__OUTPUT 	= ARG->OUT_DEV__OUTPUT;
	//#----------------------------------------------------------
		struct timeval  xtv;
		struct timespec xts;
	//#----------------------------------------------------------
		//pthread_t parent_self = ARG->self;
		pthread_t self = pthread_self();
	//#----------------------------------------------------------
		//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,777,OUT_DEV__NAME,OUT_DEV__OUTPUT);//debugger!!!
		//if(Temp_DB==1)printf("... WE_SOC(%d) ----(%d)(%d)START\n\r",sock,(int)OUT_DEV__NAME,(int)OUT_DEV__OUTPUT);
	//#----------------------------------------------------------
		ARG->BUSY = 0;
		DEB_WE_Sent("... WE_SOC(%d) START_LISTENING DEV(%ld)OUT(%ld) --> DEV(%ld)IN(%ld)\n\r"
				,sock
				,(unsigned long)OUT_DEV__NAME
				,(unsigned long)OUT_DEV__OUTPUT
				,(unsigned long)IN_DEV__NAME
				,(unsigned long)IN_DEV__INPUT);
	//#----------------------------------------------------------
		char JSON_Value[300];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
	//#----------------------------------------------------------
		unsigned char S_Velue = 0;
		char Buffer_0[Buffer_0_LEN];
		char Buffer_1[Buffer_1_LEN];
	//#----------------------------------------------------------
		long SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)OUT_DEV__NAME);
		if(SLOT_INDEX != -1){
			while(1){
				//###############################################################################
					if((unsigned long)OUT_DEV__NAME != (unsigned long)IN_DEV__NAME){
						if(WE_DEVICE[MY_WE_DEVICE].INPUT[(unsigned char)IN_DEV__INPUT] == 0) break;
					}
					if(WE_DEVICE[MY_WE_DEVICE].WE_DEVICE__BUSY_STATUS == 0) break;
					if(SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)OUT_DEV__NAME)==-1) break;
				//###############################################################################
					gettimeofday(&xtv, NULL);
					xts.tv_sec = xtv.tv_sec;
					xts.tv_nsec = xtv.tv_usec*1000;
					xts.tv_sec += 3;

					pthread_mutex_lock(&SLOT[SLOT_INDEX].Device_cond_mutex);
					int cond = pthread_cond_timedwait(&SLOT[SLOT_INDEX].Device_condition,&SLOT[SLOT_INDEX].Device_cond_mutex, &xts);
					pthread_mutex_unlock(&SLOT[SLOT_INDEX].Device_cond_mutex);

					if(cond == 0){
						#include "WE_IN_DATA_PROCESSOR.c"
					} else {
						// TimeOUT //
					}
		   }
		}
	//###############################################################################
	WE_DEVICE[MY_WE_DEVICE].INPUT[(unsigned char)IN_DEV__INPUT] = 0;
	DEB_WE_Sent("... WE_SOC(%d) STOP_LISTENING DEV(%ld)OUT(%ld) --> DEV(%ld)IN(%ld)\n\r"
			,sock
			,(unsigned long)OUT_DEV__NAME
			,(unsigned long)OUT_DEV__OUTPUT
			,(unsigned long)IN_DEV__NAME
			,(unsigned long)IN_DEV__INPUT);
	//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
	//if(Temp_DB==1)printf("... WE_SOC(%d) ----(%d)(%d)STOP !!!\n\r",sock,(int)OUT_DEV__NAME,(int)OUT_DEV__OUTPUT);
    fflush(stdout);
    pthread_detach(self);
    return 0;
}








//###############################################################################
//#
//###############################################################################
unsigned short WebSOC_RDATA_Processing( char *Input_Data,char *Output_Data )
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


//	for( i=0; i<WebSoc_Payload_Len; i++){
//		Output_Data[i] = (unsigned char)Input_Data[WebSoc_DataStart + i] ;
//	}
	//Output_Data[ WebSoc_Payload_Len ] = 0x00;
//	for (i = 0; i < WebSoc_Payload_Len; i++){
//		Output_Data[i] = Output_Data[i] ^ WebSoc_Masking_key[i % 4];
//	}

	for (i = 0; i < WebSoc_Payload_Len; i++){
		Output_Data[i] = (unsigned char)Input_Data[WebSoc_DataStart + i]  ^ WebSoc_Masking_key[i % 4];
	}




	return WebSoc_Payload_Len;
}





//###############################################################################
//#
//###############################################################################
void WebSOC_TDATA_Processing( char *Output_Data, char *Input_Data )
{
	if( strlen(Input_Data) > 125 ){
		Input_Data[115] = 0;
		sprintf(Output_Data, "..%s,\"ER\":\"1\"}",Input_Data);
	} else {
		sprintf(Output_Data, "..%s",Input_Data);
	}
	Output_Data[0]=0x81;
	Output_Data[1]=strlen(Output_Data)-2;
}

unsigned short WebSOC_TDATA_Processing_2( char *Input_Data,unsigned short Input_Data_Len,char *Output_Data )
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
