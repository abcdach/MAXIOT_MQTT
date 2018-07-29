
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <malloc.h>
//#------------------------------------------------
	#include <stdio.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <dirent.h>
	#include<ctype.h>
//#------------------------------------------------
	#include "../IOT__definition.h"
	#include "../SYSTEM/File/FILE_SYS.h"
	#include "../SYSTEM/SYSTEM.h"
	#include "../TOOLS/json/JSON.h"
	#include "FOBJECTS.h"
//#------------------------------------------------

long FOBJECTS__GET_LAST_FILE_NAME();
int FOBJECTS_init(){
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
		//SYS_API__GET__Folder_Content_By_Folder_Path(OBJECTS_Path);
	//#----------------------------------------------------------
		long F_Name = FOBJECTS__GET_LAST_FILE_NAME();
		if(F_Name==0){
			char File_Path[128];
			sprintf(File_Path,"%s/0",OBJECTS_Path);
			if(SYS_API__GET__File_Status_By_File_Path(File_Path)!=0){
				printf("SYS_API__GET__File_Status_By_File_Path : ERROR !!!\n\r");
				SYS_API__PUT__DATA_TO_FILE_By_FILE_Path(File_Path,"");
			}
		}
	//#----------------------------------------------------------
		return 0;
}




int FOBJECTS__Load_Objects(void){
		char DBG = 1;
		if(DBG==1)printf ("\n\r\n\r\n\r\n\r");
		long F_Name = FOBJECTS__GET_LAST_FILE_NAME();
		if(DBG==1)printf ("FOBJ : The Last file name is : %ld\n\r\n\r",F_Name);
	//#------------------------------------------------------------------
		long DEVICE_TYPE;
		long DEVICE_ID;
		char DEVICE_DESCRIPTION[DEVICE_DESCRIPTION_LEN];
		long DEVICE_X;
		long DEVICE_Y;
		long DEVICE_ROOM;
		char DEVICE_DATA[DEVICE_DATA_LEN];
	//#------------------------------------------------------------------
		long INPUT_DEVICE_ID;
		long INPUT_ID;
		char INPUT_DESCRIPTION[INPUT_DESCRIPTION_LEN];
		char INPUT_CONFIG_DATA[CONFIG_DATA_LEN];
	//#------------------------------------------------------------------
		long OUTPUT_DEVICE_ID;
		long OUTPUT_ID;
		char OUTPUT_DESCRIPTION[OUTPUT_DESCRIPTION_LEN];
		char OUTPUT_CONFIG_DATA[CONFIG_DATA_LEN];
	//#------------------------------------------------------------------
		unsigned long RX_DEVICE_ID;
		unsigned long RX_INDEX;
		unsigned long TX_DEVICE_ID;
		unsigned long TX_INDEX;
	//#------------------------------------------------------------------
		long SLOT_INDEX;

	char Path_and_Name[128];
	sprintf(Path_and_Name ,"%s%ld",OBJECTS_Path,F_Name);
	FILE *f;
	f = fopen(Path_and_Name, "rb");
	char buf[4092];

	int Step = 0;
	int SUB_Step = 0;

	while (fgets(buf, sizeof(buf), f) != NULL)
	{
		buf[strlen(buf) - 1] = '\0';
		//printf("%s\n", buf);
		switch(Step) {
			case 0 :
				if(strlen(buf)!=3)break;
				if(buf[0]!='#')break;
				if(buf[2]!='#')break;
				if(DBG==1)printf("%s\n", buf);
				switch(buf[1]) {
					case 'D': Step = 10; SUB_Step = 0; break;
					case 'I': Step = 20; SUB_Step = 0; break;
					case 'O': Step = 30; SUB_Step = 0;  break;
					case 'C': Step = 40; SUB_Step = 0;  break;
					default : Step = 0; break;
				}break;
				case 10 ://#D#
					switch(SUB_Step){
						case 0 : DEVICE_TYPE = atol(buf);if(DBG==1)printf("DEVICE_TYPE : %ld\n",DEVICE_TYPE); SUB_Step = 1; break;
						case 1 : DEVICE_ID   = atol(buf);if(DBG==1)printf("DEVICE_ID   : %ld\n",DEVICE_ID);   SUB_Step = 2; break;
						case 2 : DEVICE_X    = atol(buf);if(DBG==1)printf("DEVICE_X    : %ld\n",DEVICE_X);    SUB_Step = 3; break;
						case 3 : DEVICE_Y    = atol(buf);if(DBG==1)printf("DEVICE_Y    : %ld\n",DEVICE_Y);    SUB_Step = 4; break;
						case 4 : DEVICE_ROOM = atol(buf);if(DBG==1)printf("DEVICE_ROOM : %ld\n",DEVICE_ROOM); SUB_Step = 5; break;
						case 5 : sprintf(DEVICE_DESCRIPTION,"%s",buf);if(DBG==1)printf("DEVICE_DESCRIPTION : %s\n",DEVICE_DESCRIPTION); SUB_Step = 6;break;
						case 6 : sprintf(DEVICE_DATA,"%s",buf);if(DBG==1)printf("DEVICE_DATA : %s\n",DEVICE_DATA); Step = 0;
						//#------------------------------------------------------------------
							SYS_API__ADD__DEVICE_By_DEVICE_ID(DEVICE_ID);
							SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_ID);
							if(SLOT_INDEX != -1){
								SYS_API__CLEANING__DEVICE_By_SLOT_INDEX(SLOT_INDEX);
								SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX(SLOT_INDEX);
								SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX(SLOT_INDEX, 1);
								SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX,DEVICE_TYPE);
								SYS_API__PUT__DEVICE_X_By_SLOT_INDEX(SLOT_INDEX, DEVICE_X);
								SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX(SLOT_INDEX, DEVICE_Y);
								SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX, DEVICE_DESCRIPTION);
								SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX(SLOT_INDEX, DEVICE_DATA);
								SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX,DATA_NEW);
								SYS_API__PUT__DEVICE_ROOM_By_SLOT_INDEX(SLOT_INDEX, (char)DEVICE_ROOM);
							}
						break;
						default : Step = 0; break;
					}break;
				case 20 ://#I#
					switch(SUB_Step){
						case 0 : INPUT_DEVICE_ID = atol(buf);if(DBG==1)printf("INPUT_DEVICE_ID : %ld\n",INPUT_DEVICE_ID); SUB_Step = 1; break;
						case 1 : INPUT_ID        = atol(buf);if(DBG==1)printf("INPUT_ID   : %ld\n",INPUT_ID);   SUB_Step = 2; break;
						case 2 : sprintf(INPUT_DESCRIPTION,"%s",buf);if(DBG==1)printf("INPUT_DESCRIPTION : %s\n",INPUT_DESCRIPTION); SUB_Step = 3;break;
						case 3 : sprintf(INPUT_CONFIG_DATA,"%s",buf);if(DBG==1)printf("INPUT_CONFIG_DATA : %s\n",INPUT_CONFIG_DATA); Step = 0;
						//#------------------------------------------------------------------
							SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(INPUT_DEVICE_ID);
							if(SLOT_INDEX != -1){
								SYS_API__PUT__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)INPUT_ID, ENABLE );
								SYS_API__PUT__INPUT_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)INPUT_ID,INPUT_DESCRIPTION);
								SYS_API__PUT__INPUT_CONFIG_DATA_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)INPUT_ID,INPUT_CONFIG_DATA);
							}
						break;
						default : Step = 0; break;
					}break;
				case 30 ://#O#
					switch(SUB_Step){
						case 0 : OUTPUT_DEVICE_ID = atol(buf);if(DBG==1)printf("OUTPUT_DEVICE_ID : %ld\n",OUTPUT_DEVICE_ID); SUB_Step = 1; break;
						case 1 : OUTPUT_ID        = atol(buf);if(DBG==1)printf("OUTPUT_ID   : %ld\n",OUTPUT_ID);   SUB_Step = 2; break;
						case 2 : sprintf(OUTPUT_DESCRIPTION,"%s",buf);if(DBG==1)printf("OUTPUT_DESCRIPTION : %s\n",OUTPUT_DESCRIPTION); SUB_Step = 3;break;
						case 3 : sprintf(OUTPUT_CONFIG_DATA,"%s",buf);if(DBG==1)printf("OUTPUT_CONFIG_DATA : %s\n",OUTPUT_CONFIG_DATA); Step = 0;
						//#------------------------------------------------------------------
							SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUTPUT_DEVICE_ID);
							if(SLOT_INDEX != -1){
								SYS_API__PUT__OUTPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)OUTPUT_ID, ENABLE );
								SYS_API__PUT__OUTPUT_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)OUTPUT_ID,OUTPUT_DESCRIPTION);
								SYS_API__PUT__OUTPUT_CONFIG_DATA_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)OUTPUT_ID,OUTPUT_CONFIG_DATA);
							}
						break;
						default : Step = 0; break;
					}break;
				case 40 ://#C#
					switch(SUB_Step){
						case 0 : TX_DEVICE_ID = atol(buf);if(DBG==1)printf("TX_DEVICE_ID : %ld\n",TX_DEVICE_ID); SUB_Step = 1; break;
						case 1 : TX_INDEX = atol(buf);if(DBG==1)printf("TX_INDEX   : %ld\n",TX_INDEX);   SUB_Step = 2; break;
						case 2 : RX_DEVICE_ID = atol(buf);if(DBG==1)printf("RX_DEVICE_ID : %ld\n",RX_DEVICE_ID); SUB_Step = 3; break;
						case 3 : RX_INDEX  = atol(buf);if(DBG==1)printf("RX_INDEX   : %ld\n",RX_INDEX);  Step = 0;
						//#------------------------------------------------------------------
						SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(RX_DEVICE_ID);
						if(SLOT_INDEX != -1){
							SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) RX_INDEX, TX_DEVICE_ID);
							SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) RX_INDEX, TX_INDEX);
						}break;
						default : Step = 0; break;
					}break;
			default :
				break;
		}
	}
	fclose(f);
	return 0;
}




