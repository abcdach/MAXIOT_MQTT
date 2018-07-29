#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

////////////////////////////////////////////////////////////
#include"../SYSTEM.h"
#include"DEVSYS.h"
////////////////////////////////////////////////////////////
long DEVSYS__Devices_Buffer[SLOT_Len];
long DEVSYS__SLOT_Pointer[SLOT_Len];
long DEVSYS__Devices_Numer_in_Devices_Buffer = 0;
///////////////////////////////////////////////////////

void DEVSYS__init()
{
	DEVSYS__Devices_Numer_in_Devices_Buffer = 0;
    for (long i=0; i<=SLOT_Len-1; i++){
    	DEVSYS__Devices_Buffer[i] = 0;
    	DEVSYS__SLOT_Pointer[i] = -1;
    }
}

long DEVSYS__list_check(void)
{
    long a=0;
    long i=0;
	for (i=0; i<=SLOT_Len - 1; i++){
        if (DEVSYS__Devices_Buffer[i] != 0){
            if (a < DEVSYS__Devices_Buffer[i]){
                a = DEVSYS__Devices_Buffer[i];
            }else{
                return -1;
            }
        }else{
        	 return i;
        }
	}
    return i;
}


void DEVSYS__Delate_device(long Device_Num)
{
    long i=0;
	for (i=Device_Num; i<=DEVSYS__Devices_Numer_in_Devices_Buffer - 2; i++){
		DEVSYS__Devices_Buffer[i] = DEVSYS__Devices_Buffer[i + 1];
		DEVSYS__SLOT_Pointer[i] = DEVSYS__SLOT_Pointer[i + 1];
	}
    DEVSYS__Devices_Buffer[DEVSYS__Devices_Numer_in_Devices_Buffer - 1] = 0;
    DEVSYS__SLOT_Pointer[DEVSYS__Devices_Numer_in_Devices_Buffer - 1] = -1;
    DEVSYS__Devices_Numer_in_Devices_Buffer -= 1	;
}
//###############################################################################
//
//
//
//	if return > -1 ::: Value is Devise nuber in devise list buffer
//	if return = -1 ::: Devise is not found
//
//###############################################################################

long DEVSYS__Finde_device(long Device_Name)
{
	struct DevInfo local = _DEVSYS__Get_Device_Info(Device_Name);
    if (local.Device_Value == Device_Name ){
    	return local.Device_Position;
    }else{
    	return -1;// Device is not found
    }
}
struct DevInfo _DEVSYS__Get_Device_Info(long Device_Name)
{
	struct DevInfo Local;
	Local.Device_Name=Device_Name;
	Local.Device_Value=0;//#############
	Local.Device_Position=0;//#############

	long k=0;long x1=0;long x2=0;
	long b = DEVSYS__Devices_Numer_in_Devices_Buffer - 1;
	long c = DEVSYS__Devices_Numer_in_Devices_Buffer - 1;

	////////////////////////////////////////////////////////////////
    if (DEVSYS__Devices_Numer_in_Devices_Buffer == 0){
    	Local.Device_Value=DEVSYS__Devices_Buffer[0];
    	Local.Device_Position=0;
        return Local;
    }
	////////////////////////////////////////////////////////////////
    if (DEVSYS__Devices_Buffer[0] >= Device_Name){
    	Local.Device_Value=DEVSYS__Devices_Buffer[0];//#############
    	Local.Device_Position=0;//#############
        return Local;
    }
	////////////////////////////////////////////////////////////////
    if (DEVSYS__Devices_Buffer[DEVSYS__Devices_Numer_in_Devices_Buffer - 1] <= Device_Name){
    	Local.Device_Value=DEVSYS__Devices_Buffer[DEVSYS__Devices_Numer_in_Devices_Buffer - 1];//#############
    	Local.Device_Position=DEVSYS__Devices_Numer_in_Devices_Buffer - 1;//#############
        return Local;
	}
	////////////////////////////////////////////////////////////////
    for (long i=0; i<=100000; i++)
    {
        if (b == 0){
            for (k=0; k<=c - 1; k++){
                x1 = DEVSYS__Devices_Buffer[c - k];
                x2 = DEVSYS__Devices_Buffer[c - k - 1];
                if (x2 == Device_Name){
                	Local.Device_Value=DEVSYS__Devices_Buffer[c - k - 1];
                	Local.Device_Position=c - k - 1;
                    return Local;
				}
                if (x1 > Device_Name){
                    if (Device_Name >= x2){
                    	Local.Device_Value=DEVSYS__Devices_Buffer[c - k - 1];
                    	Local.Device_Position=c - k - 1;
                        return Local;
                    }
				}
            }
            return Local;
        }
        ///////////////////////////////////////////////////////////////////
        if (DEVSYS__Devices_Buffer[b] == Device_Name){
        	Local.Device_Value=DEVSYS__Devices_Buffer[b];
        	Local.Device_Position=b;
			return Local;
        }
        ///////////////////////////////////////////////////////////////////
        else if (DEVSYS__Devices_Buffer[c] == Device_Name){
        	Local.Device_Value=DEVSYS__Devices_Buffer[c];
        	Local.Device_Position=c;
			return Local;
        }
        ///////////////////////////////////////////////////////////////////
        else if (DEVSYS__Devices_Buffer[c] > Device_Name){
            b = b / 2; c = c - b;
            if (c <= -2) c = -1;
            if (c == -1){
				 for (k=0; k<=DEVSYS__Devices_Numer_in_Devices_Buffer - 1; k++){
                    x1 = DEVSYS__Devices_Buffer[k];
                    x2 = DEVSYS__Devices_Buffer[k + 1];
                    if (x2 == Device_Name){
                    	Local.Device_Value=DEVSYS__Devices_Buffer[k + 1];
                    	Local.Device_Position=k + 1;
                        return Local;
                    }
                    if (x1 <= Device_Name){
                        if (Device_Name <= x2){
                        	Local.Device_Value=DEVSYS__Devices_Buffer[k];
                        	Local.Device_Position=k;
							return Local;
                        }
                    }
				 }
				 return Local;
             }
        }
        ///////////////////////////////////////////////////////////////////
        else if (DEVSYS__Devices_Buffer[c] < Device_Name){
            b = b / 2;
            if (b == 0)b = 1;
            c = c + b;
        }
        ///////////////////////////////////////////////////////////////////
        if (c > (DEVSYS__Devices_Numer_in_Devices_Buffer - 1)){
            for (k=0; k<=c - 1; k++){
                x1 = DEVSYS__Devices_Buffer[c - k - 1];
                x2 = DEVSYS__Devices_Buffer[c - k - 2];
                if (x2 == Device_Name){
                	Local.Device_Value=DEVSYS__Devices_Buffer[c - k - 2];
                	Local.Device_Position=c - k - 2;
					return Local;
                }
                if (x1 >= Device_Name){
                    if (Device_Name >= x2){
                    	Local.Device_Value=DEVSYS__Devices_Buffer[c - k - 1];
                    	Local.Device_Position= c - k - 1;
						return Local;
                    }
                }
            }
			return Local;
        }
    }
    return Local;
}

