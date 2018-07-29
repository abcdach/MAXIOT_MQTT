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
	#include "../core.h"
	#include "../SYSTEM/File/FILE_SYS.h"
	#include "FILE_DEBUG.h"
	#include "../IOT__config.h"
//#------------------------------------------------


int FILE_DEBUG_init(void){
	//#----------------------------------------------------------
		Print_Line();
		printf("*** Check the FILE_DEBUG structure\n\r");
		Print_Line();
	//#----------------------------------------------------------
		printf("FILE_DEBUG : Check Folder /tmp/MAXIOT : ");
		if (SYS_API__GET__Folder_Status_By_Folder_Path("/tmp/MAXIOT/")!=0){
			printf("ERROR\n\r");
			printf("FILE_DEBUG : Create Folder /tmp/MAXIOT : ");
			if (SYS_API__PUT__Folder_By_Folder_Path("/tmp/MAXIOT")!=0){
				printf("ERROR\n\r");
				printf("FILE_DEBUG : FATAL ERROR !!!\n\r");
				return -1;
			}else printf("OK\n\r");
		}else printf("OK\n\r");
	//#----------------------------------------------------------
		printf("FILE_DEBUG : Check File /tmp/MAXIOT/MySQL_STATUS : ");
		if (SYS_API__GET__File_Status_By_File_Path("/tmp/MAXIOT/MySQL_STATUS")!=0){
			printf("ERROR\n\r");
		}else printf("OK\n\r");
	//#----------------------------------------------------------
		printf("FILE_DEBUG : Create File /tmp/MAXIOT/MySQL_STATUS : ");
		if (SYS_API__PUT__DATA_TO_FILE_By_FILE_Path("/tmp/MAXIOT/MySQL_STATUS","")!=0){
			printf("ERROR\n\r");
		}else printf("OK\n\r");
	//#----------------------------------------------------------



	//##########################################################
	//##########################################################

		//#----------------------------------------------------------
			printf("FILE_DEBUG : Check Folder %s : ",OBJECTS_Path);
			if (SYS_API__GET__Folder_Status_By_Folder_Path(OBJECTS_Path)!=0){
				printf("ERROR\n\r");
				printf("FILE_DEBUG : Create Folder %s : ",OBJECTS_Path);
				if (SYS_API__PUT__Folder_By_Folder_Path(OBJECTS_Path)!=0){
					printf("ERROR\n\r");
					printf("FILE_DEBUG : FATAL ERROR !!!\n\r");
					return -1;
				}else printf("OK\n\r");
			}else printf("OK\n\r");
		//#----------------------------------------------------------


			SYS_API__GET__Folder_Content_By_Folder_Path("/etc/MAXIOT/");




	//##########################################################
	//##########################################################



	//#----------------------------------------------------------
		Print_Line();
		return 0;
}
//SAVE_DATA_TO_MySQL_STATUS_FILE(STATUS_BUF_MySQL);

char STATUS_BUF_MySQL[1024];
int SAVE_DATA_TO_MySQL_STATUS_FILE(char *DATA){
	printf("%s",DATA);
	if (SYS_API__Append__DATA_TO_FILE_By_FILE_Path("/tmp/MAXIOT/MySQL_STATUS",DATA)!=0){
		return -1;
	}return 0;
}











