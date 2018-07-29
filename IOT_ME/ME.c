//#------------------------------------------------
	#define _GNU_SOURCE
	#include <stdlib.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <Python.h>
	#include <sys/time.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	//#include "../IOT__structure.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../core.h"
	#include "../TOOLS/json/JSON.h"
	#include "../TOOLS/base64_2/base64_2.h"
	//#include "../IOT_DEBUG/SYS_INFO/SYS_INFO.h"
	//#include "../IOT_DEBUG/SYS_INFO/Linked_List.h"
	#include "ME.h"
//#------------------------------------------------
	pthread_attr_t ATTR_STACK_SIZE;
//#------------------------------------------------
	int Python_parser_1 (char *input, char *output);
	int Python_parser_2 (char *input, char *output);
	void *ME_pthread__DEVICE_handler(void *arg);
	void *ME_pthread__GET_OUTPUT_DATA(void *arg);
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  long	DEVICE_NAME;
	  long	DEVICE_INDEX;
	  char	BUSY;
	} _MED_AEG;
//#------------------------------------------------
	typedef struct {
	  pthread_t self;
	  long  IN_DEV__NAME;
	  long  IN_DEV__SLOT_INDEX;
	  long  IN_DEV__INPUT;
	  long	OUT_DEV__OUTPUT;
	  long	OUT_DEV__NAME;
	  char	BUSY;
	} _ME_ARG;
//#------------------------------------------------
	#define JSON_parse(x)	if ((JSON_Len = JSON_Parser(SENSOR_message,x,JSON_Value))!=-1){\
								JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
							   }else JSON_STATUS = -3;

	#define JSON_s_parse(x)	if ((JSON_Len = JSON_Parser(SENSOR_message,x,JSON_Value))!=-1){\
								JSON_STATUS = 1;\
							   }else JSON_STATUS = -3;

	#define JSON_PythonCODE(x)	if ((JSON_Len = JSON_Parser(Python_CODE,x,JSON_Value))!=-1){\
							    JSON_Long_Value = atol(JSON_Value);JSON_STATUS = 1;\
						        }else JSON_STATUS = -3;

	#define JSON_s_PythonCODE(x)	if ((JSON_Len = JSON_Parser(Python_CODE,x,JSON_Value))!=-1){\
									JSON_STATUS = 1;\
						   	   	   }else JSON_STATUS = -3;
//#------------------------------------------------




void *ME_pthread__Prossesor( void *arg )
{
    //#------------------------------------------------------------------
		//Print_Line();
		if(DEB_ME==1)printf("... MEDITOR START PROSSESOR\r");
    //#------------------------------------------------------------------
		pthread_t self;
		self = pthread_self();
		//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self, 0,4,0,0);//debugger!!!
    //#------------------------------------------------------------------
		long i=0;
		long SLOT_INDEX;
		long DEVICE_NAME;
		_MED_AEG    MED_AEG;
    //#------------------------------------------------------------------
		pthread_attr_init(&ATTR_STACK_SIZE);
		pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
    //#------------------------------------------------------------------
		while(1){
			for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
				//#------------------------------------------------------------------
					DEVICE_NAME = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(i);
					SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);
				//#------------------------------------------------------------------
					if(SLOT_INDEX != -1){
						if(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX) == TYPE_ME){
							if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX) == IS_NOT_RUN){
								//#--------------------------------------------------------------------------
									SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX,IS_RUN);
								//#--------------------------------------------------------------------------
									MED_AEG.DEVICE_NAME  = DEVICE_NAME;
									MED_AEG.DEVICE_INDEX = SLOT_INDEX;
									MED_AEG.self = self;
									MED_AEG.BUSY = 1;
								//#--------------------------------------------------------------------------
									SLOT[SLOT_INDEX].MEDIATOR.DATA[0][0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA[1][0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA[2][0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA[3][0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[1] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[2] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.DATA_STATUS[3] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.PUSH[0] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.PUSH[1] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.PUSH[2] = 0;
									SLOT[SLOT_INDEX].MEDIATOR.PUSH[3] = 0;
								//#--------------------------------------------------------------------------
									pthread_mutex_init(&SLOT[SLOT_INDEX].MEDIATOR.mutex, NULL);
									pthread_cond_init(&SLOT[SLOT_INDEX].MEDIATOR.cond, NULL);
								//#--------------------------------------------------------------------------
									pthread_t _ME_pthread__DEVICE_handler;
									if( pthread_create( &_ME_pthread__DEVICE_handler , &ATTR_STACK_SIZE , ME_pthread__DEVICE_handler , (void*) &MED_AEG) < 0){
									}
								//#--------------------------------------------------------------------------
									while(MED_AEG.BUSY) usleep(1000);
								//#--------------------------------------------------------------------------
							}
						}
					}
			}
			SYS_BUSY = 0;
			usleep(5000000);
		}
	//###########################################################################
	//# EXIT
	//###########################################################################
    while(1) usleep(500000);
	if(DEB_ME==1)printf("... MEDITOR EXIT!!!\n\r");
	//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
    fflush(stdout);
    pthread_detach(self);
    return 0;
}





