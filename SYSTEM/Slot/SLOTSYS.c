
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
///////////////////////////////////////////////////////
#include"../SYSTEM.h"
#include"SLOTSYS.h"

long SLOTSYS_USED_Slots_number = 0;


void SLOTSYS__init()
{
    for (int i=0; i<SLOT_Len; i++){
    	SLOT[i].X=i-1;
    	SLOT[i].Y=i+1;
    }
    SLOT[0].X=SLOT_Len+1;
    SLOT[SLOT_Len-1].Y=SLOT_Len+2;
    SLOT[SLOT_Len].X=0;
    SLOT[SLOT_Len].Y=0;
    SLOT[SLOT_Len+1].X=0;
    SLOT[SLOT_Len+1].Y=0;
    SLOT[SLOT_Len+2].X=SLOT_Len-1;
    SLOT[SLOT_Len+2].Y=0;
}

long SLOTSYS__GET_SLOT()
{
	long Temp1=0;long Temp2=0;
	if(SLOT[SLOT_Len+1].X != SLOT[SLOT_Len+2].X){
	   Temp1 = SLOT[SLOT_Len+1].X;
	   Temp2 = SLOT[Temp1].Y;
	   SLOT[Temp2].X=SLOT_Len+1;
	   SLOT[Temp1].X=SLOT_Len;
	   SLOT[Temp1].Y=SLOT_Len;
	   SLOT[SLOT_Len+1].X=Temp2;
	   SLOTSYS_USED_Slots_number+=1;
	   return Temp1;
	}else{
		return -1;
	}
}

long SLOTSYS__FREE_SLOT(long SLOT_NUM)
{
	long Temp=0;
	if(SLOT[SLOT_NUM].X == SLOT[SLOT_NUM].Y){
		Temp=SLOT[SLOT_Len+2].X;
		SLOT[Temp].Y=SLOT_NUM;
		SLOT[SLOT_NUM].X=Temp;
		SLOT[SLOT_NUM].Y=SLOT_Len+2;
		SLOT[SLOT_Len+2].X=SLOT_NUM;
		SLOTSYS_USED_Slots_number-=1;
		return SLOT_NUM;
	}else{
		return -1;
	}
}



