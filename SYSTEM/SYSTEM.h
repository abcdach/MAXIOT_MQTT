///////////////////////////////////////////////////////
void SYS_API__init();
///////////////////////////////////////////////////////
void SYS_API__ADD__DEVICE_By_DEVICE_ID(unsigned long DEVICE_ID);
void SYS_API__DELATE__DEVICE_By_DEVICE_ID(unsigned long DEVICE_ID);
///////////////////////////////////////////////////////
long SYS_API__GET__DEVICE_INDEX_By_DEVICE_ID(unsigned long DEVICE_ID);
unsigned long SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(unsigned long Device_index);//$
long SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(unsigned long DEVICE_ID);//$
long SYS_API__GET__SLOT_INDEX_By_DEVICE_INDEX(unsigned long DEVICE_INDEX);
///////////////////////////////////////////////////////
void SYS_API__PUT__MESSEGE_t(long Devise_SLOT_Number, char *Messege);// uqmdeba SYS_API__PUT__LAST_DATA_By_SLOT_INDEX
char SYS_API__GET__MESSEGE_t(long Devise_SLOT_Number, char *Buffer);// uqmdeba SYS_API__GET__LAST_DATA_By_SLOT_INDEX
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned long DEVICE_USER_INDEX);//$
unsigned long SYS_API__GET__DEVICE_USER_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char DEVICE_TYPE);//$
unsigned char SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void  SYS_API__PUT__DEVICE_X_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned short DEVICE_X);//$
void  SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned short DEVICE_Y);//$
unsigned short SYS_API__GET__DEVICE_X_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
unsigned short SYS_API__GET__DEVICE_Y_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *DESCRIPTION);//$
char *SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *DATA);
char *SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX);
void SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char STATUS);
unsigned char SYS_API__GET__DEVICE_DATA_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX);
////////////////////////////////////////////////////////
void SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
void SYS_API__PTHREAD_WAIT__By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__CLEANING__DEVICE_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__INPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char INPUT_STATUS);//$
unsigned char SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char INPUT_STATUS);
unsigned char SYS_API__GET__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);
////////////////////////////////////////////////////////
void SYS_API__PUT__OUTPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, unsigned char OUTPUT_STATUS);
unsigned char SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX);
////////////////////////////////////////////////////////
void SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned long LISTEN_DEVICE_NAME);//$
void SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char LISTEN_DEVICE_OUTPUT_INDEX);//$
unsigned long SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);//$
unsigned char SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char STATUS);
unsigned char SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX);
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned char STATUS);
unsigned char SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);
////////////////////////////////////////////////////////
long SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER();
unsigned long SYS_API__GET__DEVICE_ID_By_SLOT_INDEX(unsigned long SLOT_INDEX);//!!!!!
////////////////////////////////////////////////////////
void SYS_API__PUT__DEVICE_ROOM_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char ROOM);//$
unsigned char SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX(unsigned long SLOT_INDEX);//$
////////////////////////////////////////////////////////
void SYS_API__PUT__LAST_OUTPUT_DATA_COUNTER_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, unsigned long COUNTER);
unsigned long SYS_API__GET__LAST_OUTPUT_DATA_COUNTER_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);
////////////////////////////////////////////////////////
char SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *Messege);//$
char SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *Buffer);//$
unsigned long SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX);//$
////////////////////////////////////////////////////////
void  SYS_API__PUT__INPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, char *DESCRIPTION);//$
char *SYS_API__GET__INPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);//$
void  SYS_API__PUT__INPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX, char *CONFIG_DATA);//$
char *SYS_API__GET__INPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char INPUT_INDEX);//$
////////////////////////////////////////////////////////
void  SYS_API__PUT__OUTPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *DESCRIPTION);
char *SYS_API__GET__OUTPUT_DESCRIPTION_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX);
void  SYS_API__PUT__OUTPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX, char *CONFIG_DATA);
char *SYS_API__GET__OUTPUT_CONFIG_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, unsigned char OUTPUT_INDEX);
////////////////////////////////////////////////////////
long SYS_API__GET__Folder_Content_By_Folder_Path(char * Folder_Path);
int  SYS_API__PUT__Folder_By_Folder_Path(char * Folder_Path);
int  SYS_API__GET__Folder_Status_By_Folder_Path(char * Folder_Path);
int  SYS_API__PUT__DATA_TO_FILE_By_FILE_Path(char * FILE_Path, char *DATA);
int  SYS_API__GET__DATA_FROM_FILE_By_FILE_Path(char * FILE_Path, char *DATA);
////////////////////////////////////////////////////////




char SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(unsigned long SLOT_INDEX, char *Messege);
char SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX( unsigned long SLOT_INDEX, char *Buffer);




#include "../IOT__definition.h"
#include "../IOT__config.h"

#include "MAIN_STRUCT.c"

//#------------------------------------------------
	extern _SLOT SLOT[];
	extern long SYS_Signal_Counter__Add_Sensor_Input;
	extern long SYS_TIME_SEC;
//#------------------------------------------------
























