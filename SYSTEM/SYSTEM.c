//##############################################################
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <pthread.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	#include "../IOT__definition.h"
	#include "SYSTEM.h"
//#------------------------------------------------
	#include "Device/DEVSYS.h"
	#include "Messege/MSGSYS.h"
	#include "Slot/SLOTSYS.h"
	#include "File/FILE_SYS.h"
//##############################################################
	long SYS_TIME_SEC = 0;
//#------------------------------------------------
	pthread_mutex_t SYS_API_mutex;
	pthread_mutex_t MSGSYS_mutex;
	long SYS_Signal_Counter__Add_Sensor_Input = 0;
	_SLOT SLOT[SLOT_Len+10];
//#------------------------------------------------
	void _SYS_API__PrinOUT_Device_Buffer(long Count);

//##############################################################
void SYS_API__init(){
	pthread_mutex_init(&SYS_API_mutex, NULL);
	pthread_mutex_init(&MSGSYS_mutex, NULL);
	DEVSYS__init();
	SLOTSYS__init();
	MSGSYS__init();
}
//##############################################################
void SYS_API__PTHREAD_WAIT__By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	pthread_mutex_lock(&SLOT[SLOT_INDEX].Device_cond_mutex);
	pthread_cond_wait(&SLOT[SLOT_INDEX].Device_condition,&SLOT[SLOT_INDEX].Device_cond_mutex);
	pthread_mutex_unlock(&SLOT[SLOT_INDEX].Device_cond_mutex);
}
void SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	pthread_mutex_init(&SLOT[SLOT_INDEX].Device_cond_mutex, NULL);
	pthread_cond_init(&SLOT[SLOT_INDEX].Device_condition, NULL);
}
//##############################################################
void SYS_API__PUT__DEVICE_ROOM_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char ROOM){//$
	SLOT[SLOT_INDEX].DEVICE.ROOM = ROOM;
}
unsigned char SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.ROOM;
}
//##############################################################
void SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned long DEVICE_USER_INDEX){//$
	SLOT[SLOT_INDEX].DEVICE.USER_INDEX = DEVICE_USER_INDEX;
}
unsigned long SYS_API__GET__DEVICE_USER_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.USER_INDEX;
}
//##############################################################
void SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char DEVICE_TYPE){//$
	SLOT[SLOT_INDEX].DEVICE.TYPE = DEVICE_TYPE;
}
unsigned char SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.TYPE;
}
//##############################################################
void SYS_API__PUT__DEVICE_X_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned short DEVICE_X){//$
	SLOT[SLOT_INDEX].DEVICE.X = DEVICE_X;
}
unsigned short SYS_API__GET__DEVICE_X_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.X;
}
void SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned short DEVICE_Y){//$
	SLOT[SLOT_INDEX].DEVICE.Y = DEVICE_Y;
}
unsigned short SYS_API__GET__DEVICE_Y_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.Y;
}
//##############################################################
void SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *DESCRIPTION){//$
	sprintf(SLOT[SLOT_INDEX].DEVICE.DESCRIPTION,"%s",DESCRIPTION);
}
char *SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	char *Temp = SLOT[SLOT_INDEX].DEVICE.DESCRIPTION;
	return Temp;
}
//##############################################################
void SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *DATA){//$
	sprintf(SLOT[SLOT_INDEX].DEVICE.DATA,"%s",DATA);
}
char *SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.DATA;
}
//##############################################################
void SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char STATUS){//$
	SLOT[SLOT_INDEX].DEVICE.DATA_STATUS = STATUS;
}
unsigned char SYS_API__GET__DEVICE_DATA_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.DATA_STATUS;
}
//##############################################################
void SYS_API__PUT__INPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, char *DESCRIPTION){//$
	sprintf(SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].DESCRIPTION,"%s",DESCRIPTION);
}
char *SYS_API__GET__INPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	char *Temp = SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].DESCRIPTION;
	return Temp;
}
void SYS_API__PUT__INPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, char *CONFIG_DATA){//$
	sprintf(SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].CONFIG_DATA,"%s",CONFIG_DATA);
}
char *SYS_API__GET__INPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	char *Temp = SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].CONFIG_DATA;
	return Temp;
}
//##############################################################
void SYS_API__PUT__OUTPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *DESCRIPTION){//$
	sprintf(SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].DESCRIPTION,"%s",DESCRIPTION);
}
char *SYS_API__GET__OUTPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX){//$
	char *Temp = SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].DESCRIPTION;
	return Temp;
}
void SYS_API__PUT__OUTPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *CONFIG_DATA){//$
	sprintf(SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].CONFIG_DATA,"%s",CONFIG_DATA);
}
char *SYS_API__GET__OUTPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX){//$
	char *Temp = SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].CONFIG_DATA;
	return Temp;
}
//##############################################################
void SYS_API__PUT__INPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char INPUT_STATUS){//$
	SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].STATUS = INPUT_STATUS;
}
unsigned char SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].STATUS ;
}
//##############################################################
void SYS_API__PUT__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char INPUT_STATUS){//$
	SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].MQTT_SUBSCRIBE_STATUS = INPUT_STATUS;
}
unsigned char SYS_API__GET__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].MQTT_SUBSCRIBE_STATUS ;
}
//##############################################################
void SYS_API__PUT__OUTPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, unsigned char OUTPUT_STATUS){//$
	SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].STATUS = OUTPUT_STATUS;
}
unsigned char SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX){//$
	return SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].STATUS ;
}
//##############################################################
void SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned long LISTEN_DEVICE_NAME){//$
	SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_DEVICE_NAME = LISTEN_DEVICE_NAME;
}
void SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char LISTEN_DEVICE_OUTPUT_INDEX){//$
	SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_DEVICE_OUTPUT_INDEX = LISTEN_DEVICE_OUTPUT_INDEX;
}
unsigned long SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_DEVICE_NAME;
}
unsigned char SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_DEVICE_OUTPUT_INDEX;
}
//##############################################################
void SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char STATUS){//$
	SLOT[SLOT_INDEX].RUN_STATUS = STATUS;
}
unsigned char SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].RUN_STATUS;
}
//##############################################################
void SYS_API__PUT__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char STATUS){//$
	SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_STATUS = STATUS;
}
unsigned char SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].INPUT[INPUT_INDEX].LISTEN_STATUS;
}
//##############################################################
void SYS_API__CLEANING__DEVICE_By_SLOT_INDEX(unsigned long SLOT_INDEX){//$

		long i=0;
	//#---------------------------------------------------
		SLOT[SLOT_INDEX].MSG_Number  = 0;
		SLOT[SLOT_INDEX].MSG_Pointer = 0;
	//#---------------------------------------------------
	//# _DEVICE
	//#---------------------------------------------------
		SLOT[SLOT_INDEX].DEVICE.ROOM = 0;
		SLOT[SLOT_INDEX].DEVICE.USER_INDEX = -1;
		SLOT[SLOT_INDEX].DEVICE.ID = 0;
		SLOT[SLOT_INDEX].DEVICE.TYPE = 0;
		SLOT[SLOT_INDEX].DEVICE.X = 0;
		SLOT[SLOT_INDEX].DEVICE.Y = 0;
		SLOT[SLOT_INDEX].DEVICE.DESCRIPTION[0] = 0;
		SLOT[SLOT_INDEX].DEVICE.DATA[0] = 0;
		SLOT[SLOT_INDEX].DEVICE.DATA_STATUS = 0;
	//#---------------------------------------------------
	//# _INPUT
	//#---------------------------------------------------
		for (i = 0; i < INPUT_LEN; i++){
			SLOT[SLOT_INDEX].INPUT[i].STATUS = 0;
			SLOT[SLOT_INDEX].INPUT[i].DESCRIPTION[0] = 0;
			SLOT[SLOT_INDEX].INPUT[i].LISTEN_DEVICE_NAME = 0;
			SLOT[SLOT_INDEX].INPUT[i].LISTEN_DEVICE_OUTPUT_INDEX = 0;
			SLOT[SLOT_INDEX].INPUT[i].LISTEN_STATUS = 0;
			SLOT[SLOT_INDEX].INPUT[i].CONFIG_DATA[0] = 0;
			SLOT[SLOT_INDEX].INPUT[i].MQTT_SUBSCRIBE_STATUS = 0;
		}
	//#---------------------------------------------------
	//# _OUTPUT
	//#---------------------------------------------------
		for (i = 0; i < OUTPUT_LEN; i++){
			SLOT[SLOT_INDEX].OUTPUT[i].STATUS = 0;
			SLOT[SLOT_INDEX].OUTPUT[i].DESCRIPTION[0] = 0;
			SLOT[SLOT_INDEX].OUTPUT[i].LAST_DATA[0]  = 0;
			SLOT[SLOT_INDEX].OUTPUT[i].LAST_DATA_TIME = 0;
			SLOT[SLOT_INDEX].OUTPUT[i].CONFIG_DATA[0] = 0;
		}
	//#---------------------------------------------------
	//# _MEDIATOR
	//#---------------------------------------------------
		SLOT[SLOT_INDEX].MEDIATOR.STATUS = 0;
		for (i = 0; i < 4; i++){
			SLOT[SLOT_INDEX].MEDIATOR.DATA[i][0] = 0;
			SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[i] = 0;
			SLOT[SLOT_INDEX].MEDIATOR.PUSH[i] = 0;
		}
	//#---------------------------------------------------
	//#
	//#---------------------------------------------------
		SLOT[SLOT_INDEX].RUN_STATUS = 0;
		SLOT[SLOT_INDEX].THE_LAST_DATA[0] = 0;
}
//##############################################################
unsigned long  SYS_API__GET__DEVICE_ID_By_SLOT_INDEX(long unsigned SLOT_INDEX){//$
	return SLOT[SLOT_INDEX].DEVICE.ID;
}
long SYS_API__GET__SLOT_INDEX_By_DEVICE_INDEX(unsigned long DEVICE_INDEX){//$
	if (DEVICE_INDEX != SLOT_Len){
		return DEVSYS__SLOT_Pointer[DEVICE_INDEX];
	}return -1;
}
long SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(unsigned long DEVICE_ID){//$
	struct DevInfo local = _DEVSYS__Get_Device_Info(DEVICE_ID);
	if (local.Device_Value == local.Device_Name){
		return DEVSYS__SLOT_Pointer[local.Device_Position];
	}return -1;
}
unsigned long SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(unsigned long Device_index){//$
	return DEVSYS__Devices_Buffer[Device_index];
}
long SYS_API__GET__DEVICE_INDEX_By_DEVICE_ID(unsigned long DEVICE_ID){
	struct DevInfo local = _DEVSYS__Get_Device_Info(DEVICE_ID);
	if (local.Device_Value == local.Device_Name){
		return local.Device_Position;
	}return -1;
}
void SYS_API__DELATE__DEVICE_By_DEVICE_ID(unsigned long DEVICE_ID){
	struct DevInfo local = _DEVSYS__Get_Device_Info(DEVICE_ID);
	if (local.Device_Value == local.Device_Name){
		SLOTSYS__FREE_SLOT(local.Device_Position);
		DEVSYS__Delate_device(local.Device_Position);
	}
}
void SYS_API__ADD__DEVICE_By_DEVICE_ID(unsigned long DEVICE_ID)
{
	long Device_Index;
	long SLOT_Index;
	struct DevInfo local = _DEVSYS__Get_Device_Info(DEVICE_ID);
	//printf("*** Device_Name:%ld\n\r",local.Device_Name);
	//printf("*** Device_Value:%ld\n\r",local.Device_Value);
	//printf("*** Device_Position:%ld\n\r",local.Device_Position);
	if (local.Device_Value == local.Device_Name){
		SLOTSYS__FREE_SLOT(local.Device_Position);
		DEVSYS__SLOT_Pointer[local.Device_Position]=-1;
		SLOT_Index = SLOTSYS__GET_SLOT();
		DEVSYS__SLOT_Pointer[local.Device_Position]=SLOT_Index;
	}else{
		Device_Index = _DEVSYS__Add_device(&local);
		//printf("*** Device_Index %ld \n\r",Device_Index);
		SLOT_Index = SLOTSYS__GET_SLOT();
		//printf("*** SLOT_Index %ld \n\r",SLOT_Index);
		DEVSYS__SLOT_Pointer[Device_Index]=SLOT_Index;
	}
	SLOT[SLOT_Index].DEVICE.ID = DEVICE_ID;
}