//###############################################################################
//
//
//	if return > -1 ::: Value is Devise nuber in devise list buffer
//	if return = -1 ::: DEVSYS__Devices_Buffer is full
//
//###############################################################################
long DEVSYS__Add_device(long Device_Name)
{
	struct DevInfo local = _DEVSYS__Get_Device_Info(Device_Name);
	if (local.Device_Value == local.Device_Name){
		return local.Device_Position;
		//return -1;
	}else{
    	if (DEVSYS__Devices_Numer_in_Devices_Buffer != SLOT_Len){
    		//_DEVSYS__Add_device(&local);
    		return _DEVSYS__Add_device(&local);
		}else{
    		return -1;
    	}
	}
}
long _DEVSYS__Add_device(struct DevInfo *_DevInfo)
{
	long a = 0;long b = 0;
    ///////////////////////////////////////////////////////////////////
    if (DEVSYS__Devices_Numer_in_Devices_Buffer == 0){
        DEVSYS__Devices_Buffer[0] = _DevInfo->Device_Name;
        DEVSYS__SLOT_Pointer[0]   =  -1;
        DEVSYS__Devices_Numer_in_Devices_Buffer += 1;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////
    if (_DevInfo->Device_Value < _DevInfo->Device_Name){
        a = DEVSYS__Devices_Numer_in_Devices_Buffer;
        b = a - 1;
        for (long i=1; i<=DEVSYS__Devices_Numer_in_Devices_Buffer - (_DevInfo->Device_Position + 1); i++){
            DEVSYS__Devices_Buffer[a] = DEVSYS__Devices_Buffer[b];
            DEVSYS__SLOT_Pointer[a]   = DEVSYS__SLOT_Pointer[b];
            b = b - 1;
            a = a - 1;
		}
        DEVSYS__Devices_Buffer[_DevInfo->Device_Position + 1] = _DevInfo->Device_Name;
        DEVSYS__SLOT_Pointer[_DevInfo->Device_Position + 1]   = -1;
        DEVSYS__Devices_Numer_in_Devices_Buffer += 1;
        return _DevInfo->Device_Position+1;//!!!!!!!!!!!!!!!!!!!
	}
    ///////////////////////////////////////////////////////////////////
    if (_DevInfo->Device_Value > _DevInfo->Device_Name){
        a = DEVSYS__Devices_Numer_in_Devices_Buffer;
        b = a - 1;
		for (long i=1; i<=DEVSYS__Devices_Numer_in_Devices_Buffer - _DevInfo->Device_Position; i++){
            DEVSYS__Devices_Buffer[a] = DEVSYS__Devices_Buffer[b];
            DEVSYS__SLOT_Pointer[a]   = DEVSYS__SLOT_Pointer[b];
            b = b - 1;
            a = a - 1;
		}
        DEVSYS__Devices_Buffer[_DevInfo->Device_Position] = _DevInfo->Device_Name;
        DEVSYS__SLOT_Pointer[_DevInfo->Device_Position]   = -1;
        DEVSYS__Devices_Numer_in_Devices_Buffer += 1;
        if(_DevInfo->Device_Position==0){
        	return 0;
        }else{
        	return _DevInfo->Device_Position-1;
        }
	}
    return -1;
}











