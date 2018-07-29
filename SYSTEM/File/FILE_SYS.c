#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
///////////////////////////////////////////////////////
#include "FILE_SYS.h"
#include"../SYSTEM.h"
///////////////////////////////////////////////////////



#define FSYS_Name_Num	256
long FSYS_Counter = 0;
char FSYS_Name[FSYS_Name_Num][64];

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
//#################################################################################
//##
//#################################################################################
int  SYS_API__GET__File_Status_By_File_Path(char * FILE_Path){
   FILE * f;
   f = fopen (FILE_Path, "r");
   if (f == NULL){
	  fclose (f);return -1;
   }
   fclose (f);return 0;
}
//#################################################################################
//##
//#################################################################################
int SYS_API__Append__DATA_TO_FILE_By_FILE_Path(char * FILE_Path, char *DATA){
	   FILE * f;
	   f = fopen (FILE_Path, "a");
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
long SYS_API__GET__FILE_Len_By_FILE_Path(char * FILE_Path){
	FILE *f;
	f = fopen(FILE_Path, "rb");
	if (f != NULL){
		fseek(f, 0L, SEEK_END);
		long fsize = ftell(f);
		fclose (f);
		return fsize;
	}return 0;
}


