long FOBJECTS__GET_LAST_FILE_NAME(){
	#define FSYS_Name_Num	256
	char FSYS_Name[128];
	long F_NUM=0;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (OBJECTS_Path)) != NULL){
	   long i;
	   long F_TMP=0;
	   for( i = 0; i < 500; i++ ){
			if(((ent = readdir (dir)) == NULL)) break;
			sprintf(FSYS_Name,"%s",ent->d_name);
			if(FSYS_Name[0]=='.')continue;
			long r;long b = 0;
			for(  r = 0; r < strlen(FSYS_Name); r++ ){
			  if(!isdigit(FSYS_Name[r])){b = 1; break;}
			}if (b == 1)continue;
			F_TMP = atol(FSYS_Name);
			if ( F_TMP > F_NUM ) F_NUM = F_TMP ;
	   }
	}closedir (dir); return F_NUM;
}




int FOBJECTS__Save_Objects(void){
	char DBG = 0;
	if(DBG==1)printf ("\n\r\n\r\n\r\n\r");
	long F_Name = FOBJECTS__GET_LAST_FILE_NAME();
	if(DBG==1)printf ("FOBJ : The Last file name is : %ld\n\r\n\r",F_Name);
	F_Name ++ ;
	if(DBG==1)printf ("FOBJ : The New file name is  : %ld\n\r\n\r",F_Name);

	char Path_and_Name[128];
	sprintf(Path_and_Name ,"%s%ld",OBJECTS_Path,F_Name);
	if(DBG==1)printf ("FOBJ : Path : %s\n\r",Path_and_Name);

	FILE * f;
	f = fopen (Path_and_Name, "w");
	if (f == NULL)return -1;

	long DEVICE_ID;;
	long SLOT_INDEX;
	long i=0;long ii=0;
	//#####################################################################
	//# DEVICE
	//#####################################################################
	if(DBG==1)printf ("\n\rFOBJ : DEVICES *********\n\r");
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){

				fprintf(f, "%s\n", "#D#");
				fprintf(f, "%ld\n", (unsigned long)SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				fprintf(f, "%ld\n", (unsigned long)DEVICE_ID);
				fprintf(f, "%ld\n", (unsigned long)SYS_API__GET__DEVICE_X_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				fprintf(f, "%ld\n", (unsigned long)SYS_API__GET__DEVICE_Y_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				fprintf(f, "%ld\n", (unsigned long)SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				fprintf(f, "%s\n", SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				fprintf(f, "%s\n", SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				//#------------------------------------------------------------------
				if(DBG==1)printf("#D#\n%ld\n%ld\n%ld\n%ld\n%ld\n%s\n%s\n\n"
						 , (unsigned long)SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)DEVICE_ID
						 , (unsigned long)SYS_API__GET__DEVICE_X_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_Y_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
				 	 	 , SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX((unsigned long )SLOT_INDEX));

			}
	}
	//#####################################################################
	//# INPUT
	//#####################################################################
	if(DBG==1)printf ("\n\rFOBJ : INPUT *********\n\r");
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < INPUT_LEN; ii++){
					 if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long )SLOT_INDEX, (unsigned char)ii)==ENABLE){

						 fprintf(f, "%s\n", "#I#");
						 fprintf(f, "%ld\n",(unsigned long )DEVICE_ID);
						 fprintf(f, "%ld\n",(unsigned long )ii);
						 fprintf(f, "%s\n",SYS_API__GET__INPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
						 fprintf(f, "%s\n",SYS_API__GET__INPUT_CONFIG_DATA_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
						 //#------------------------------------------------------------------
						 if(DBG==1)printf("#I#\n%ld\n%ld\n%s\n%s\n"
								,(unsigned long )DEVICE_ID
								,(unsigned long )ii
								,SYS_API__GET__INPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii)
						 	 	,SYS_API__GET__INPUT_CONFIG_DATA_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
					 }
				 }
			}
	}
	//#####################################################################
	//# OUTPUT
	//#####################################################################
	if(DBG==1)printf ("\n\rFOBJ : OUTPUT *********\n\r");
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < OUTPUT_LEN; ii++){
					if(SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii)==ENABLE){

						 fprintf(f, "%s\n", "#O#");
						 fprintf(f, "%ld\n",(unsigned long )DEVICE_ID);
						 fprintf(f, "%ld\n",(unsigned long )ii);
						 fprintf(f, "%s\n",SYS_API__GET__OUTPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
						 fprintf(f, "%s\n",SYS_API__GET__OUTPUT_CONFIG_DATA_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
						 //#------------------------------------------------------------------
						 if(DBG==1)printf("#O#\n%ld\n%ld\n%s\n%s\n"
								 ,(unsigned long)DEVICE_ID
								 ,(unsigned long)ii
								 ,SYS_API__GET__OUTPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii)
								 ,SYS_API__GET__OUTPUT_CONFIG_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii));

					} else break;
				 }
			}
	}
	//#####################################################################
	//# INTERCONN
	//#####################################################################
	if(DBG==1)printf ("\n\rFOBJ : INTERCONN *********\n\r");
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);//$
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);//$
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < INPUT_LEN; ii++){
					 if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long )SLOT_INDEX, (unsigned char)ii)==ENABLE){//$
							unsigned long LISTEN_DEVICE_ID = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii);
							unsigned char LISTEN_DEVICE_OUTPUT_INDEX = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii);
							if(LISTEN_DEVICE_ID != 0){

								fprintf(f, "%s\n", "#C#");
								fprintf(f, "%ld\n",(unsigned long )LISTEN_DEVICE_ID);
								fprintf(f, "%ld\n",(unsigned long )LISTEN_DEVICE_OUTPUT_INDEX);
								fprintf(f, "%ld\n",(unsigned long )DEVICE_ID);
								fprintf(f, "%ld\n",(unsigned long )ii);
								//#------------------------------------------------------------------
								if(DBG==1)printf("#C#\n%ld\n%ld\n%ld\n%ld\n"
									 ,(unsigned long)LISTEN_DEVICE_ID
									 ,(unsigned long)LISTEN_DEVICE_OUTPUT_INDEX
									 ,(unsigned long)DEVICE_ID
									 ,(unsigned long)ii );
							}
					 } else break;
				 }
			}
	}
	//#####################################################################
	//# END
	//#####################################################################
	fclose (f);
	return 0;
}


