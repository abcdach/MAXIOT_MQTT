#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include "FILE_SYS.h"

#define FSYS_Name_Num	256
long FSYS_Counter = 0;
char FSYS_Name[FSYS_Name_Num][64];
long JSON_Parser(char *JSON_String, char *JSON_Name , char *JSON_Value);

int SYS_API__PUT__DATA_TO_FILE_By_FILE_Path(char * FILE_Path, char *DATA);
int SYS_API__GET__DATA_FROM_FILE_By_FILE_Path(char * FILE_Path, char *DATA);
int  SYS_API__GET__Folder_Status_By_Folder_Path(char * Folder_Path);
int  SYS_API__PUT__Folder_By_Folder_Path(char * Folder_Path);
long SYS_API__GET__Folder_Content_By_Folder_Path(char * Folder_Path);
///////////////////////////////////////////////////
int  SYS_API__PUT__FILE_SYSTEM(void);
///////////////////////////////////////////////////
int  SYS_API__PUT__IOT_DEVICE(long DEVICE, char *Description, long Type, long X, long Y, long Room, char *Data);
///////////////////////////////////////////////////

typedef struct {
	char 	DESCRIPTION[128];
	long	X;
	long	Y;
	long	TYPE;
	long	ROOM;
	char	DATA[2048];
} IOT_FILE_DEVICE;

IOT_FILE_DEVICE FILE_DEVICE;

//int  FSYS_API__PUT__IOT_DEVICE_FILE(long DEVICE,char * DESCRIPTION, long X, long Y, long TYPE, long ROOM,char * DATA){
int  SYS_API__PUT__IOT_DEVICE_FILE(long DEVICE_ID, IOT_FILE_DEVICE *DEVICE){
	char Temp_S[50];
	FILE *f;
	sprintf(Temp_S,"IOT_DB/DEVICE/%ld",DEVICE_ID);
	f = fopen(Temp_S, "w");

	fprintf(f,"{");
	fprintf(f,"\n\t\"DESCRIPTION\":\"%s\",",DEVICE->DESCRIPTION);
	fprintf(f,"\n\t\"X\":\"%ld\",",DEVICE->X);
	fprintf(f,"\n\t\"Y\":\"%ld\",",DEVICE->Y);
	fprintf(f,"\n\t\"TYPE\":\"%ld\",",DEVICE->TYPE);
	fprintf(f,"\n\t\"ROOM\":\"%ld\",",DEVICE->ROOM);
	fprintf(f,"\n\t\"DATA\":\"%s\"",DEVICE->DATA);
	fprintf(f,"\n}");

	fclose(f);
	return 1;
}




//##################################################################################3


#include <errno.h>


