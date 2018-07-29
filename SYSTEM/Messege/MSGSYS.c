#include<stdio.h>
#include<string.h>
#include<stdlib.h>
///////////////////////////////////////////////////////
#include"MSGSYS.h"
#include"../SYSTEM.h"
///////////////////////////////////////////////////////
#define MSGSYS_Buffer_len  	10000
char MSGSYS_Buffer[MSGSYS_Buffer_len];
///////////////////////////////////////////////////////
long MSGSYS_Pointer=0;
///////////////////////////////////////////////////////



void MSGSYS__init()
{
	MSGSYS_Pointer = 0;
    for (long i=0; i<=SLOT_Len-1; i++)SLOT[i].MSG_Number = 0;
    for (long i=0; i<=SLOT_Len-1; i++)SLOT[i].MSG_Pointer = -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//
//
//  return 1; if Last_Messege_Pointer = -1;
//  return 2; if Last_Messege_Number is not does not match
//
//////////////////////////////////////////////////////////////////////////////////////////////
char MSGSYS__GET_Messege(long SLOT_Index, char *Buffer)
{
    union DATA{
       long xlong;
       char xchar[4];
    } DATA;
    ///////////////////////////////////////////
    long Last_Messege_Number = SLOT[SLOT_Index].MSG_Number;
    long Last_Messege_Pointer = SLOT[SLOT_Index].MSG_Pointer;
    /////////////////////////////////////////////////
    if (Last_Messege_Pointer==-1)return 1;
    /////////////////////////////////////////////////
    char *xxx = MSGSYS_Buffer;
    xxx+=Last_Messege_Pointer;
    /////////////////////////////////////////////////
    DATA.xchar[0]=*(xxx++);
    DATA.xchar[1]=*(xxx++);
    DATA.xchar[2]=*(xxx++);
    DATA.xchar[3]=*(xxx++);
    if (Last_Messege_Number!=DATA.xlong)return 2;
    /////////////////////////////////////////////////
    xxx+=4;
    char Temp;
    do{
        Temp=*(xxx++); *(Buffer++)=Temp;
    }while(Temp);

    return 0;
}

void MSGSYS__PUT_Messege(long SLOT_Index, char *Messege)
{
    union DATA{
       long xlong;
       char xchar[4];
    } DATA;
    ///////////////////////////////////////////
    long i=0;
    long Last_Messege_Number = SLOT[SLOT_Index].MSG_Number;
    Last_Messege_Number+=1;
    SLOT[SLOT_Index].MSG_Number = Last_Messege_Number;
    long Last_Messege_Pointer = SLOT[SLOT_Index].MSG_Pointer;
    /////////////////////////////////////////////////////
    long Messege_len = strlen(Messege);
    if ((MSGSYS_Pointer+Messege_len+8)>=MSGSYS_Buffer_len){
    	MSGSYS_Pointer=0;
    	Last_Messege_Pointer=0;
    }
    SLOT[SLOT_Index].MSG_Pointer = MSGSYS_Pointer;
    /////////////////////////////////////////////////////
    DATA.xlong=Last_Messege_Number;
    for(i=0; i<=3; i++){
         *(MSGSYS_Buffer+MSGSYS_Pointer)=DATA.xchar[i];
         MSGSYS_Pointer++;
    }
    /////////////////////////////////////////////////////
    DATA.xlong=Last_Messege_Pointer;
    for(i=0; i<=3; i++){
         *(MSGSYS_Buffer+MSGSYS_Pointer)=DATA.xchar[i];
         MSGSYS_Pointer++;
    }
    /////////////////////////////////////////////////////
    for(i=0; i<=Messege_len; i++){
        *(MSGSYS_Buffer+MSGSYS_Pointer)=*(Messege+i);
        MSGSYS_Pointer++;
    }
}




