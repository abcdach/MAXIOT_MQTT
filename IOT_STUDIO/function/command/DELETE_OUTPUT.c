//#-----------------------------------------------------
	JSON_parse("D");
	if (JSON_STATUS != 1){Sent_Error("DELETE OUTPUT","1","DELETE OUTPUT Error: JSON(D)");break;}
	DEVICE_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_Error("DELETE OUTPUT","1","DELETE OUTPUT Error: DEVICE_ID < 100");break;}
	if(DEVICE_ID > 99999){Sent_Error("DELETE OUTPUT","1","DELETE OUTPUT Error: DEVICE_ID > 99999");break;}
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1){Sent_OK("DELETE OUTPUT");break;}
//#-----------------------------------------------------
	JSON_parse("I");
	if (JSON_STATUS != 1){Sent_Error("DELETE OUTPUT","1","DELETE OUTPUT Error: JSON(I)");break;}
	OUTPUT_ID = (unsigned char)JSON_Long_Value;
//#--------------------------------------------------------------------------
//#	UPDATE SQL !!!
//#--------------------------------------------------------------------------
//	if(MySQL_DELETE_OUTPUT_OBJECTS(DEVICE_ID, OUTPUT_ID)!=0){
//		Sent_Error("DELETE OUTPUT","1","DELETE OUTPUT Error: Mysql");
//		break;
//	}
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__PUT__OUTPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)OUTPUT_ID,DISABLE);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_INDEX)){
		case TYPE_DE: EVENT_COUNTER__DELETE_OUTPUT__De ++; break;
		case TYPE_ME: EVENT_COUNTER__DELETE_OUTPUT__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__DELETE_OUTPUT__We ++; break;
		default:break;
	}
	EVENT_COUNTER__DELETE_OUTPUT ++;
	Sent_OK("DELETE OUTPUT");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#		inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	sprintf(Server_message,"{\"F\":\"11\",\"D\":\"%ld\",\"I\":\"%ld\"}"
			,(unsigned long)DEVICE_ID
			,(unsigned long)OUTPUT_ID);
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#--------------------------------------------------------------------------
	break;