int main ()
{
	//#----------------------------------------------------------------------------------
		long Temp = 0;
		char Temp_S[256];
	//###########################################################################################
		char JSON_Value[128];
	//###########################################################################################
		printf("MySQL_STATU : Check the Folder MAXIOT : ");
		Temp = SYS_API__GET__Folder_Status_By_Folder_Path("MAXIOT");
		if (Temp == -1){
			printf("ERROR\n\r");
			printf("MySQL_ERROR : Folder MAXIOT is not found\n\r");
			printf("MySQL_STATU : Create Folder MAXIOT : ");
			Temp = SYS_API__PUT__Folder_By_Folder_Path("MAXIOT");
			if (Temp == -1){
				printf("ERROR\n\r");
				return -1;
			}else{
				printf("OK\n\r");
				printf("MySQL_STATU : Create File MySQL_Config : ");
				sprintf(Temp_S,
				"{"
				"\n\t\"SERVER\":\"localhost\""
				"\n\t\"USER\":\"pma\""
				"\n\t\"PASSWORD\":\"dachdach\""
				"\n\t\"DATABASE\":\"iot\""
				"\n}");
				Temp = SYS_API__PUT__DATA_TO_FILE_By_FILE_Path("MAXIOT/MySQL_Config",Temp_S);
				if (Temp == -1){
					printf("ERROR\n\r");
					return -1;
				}else printf("OK\n\r");
			}
		}else printf("OK\n\r");
	//###########################################################################################
		printf("MySQL_STATU : Read File MySQL_Config : ");
		Temp = SYS_API__GET__DATA_FROM_FILE_By_FILE_Path("MAXIOT/MySQL_Config",Temp_S);
		if (Temp == -1){
			printf("ERROR\n\r");
			return -1;
		}else printf("OK\n\r");
		printf("MySQL_STATU : FILe :\n\r%s\n\r",Temp_S);
	//#----------------------------------------------------------------------------------
		printf("MySQL_STATU : SERVER : ");
		if((Temp=JSON_Parser(Temp_S,"SERVER",JSON_Value))!=-1){
			if (Temp>0){
				printf("OK : %s \n\r",JSON_Value);
			}else{
				printf("ERROR\n\r");return -1;
			}
		}else{
			printf("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		printf("MySQL_STATU : USER : ");
		if((Temp=JSON_Parser(Temp_S,"USER",JSON_Value))!=-1){
			if (Temp>0){
				printf("OK : %s \n\r",JSON_Value);
			}else{
				printf("ERROR\n\r");return -1;
			}
		}else{
			printf("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		printf("MySQL_STATU : PASSWORD : ");
		if((Temp=JSON_Parser(Temp_S,"PASSWORD",JSON_Value))!=-1){
			if (Temp>0){
				printf("OK : %s \n\r",JSON_Value);
			}else{
				printf("ERROR\n\r");return -1;
			}
		}else{
			printf("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		printf("MySQL_STATU : DATABASE : ");
		if((Temp=JSON_Parser(Temp_S,"DATABASE",JSON_Value))!=-1){
			if (Temp>0){
				printf("OK : %s \n\r",JSON_Value);
			}else{
				printf("ERROR\n\r");return -1;
			}
		}else{
			printf("ERROR\n\r");return -1;
		}
	//###########################################################################################

	return 0;



////////////////////////////////////////////////////////////////////////////////////////////////


	printf("... FILE_SYS : START\n\r");

	printf("... FILE_SYS : Check the Folder IOT_DB : ");
	Temp = SYS_API__GET__Folder_Status_By_Folder_Path("IOT_DB");
	if (Temp == 0){
		printf("ERROR\n\r");
		printf("... FILE_SYS : Create folder IOT_DB : ");
		Temp = SYS_API__PUT__Folder_By_Folder_Path("IOT_DB");
		if (Temp == 0){
			printf("ERROR\n\r");
		}else{
			printf("OK\n\r");
		}
	}else{
		printf("OK\n\r");
	}

	printf("... FILE_SYS : Check the Folder IOT_DB/DEVICE : ");
	Temp = SYS_API__GET__Folder_Status_By_Folder_Path("IOT_DB/DEVICE");
	if (Temp == 0){
		printf("ERROR\n\r");
		printf("... FILE_SYS : Create folder : IOT_DB/DEVICE : ");
		Temp = SYS_API__PUT__Folder_By_Folder_Path("IOT_DB/DEVICE");
		if (Temp == 0){
			printf("ERROR\n\r");
		}else{
			printf("OK\n\r");
		}
	}else{
		printf("OK\n\r");
	}

	//IOT_FILE_DEVICE
	int i = 1;
	if(i==0){
		sprintf(FILE_DEVICE.DESCRIPTION,"%s","undefined");
		FILE_DEVICE.X = 50;
		FILE_DEVICE.Y = 100;
		FILE_DEVICE.TYPE = 0;
		FILE_DEVICE.ROOM = 0;
		sprintf(FILE_DEVICE.DATA,"%s","1");

		//SYS_API__PUT__IOT_DEVICE_FILE(200, &FILE_DEVICE);
	} else {

		//SYS_API__GET__IOT_DEVICE_FILE(200, &FILE_DEVICE);
	}

	return 0;
}












//#################################################################################
//##
//#################################################################################
int  SYS_API__PUT__IOT_DEVICE(long DEVICE, char *Description, long Type, long X, long Y, long Room, char *Data){
		long Temp = 0;
		char Temp_S[100];
			FILE *f;
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld",DEVICE);
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				//printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/Description",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%s", Description);
		fclose(f);
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/Type",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%ld", Type);
		fclose(f);
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/X",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%ld", X);
		fclose(f);
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/Y",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%ld", Y);
		fclose(f);
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/Room",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%ld", Room);
		fclose(f);
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE/%ld/Data",DEVICE);
		f = fopen(Temp_S, "w");
		fprintf(f, "%s", Data);
		fclose(f);
	//#--------------------------------------------------------



		return 1;
}
//#################################################################################
//##
//#################################################################################
int  SYS_API__PUT__FILE_SYSTEM(){

		long Temp = 0;
		char Temp_S[100];
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB");
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/DEVICE");
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/OUTPUT");
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/INPUT");
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
		sprintf(Temp_S,"IOT_DB/INTERCONN");
		if (SYS_API__GET__Folder_Status_By_Folder_Path(Temp_S) == 0 ){
			Temp = SYS_API__PUT__Folder_By_Folder_Path(Temp_S);
			if (Temp == 0){
				printf("... FILE_SYS Critical Error !!!!\n\r");
				return 0;
			}
		}
	//#--------------------------------------------------------
	return 1;
}








//#################################################################################
//##
//#################################################################################
long SYS_API__GET__Folder_Content_By_Folder_Path(char * Folder_Path){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (Folder_Path)) != NULL) {
	   long i;
	   FSYS_Counter = 0;
	   for( i = 0; i < FSYS_Name_Num; i++ ){
		  if(((ent = readdir (dir)) == NULL)) break;
		  sprintf(FSYS_Name[i],"%s",ent->d_name);
		  if(FSYS_Name[i][0]=='.')continue;
		  printf ("... FILE_SYS %ld : %s\n",i, FSYS_Name[i]);
		  FSYS_Counter ++;
	   }closedir (dir);
	}return FSYS_Counter;
}
//#################################################################################
//##
//#################################################################################
int SYS_API__PUT__Folder_By_Folder_Path(char * Folder_Path){
	mkdir(Folder_Path, 0700);
	struct stat st = {0};
	if (stat(Folder_Path, &st) == -1) {
		return -1;
	}return 0;
}
//#################################################################################
//##
//#################################################################################
int SYS_API__GET__Folder_Status_By_Folder_Path(char * Folder_Path){
	struct stat st = {0};
	if (stat(Folder_Path, &st) == -1) {
		return -1;
	}return 0;
}
//#################################################################################
//##
//#################################################################################
int SYS_API__PUT__DATA_TO_FILE_By_FILE_Path(char * FILE_Path, char *DATA){
	   FILE * f;
	   f = fopen (FILE_Path, "w");
	   if (f == NULL){
	      return -1;
	   } else {
		  fprintf(f, "%s", DATA);
	      fclose (f);
	   }return 0;
}
//#################################################################################
//##
//#################################################################################
int SYS_API__GET__DATA_FROM_FILE_By_FILE_Path(char * FILE_Path, char *DATA){
	FILE *f;
	f = fopen(FILE_Path, "rb");
	if (f == NULL){
	  return -1;
	} else {
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);  //same as rewind(f);
		fread(DATA, fsize, 1, f);
		fclose(f);
		DATA[fsize] = 0;
	}return 0;
}








