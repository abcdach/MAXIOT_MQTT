//#-----------------------------------------------------
	JSON_parse("D");
	if(JSON_STATUS != 1){Sent_Error("DELETE DEVICE","1","DELETE DEVICE Error: JSON(D)");break;}
	DEVICE_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_Error("DELETE DEVICE","1","DELETE DEVICE Error: DEVICE_ID < 100");break;}
	if(DEVICE_ID > 99999){Sent_Error("DELETE DEVICE","1","DELETE DEVICE Error: DEVICE_ID > 99999");break;}
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1){Sent_Error("DELETE DEVICE","1","DELETE DEVICE Error: SLOT_INDEX");break;}
//#--------------------------------------------------------------------------
//#	UPDATE SQL !!!
//#--------------------------------------------------------------------------
//	if(MySQL_DELETE_DEVICE_OBJECTS(DEVICE_ID)!=0){
//		Sent_Error("DELETE DEVICE","1","DELETE DEVICE Error: Mysql");
//		break;
//	}
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__CLEANING__DEVICE_By_SLOT_INDEX((unsigned long)SLOT_INDEX);
	SYS_API__DELATE__DEVICE_By_DEVICE_ID((unsigned long)DEVICE_ID);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX)){
		case TYPE_DE: EVENT_COUNTER__DELETE_DEVICE__De ++; break;
		case TYPE_ME: EVENT_COUNTER__DELETE_DEVICE__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__DELETE_DEVICE__We ++; break;
		default:break;
	}
	EVENT_COUNTER__DELETE_DEVICE ++;
	Sent_OK("DELETE DEVICE");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#		inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,Server_message_LEN,"{\"F\":\"7\",\"D\":\"%ld\",\"U\":\"%ld\"}"
			,(unsigned long)DEVICE_ID
			,(unsigned long)USER_ID );
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#--------------------------------------------------------------------------
	break;