void *ME_pthread__DEVICE_handler(void *arg)
{
	//##----------------------------------------------------------
		_MED_AEG* ARG = (_MED_AEG*)arg;
	//##----------------------------------------------------------
		long DEVICE_NAME = ARG->DEVICE_NAME;
		long SLOT_INDEX  = ARG->DEVICE_INDEX;
	//##----------------------------------------------------------
		//pthread_t parent_self;
		//parent_self = ARG->self;
		pthread_t self = pthread_self();
	//##----------------------------------------------------------
		ARG->BUSY = 0;
	//##----------------------------------------------------------
		//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,44,DEVICE_NAME,0);//debugger!!!
	//##----------------------------------------------------------
		char JSON_Value[50];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
		long AUTO_PERIOD = 0;
		char PYTON_PROCESSOR_START = 0;
	//##----------------------------------------------------------
		if(DEB_ME==1)printf("... MEDITOR START DEVICE:%ld INDEX:%ld\n\r",DEVICE_NAME,SLOT_INDEX);
	//##----------------------------------------------------------
		char Python_CODE[DEVICE_DATA_LEN];
		char *CODE_IN = SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX(SLOT_INDEX);
		long CODE_LEN = 0;
	//##----------------------------------------------------------
		struct timeval tv;
		struct timespec ts;
	//##----------------------------------------------------------
		_ME_ARG      ME_ARG;
	//##----------------------------------------------------------
		long My_EVENT_COUNTER__CREATE_INTERCONN__Me = 9999;
	//##----------------------------------------------------------
		char MyMessege[100];
		char JISON_NAME[40];
	//##----------------------------------------------------------
		int i = 0;
		long ii = 0;
		long OUT_Len = 0;
		char OUT_NAME[10];

		char IN_0[256];
		char IN_1[256];
		char IN_2[256];
		char IN_3[256];

		char IN_0_NEW[4];
		char IN_1_NEW[4];
		char IN_2_NEW[4];
		char IN_3_NEW[4];


		char OUT[256];
		char MEM_0[256];MEM_0[0]=0;
	//##----------------------------------------------------------
		char is_error = 0;
		char Error_value[1024];
		char b64_Error_value[1024];
	//#----------------------------------------------------------
	//#	PyObjects !!!
	//#----------------------------------------------------------
		PyEval_AcquireLock();
		PyThreadState* pThreadState = Py_NewInterpreter();
		assert( pThreadState != NULL );
	//#----------------------------------------------------------
		PyObject *pVal;
	//#------------------------------------------------------------------------
		PyObject *py_main = PyImport_AddModule("__main__");
		PyObject *Global_Dir = PyModule_GetDict(py_main);
		PyObject *Local_Dir = PyDict_New();
		PyDict_SetItemString(Local_Dir, "__builtins__", PyEval_GetBuiltins());
	//#------------------------------------------------------------------------
		PyEval_ReleaseThread( pThreadState ) ;
	//#------------------------------------------------------------------------
		SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX,DATA_NEW);
	//#------------------------------------------------------------------------
		while(1){
			//###########################################################################
			//# GET EXIT CONDITIO
			//###########################################################################
				if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX) == IS_NOT_RUN)break;
				//if(SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME) == -1)break;
			//###########################################################################
			//# IF NEW python CODE
			//###########################################################################
				if(SYS_API__GET__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX) == DATA_NEW){
					CODE_LEN = strlen(CODE_IN);
					if(CODE_LEN > 0){
						//printf("... MEDITOR Python_CODE :%ld INDEX:%ld CODE_LEN:%ld\n\r",DEVICE_NAME,SLOT_INDEX,CODE_LEN);//!!!!!
						_b64_decode(CODE_IN, Python_CODE);
						SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX,DATA_OLD);
					//#------------------------------------------------
						AUTO_PERIOD = 0;
						JSON_PythonCODE("_PER_");
						if (JSON_STATUS == 1){
							if(JSON_Long_Value != 0){
								if(DEB_ME==1)printf("... MEDITOR DEV(%ld) AUTO_PERIOD = %ld\n\r",DEVICE_NAME,JSON_Long_Value);
								//printf("... MEDITOR DEV(%ld) _PER_ = %ld\n\r",DEVICE_NAME,JSON_Long_Value);
								AUTO_PERIOD = JSON_Long_Value;
							}
						}
					//#------------------------------------------------
						JSON_s_PythonCODE("_DES_");
						if (JSON_STATUS == 1){
							if(strlen(JSON_Value) > 0){
									//printf("... MEDITOR DEV(%ld) _DES_ = %s\n\r",DEVICE_NAME,JSON_Value);
								//#------------------------------------------------
									sprintf(MyMessege, "{\"C\":\"4\",\"D\":\"%ld\",\"V\":\"%s\"}",DEVICE_NAME,JSON_Value );
									if(DEB_ME==1)printf("... MEDITOR DEV(%ld) Description = %s\n\r",DEVICE_NAME,MyMessege);
									//printf("... MEDITOR DEV(%ld)(%ld) = %s\n\r",DEVICE_NAME,SLOT_INDEX,MyMessege);
								//#------------------------------------------------
									SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX, JSON_Value);
								//#------------------------------------------------
									//SYS_API__PUT__MESSEGE(SLOT_INDEX,MyMessege);
									SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,MyMessege);
									pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
									pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
									pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
								//#------------------------------------------------
									usleep(400);
							}
						}
					//#------------------------------------------------
						for (i = 0; i < OUTPUT_LEN; i++){
							if(SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX,i)==1){
								sprintf(JISON_NAME,"_OUT_%d_DES_",i);
								JSON_s_PythonCODE(JISON_NAME);
								if (JSON_STATUS == 1){
									SYS_API__PUT__OUTPUT_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX,i, JSON_Value);
									sprintf(MyMessege, "{\"C\":\"7\",\"D\":\"%ld\",\"IN\":\"%d\",\"V\":\"%s\"}",DEVICE_NAME,i,JSON_Value);
								} else {
									sprintf(MyMessege, "{\"C\":\"7\",\"D\":\"%ld\",\"IN\":\"%d\",\"V\":\"undefined\"}",DEVICE_NAME,i);
								}
								//SYS_API__PUT__MESSEGE(SLOT_INDEX,MyMessege);
								SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,MyMessege);
								pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
								pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
								pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
								usleep(400);
							}
						}
					//#------------------------------------------------
						for (i = 0; i < OUTPUT_LEN; i++){
							sprintf(JISON_NAME,"_IN_%d_PUSH_",i);
							JSON_s_PythonCODE(JISON_NAME);
							if (JSON_STATUS == 1){
								if(strlen(JSON_Value) > 0){
									if(JSON_Value[0]=='1'){
										SLOT[SLOT_INDEX].MEDIATOR.PUSH[i]=1;
									}else{
										SLOT[SLOT_INDEX].MEDIATOR.PUSH[i]=0;
									}
								}
							}
						}
					//#------------------------------------------------

					}
				}
			//###########################################################################
			//#
			//###########################################################################
				gettimeofday(&tv, NULL);
				ts.tv_sec = tv.tv_sec;
				ts.tv_nsec = tv.tv_usec*1000;
				if(AUTO_PERIOD == 0) ts.tv_sec += 3; else ts.tv_sec += AUTO_PERIOD;
			//#------------------------------------------------
				pthread_mutex_lock(&SLOT[SLOT_INDEX].MEDIATOR.mutex);
				int cond = pthread_cond_timedwait(&SLOT[SLOT_INDEX].MEDIATOR.cond, &SLOT[SLOT_INDEX].MEDIATOR.mutex, &ts);
				pthread_mutex_unlock(&SLOT[SLOT_INDEX].MEDIATOR.mutex);
			//###########################################################################
			//# PYTON PROCESSOR !!!
			//###########################################################################
				if(cond == 0){
					PYTON_PROCESSOR_START = 1;
				} else {
					if(AUTO_PERIOD != 0) PYTON_PROCESSOR_START = 1;
				}
			//#------------------------------------------------
				if(PYTON_PROCESSOR_START==1){
					PYTON_PROCESSOR_START = 0;
					#include "ME_PYTON_PROCESSOR.c"
				}
			//###########################################################################
			//# INTERCONNECTION DYNAMIC CONTROL !!!
			//###########################################################################
			if(EVENT_COUNTER__CREATE_INTERCONN__Me != My_EVENT_COUNTER__CREATE_INTERCONN__Me){
				My_EVENT_COUNTER__CREATE_INTERCONN__Me = EVENT_COUNTER__CREATE_INTERCONN__Me;
				if(DEB_ME==1)printf("... MEDITOR DEV(%ld) scanning CREATE_INTERCONN connections\n\r",DEVICE_NAME);
				for (ii = 0; ii < 4; ii++){//mxolod pirveli 4 shesasvleli mowmdeba
					if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)ii) == ENABLE){
						if(SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)ii) == IS_NOT_LISTEN){
							if(SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)ii) != 0){
								SYS_API__PUT__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)ii, IS_LISTEN);
								long OUT_DEV__NAME   = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) ii);
								long OUT_DEV__OUTPUT = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) ii);
								//#-----------------------------------------------------------
									ME_ARG.IN_DEV__NAME	  	  = DEVICE_NAME;
									ME_ARG.IN_DEV__SLOT_INDEX = SLOT_INDEX;
									ME_ARG.IN_DEV__INPUT      = ii;
									ME_ARG.OUT_DEV__NAME      = OUT_DEV__NAME;
									ME_ARG.OUT_DEV__OUTPUT    = OUT_DEV__OUTPUT;
									ME_ARG.self = self;
									ME_ARG.BUSY = 1;
								//#-----------------------------------------------------------
									pthread_t _ME_pthread__GET_OUTPUT_DATA;
									if( pthread_create( &_ME_pthread__GET_OUTPUT_DATA , &ATTR_STACK_SIZE , ME_pthread__GET_OUTPUT_DATA , (void*) &ME_ARG) < 0){
									}
								//#--------------------------------------------------------------------------
									while(ME_ARG.BUSY) usleep(1000);
								//#--------------------------------------------------------------------------
							}
						}
					}
				}
			}
		}
	//###########################################################################
	//# EXIT !!!
	//###########################################################################
		PyEval_AcquireThread( pThreadState );
		Py_EndInterpreter( pThreadState );
		PyEval_ReleaseLock();
    //#-----------------------------------------------------------
		if(DEB_ME==1)printf("... MEDITOR STOP DEVICE:%ld INDEX:%ld\n\r",DEVICE_NAME,SLOT_INDEX);
	//#-----------------------------------------------------------
		//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
		fflush(stdout);
		pthread_detach(self);
		return 0;
}