long JSON_Parser(char *JSON_String, char *JSON_Name , char *JSON_Value){
	long JSON_String_len = 0;
	long JSON_Name_len = 0;
	long i,ii,iii,Temp;
	for (i = 0; i < 3000; i++){if(JSON_String[i]==0){JSON_String_len = i;break;}}
	for (i = 0; i < 3000; i++){if(JSON_Name[i]==0){JSON_Name_len = i;break;}}
	Temp = JSON_Name_len + 4;
	if(JSON_String_len>Temp){
		Temp = JSON_String_len - Temp;
		i=0;
		while (1){
			if(JSON_String[i]=='"'){
				ii = i + JSON_Name_len + 1;
				if(JSON_String[ii]=='"'){
					ii++;
					if(JSON_String[ii]==':'){
						ii = i+1;
						for (iii = 0; iii < JSON_Name_len; iii++){
							if(JSON_String[ii]!=JSON_Name[iii]) break;
							ii ++;
						}
						if(iii==JSON_Name_len){
							i = i+JSON_Name_len+3;
							if(JSON_String[ii]=='"'){
								ii = 0;
								while (1){
									i++;
									if(JSON_String[i]=='"'){
										JSON_Value[ii]=0;
										return ii;
									}
									JSON_Value[ii]=JSON_String[i];
									ii ++;
									if(i>=JSON_String_len) return -1;
								}return 0;
							}else return -1;
						}i++;
					}else i++;
				}else i++;
			}else i++;
			if(i>=Temp)break;
		}return -1;
	}else return -1;
}