void _SYS_API__PrinOUT_Device_Buffer(long Count)
{
	printf("DEVSYS__Devices_Numer_in_Devices_Buffer:%ld\n\r",DEVSYS__Devices_Numer_in_Devices_Buffer);
	printf("SLOTSYS_USED_Slots_number:%ld\n\r",SLOTSYS_USED_Slots_number);

	for (long i=0; i<=Count-1; i++)
    {
    	printf("%ld - Dev:%ld SloP:%ld \n\r",i
    			,DEVSYS__Devices_Buffer[i]
				,DEVSYS__SLOT_Pointer[i]);
    }
}

long SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(){
	return SLOTSYS_USED_Slots_number;
}









//######################################################################
//#
//######################################################################
void SYS_API__PUT__MESSEGE_t(long Devise_SLOT_Number, char *Messege)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	MSGSYS__PUT_Messege( Devise_SLOT_Number, Messege);
	pthread_mutex_unlock(&MSGSYS_mutex);
}
char SYS_API__GET__MESSEGE_t( long Devise_SLOT_Number, char *Buffer)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	MSGSYS__GET_Messege( Devise_SLOT_Number, Buffer);
	pthread_mutex_unlock(&MSGSYS_mutex);
	return 0;
}
//######################################################################
//#
//######################################################################
void SYS_API__PUT__LAST_OUTPUT_DATA_COUNTER_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned long COUNTER){//$
	SLOT[SLOT_INDEX].OUTPUT[INPUT_INDEX].LAST_DATA_COUNTER = COUNTER;
}
unsigned long SYS_API__GET__LAST_OUTPUT_DATA_COUNTER_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX){//$
	return SLOT[SLOT_INDEX].OUTPUT[INPUT_INDEX].LAST_DATA_COUNTER ;
}
//##############################################################




char SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *Messege)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	unsigned long Mess_Len = strlen(Messege);
	//if(Mess_Len >= Messege_Len) Mess_Len = Messege_Len - 1;

	unsigned long i = 0;
	for( i = 0; i < Mess_Len; i++ ){
		SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA[i] = *(Messege+i);
	}
	SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA[Mess_Len] = 0;
	SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA_TIME = SYS_TIME_SEC;
	SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA_COUNTER ++;
	///////////////////////////////
	pthread_mutex_unlock(&MSGSYS_mutex);
	return 0;
}
char SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX( unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *Buffer)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	unsigned long Mess_Len = strlen(SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA);
	unsigned char i = 0;
	for( i = 0; i < Mess_Len; i++ ){
		*(Buffer+i) = SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA[i];
	}*(Buffer+i) = 0;
	pthread_mutex_unlock(&MSGSYS_mutex);
	return 0;
}
unsigned long SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX( unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX)//$
{
	return SLOT[SLOT_INDEX].OUTPUT[OUTPUT_INDEX].LAST_DATA_TIME;
}






//######################################################################
//#
//######################################################################
// amat shecvales
//SYS_API__PUT__MESSEGE(SLOT_INDEX,MyMessege);
//SYS_API__GET__MESSEGE(SLOT_INDEX,WebSocket_Server_message);

char SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *Messege)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	sprintf(SLOT[SLOT_INDEX].THE_LAST_DATA,"%s",Messege);
	pthread_mutex_unlock(&MSGSYS_mutex);
	return 0;
}
char SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX( unsigned long SLOT_INDEX, char *Buffer)
{
	pthread_mutex_lock(&MSGSYS_mutex);
	sprintf(Buffer,"%s",SLOT[SLOT_INDEX].THE_LAST_DATA);
	pthread_mutex_unlock(&MSGSYS_mutex);
	return 0;
}








