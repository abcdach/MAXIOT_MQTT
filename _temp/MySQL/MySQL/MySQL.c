//#------------------------------------------------
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <mysql.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <malloc.h>
	#include <Python.h>
//#------------------------------------------------
	#include "../IOT__config.h"
	////#include "../IOT__structure.h"
	#include "../IOT__definition.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../core.h"
	#include "../IOT_STUDIO/IOT_STUDIO.h"
	//#include "../IOT_DEBUG/IOT_DEBUG.h"
	#include "../IOT_WE/WE.h"
	#include "../IOT_DE/DE.h"
	#include "../IOT_ME/ME.h"
	//#include "../IOT_DEBUG/SYS_INFO/SYS_INFO.h"
	#include "../IOT_STATISTICS/EVENT_COUNTER.h"
	#include "../TOOLS/json/JSON.h"
	#include "../TOOLS/base64_2/base64_2.h"
	#include "../IOT_FILE_DEBUG/FILE_DEBUG.h"
	#include "MySQL.h"



	#include "../SYSTEM/File/FILE_SYS.h"
	#include "../IOT_FOBJECTS/FOBJECTS.h"

//#------------------------------------------------
	typedef struct {
		MYSQL *CONN;
		MYSQL_RES *RES;
		MYSQL_ROW ROW;
		char *SERVER;
		char *USER;
		char *PASSWORD;
		char *DATABASE;
		char QUERY[255] ;
		char QUERY_TEXT[255] ;
		long STATUS;
	} _MySQL;
//#------------------------------------------------
	long VALUE_1[10000];
	long VALUE_2[10000];
	long VALUE_3[10000];
	long VALUE_4[10000];
//#------------------------------------------------
	long MySQL_Device_Cou    = 0;
	long MySQL_Input_Cou     = 0;
	long MySQL_Output_Cou    = 0;
	long MySQL_Interconn_Cou = 0;
//#------------------------------------------------
	char MySQL_SERVER[128];
	char MySQL_USER[128];
	char MySQL_PASSWORD[128];
	char MySQL_DATABASE[128];
//#------------------------------------------------
	_MySQL	MySQL;
//#------------------------------------------------
	#include "function/SQL_Connect.c"
	#include "function/SQL_Close.c"
	#include "function/SQL_CREATE_DATABASE.c"
//#------------------------------------------------
	#include "function/SQL_READ_DEVICE.c"//!!!
	#include "function/SQL_READ_INPUT.c"
	#include "function/SQL_READ_OUTPUT.c"
	#include "function/SQL_READ_INTERCONN.c"
//#------------------------------------------------
	#include "function/COM/SQL_CREATE_DEVICE.c"
	#include "function/COM/SQL_CREATE_INPUT.c"
	#include "function/COM/SQL_CREATE_OUTPUT.c"
	#include "function/COM/SQL_CREATE_INTERCONN.c"
//#------------------------------------------------
	#include "function/COM/SQL_DELETE_DEVICE.c"
	#include "function/COM/SQL_DELETE_INPUT.c"
	#include "function/COM/SQL_DELETE_OUTPUT.c"
	#include "function/COM/SQL_DELETE_INTERCONN.c"
//#------------------------------------------------
	#include "function/COM/SQL_GET_IN_OR_OUT_OBJECT_DATA.c"
	#include "function/COM/SQL_PUT_IN_OR_OUT_OBJECT_DATA.c"
	#include "function/COM/SQL_PUT_DEVICE_OBJECT_DATA.c"
	#include "function/COM/SQL_UPDATE_DEVICE_OBJECTS.c"
//#------------------------------------------------
	#include "function/SQL_GET_PARAMETRES.c"
	#include "function/SQL_DB_TO_STRUCTURE.c"
//#------------------------------------------------




int MySQL_START(){
	int value = 0;
	Print_MySQL("---------------------------------\n\r");
	Print_MySQL("*** Obtaining parameters of MySQL DB\n\r");
	Print_MySQL("---------------------------------\n\r");
	if(MySQL_GET_PARAMETRES() != -1){
		Print_MySQL("---------------------------------\n\r");
		Print_MySQL("*** Check the MySQL DB structure\n\r");
		Print_MySQL("---------------------------------\n\r");
		value = MySQL_Connect(); MySQL_Close();
		switch(value){
			case 1049 :
				Print_MySQL("---------------------------------\n\r");
				Print_MySQL("*** creating MySQL DB Structure\n\r");
				Print_MySQL("---------------------------------\n\r");
				MySQL_CREATE_DATABASE();
				break;
			default :
				break;
		}
		Print_MySQL("---------------------------------\n\r");
		Print_MySQL("*** Transfer data from MySQL DB into main Program Structure\n\r");
		Print_MySQL("---------------------------------\n\r");
		MySQL_DB_TO_STRUCTURE();
		Print_MySQL("---------------------------------\n\r");
	}
	return 0;
}


