//#------------------------------------------------
	#define _GNU_SOURCE
	#include <stdlib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <poll.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <mysql.h>
	#include <pthread.h>
//#------------------------------------------------
	#include "../../IOT__config.h"
	//#include "../../IOT__structure.h"
	#include "../../IOT__definition.h"
	#include "../../SYSTEM/SYSTEM.h"
	#include "../../core.h"
//#------------------------------------------------
	//#include "../TOOLS/sha1/sha1.h"
	//#include "../TOOLS/json/JSON.h"
	//#include "../TOOLS/base64/base64.h"
//#------------------------------------------------
	#include "Linked_List.h"
	#include "SYS_INFO.h"
//#------------------------------------------------
	pthread_mutex_t SYS_INFO_mutex;
//#------------------------------------------------
	//char SYS_INFO_changed = 0;
//#------------------------------------------------
	node* WebSocket_head = NULL;
	node* WebSocket_tmp = NULL;
	node* WebSocket_cursor = NULL;

	callback disp = display;
//#------------------------------------------------


int SYS_INFO_INIT()
{
	pthread_mutex_init(&SYS_INFO_mutex, NULL);

	WebSocket_head = prepend(WebSocket_head,0,0,0,0,0);
	//WebSocket_head = append(WebSocket_head,100,200,1,2,3);
	//WebSocket_head = append(WebSocket_head,101,201,1,2,3);
	//WebSocket_head = append(WebSocket_head,102,202,1,2,3);
	//WebSocket_head = append(WebSocket_head,103,203,1,2,3);
	//WebSocket_head = append(WebSocket_head,104,204,1,2,3);
	//WebSocket_head = append(WebSocket_head,105,205,1,2,3);
	//WebSocket_head = append(WebSocket_head,106,206,1,2,3);
	//WebSocket_head = append(WebSocket_head,107,207,1,2,3);
	//WebSocket_head = append(WebSocket_head,108,208,1,2,3);
	//WebSocket_head = append(WebSocket_head,109,209,1,2,3);


	//printf("count: %ld\n",(long)count(WebSocket_head));
	//traverse(WebSocket_head,disp);


	return 0;
}


void SYS_INFO_WebSocket_Reset()
{
	WebSocket_cursor = WebSocket_head;
}
long SYS_INFO_WebSocket_Read_Data()
{
	long data;
	if(WebSocket_cursor != NULL){
		data = WebSocket_cursor->data;
	} else {
		return -1;
	}
	return data;
}
long SYS_INFO_WebSocket_Read_D0()
{
	long data;
	if(WebSocket_cursor != NULL){
		data = WebSocket_cursor->D0;
	} else {
		return -1;
	}
	return data;
}
long SYS_INFO_WebSocket_Read_D1()
{
	long data;
	if(WebSocket_cursor != NULL){
		data = WebSocket_cursor->D1;
	} else {
		return -1;
	}
	return data;
}
long SYS_INFO_WebSocket_Read_D2()
{
	long data;
	if(WebSocket_cursor != NULL){
		data = WebSocket_cursor->D2;
	} else {
		return -1;
	}
	return data;
}
long SYS_INFO_WebSocket_Read_D3()
{
	long data;
	if(WebSocket_cursor != NULL){
		data = WebSocket_cursor->D3;
	} else {
		return -1;
	}
	return data;
}








void SYS_INFO_WebSocket_Read_Next()
{
	if(WebSocket_cursor != NULL){
		WebSocket_cursor = WebSocket_cursor->next;
	}
}



void SYS_INFO_WebSocket_Append(int data,int D0,int D1,int D2,int D3)
{
	pthread_mutex_lock(&SYS_INFO_mutex);
	WebSocket_head = append(WebSocket_head,data,D0,D1,D2,D3);
	pthread_mutex_unlock(&SYS_INFO_mutex);
}

void SYS_INFO_WebSocket_Remove(int data)
{
	pthread_mutex_lock(&SYS_INFO_mutex);
	WebSocket_tmp = search(WebSocket_head,data);
    if(WebSocket_tmp != NULL)
    {
    	remove_any(WebSocket_head,WebSocket_tmp);
    }
    pthread_mutex_unlock(&SYS_INFO_mutex);
}


void SYS_INFO_lock( void ){
	pthread_mutex_lock(&SYS_INFO_mutex);
}
void SYS_INFO_unlock( void ){
	 pthread_mutex_unlock(&SYS_INFO_mutex);
}