void *ME_pthread__GET_OUTPUT_DATA(void *arg)
{
	//##----------------------------------------------------------
		_ME_ARG* ARG = (_ME_ARG*)arg;
	//##----------------------------------------------------------
		long IN_DEV__NAME		  = ARG->IN_DEV__NAME;
		long IN_DEV__SLOT_INDEX   = ARG->IN_DEV__SLOT_INDEX;
		long IN_DEV__INPUT	  	  = ARG->IN_DEV__INPUT;
		long OUT_DEV__NAME     	  = ARG->OUT_DEV__NAME;
		long OUT_DEV__OUTPUT   	  = ARG->OUT_DEV__OUTPUT;
	//##----------------------------------------------------------
		//pthread_t parent_self;
		//parent_self = ARG->self;
		pthread_t self = pthread_self();
	//##----------------------------------------------------------
		//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,444,OUT_DEV__NAME,OUT_DEV__OUTPUT);//debugger!!!
	//##----------------------------------------------------------
		struct timeval tv;
		struct timespec ts;
	//##----------------------------------------------------------
		long SLOT_INDEX;
		char SENSOR_message[200];
		unsigned long isCOUNTER = 0;
		//char JSON_Value[50];long JSON_Len; long JSON_STATUS;long JSON_Long_Value;
	//##----------------------------------------------------------
		ARG->BUSY = 0;
	//##----------------------------------------------------------
		if(DEB_ME==1)printf("... MEDITOR START_LISTENING DEV(%ld)OUT(%ld) --> DEV(%ld)INP(%ld)\n\r"
				,OUT_DEV__NAME
				,OUT_DEV__OUTPUT
				,IN_DEV__NAME
				,IN_DEV__INPUT);
	//##----------------------------------------------------------
		SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUT_DEV__NAME);
		if(SLOT_INDEX != -1){
			while(1){
				//###########################################################################
					if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(IN_DEV__SLOT_INDEX) == IS_NOT_RUN)break;
					if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT) == DISABLE)break;
					if(SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT) == IS_NOT_LISTEN)break;
					if(SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT) == 0)break;
				//###########################################################################
					gettimeofday(&tv, NULL);
					ts.tv_sec = tv.tv_sec;
					ts.tv_nsec = tv.tv_usec*1000;
					ts.tv_sec += 3;

					pthread_mutex_lock(&SLOT[SLOT_INDEX].Device_cond_mutex);
					int cond = pthread_cond_timedwait(&SLOT[SLOT_INDEX].Device_condition, &SLOT[SLOT_INDEX].Device_cond_mutex, &ts);
					pthread_mutex_unlock(&SLOT[SLOT_INDEX].Device_cond_mutex);
				//###########################################################################
					if(cond == 0){

						#include "ME_IN_DATA_PROCESSOR.c"

					} else {

						//printf(" TimeOUT !!!! \n");

					}
			}
	}
	//###########################################################################
	//# EXIT !!!
	//###########################################################################
	if(DEB_ME==1)printf("... MEDITOR STOP_LISTENING DEV(%ld)OUT(%ld) --> DEV(%ld)INP(%ld)\n\r"
			,OUT_DEV__NAME
			,OUT_DEV__OUTPUT
			,IN_DEV__NAME
			,IN_DEV__INPUT);
	////////////////////////////////////////////////////////////////
	SYS_API__PUT__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT, IS_NOT_LISTEN);
	////////////////////////////////////////////////////////////////
	//if(ME_virtual_debugger==1)SYS_INFO_WebSocket_Remove((int)self);//debugger!!!
	fflush(stdout);
	pthread_detach(self);
	return 0;
}


//###############################################################################
//#
//###############################################################################
int Python_parser_1 (char *input, char *output){
	long len = strlen(input);
	long y = 0;
	char x;
	for (long i = 0; i < len; i++){
		x = *input++;
		switch(x){
		   case ' ' : break;
		   case '(' : break;
		   case '<' : break;
		   case '>' : break;
		   case '\'': break;
		   default :
			   if(x == ',')y++;
			   if(y == 4) {
				   *output++ = 0;
				   return 0;
			   } else {
				   *output++ = x;
				   if(x == ',')*output++ = ' ';
			   } break;
		}
	}
	return -1;
}
//###############################################################################
//#
//###############################################################################
int Python_parser_2 (char *input, char *output){
	long len = strlen(input);
	for (long i = 0; i < len; i++){
		*output++ = *input++;
	}
	*output++ = 0;
	return 0;
}


