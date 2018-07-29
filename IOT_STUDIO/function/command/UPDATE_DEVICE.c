//#--------------------------------------------------------------------------
	JSON_parse("D");
	if (JSON_STATUS != 1){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: JSON(D)");break;}
	DEVICE_ID =  (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: DEVICE_ID < 100");break;}
	if(DEVICE_ID > 99999){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: DEVICE_ID > 99999");break;}
	SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);//$
	if(SLOT_INDEX == -1) {Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: SLOT_INDEX");break;}
//#--------------------------------------------------------------------------
	JSON_s_parse("I");
	if (JSON_STATUS != 1){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: JSON(I)");break;}
	char DEVICE_DESCRIPTION[DEVICE_DESCRIPTION_LEN];
	snprintf(DEVICE_DESCRIPTION,DEVICE_DESCRIPTION_LEN,"%s",JSON_Value);
//#--------------------------------------------------------------------------
	JSON_parse("T");
	if (JSON_STATUS != 1){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: JSON(T)");break;}
	DEVICE_TYPE = (unsigned char)JSON_Long_Value;
//#--------------------------------------------------------------------------
	JSON_parse("X");
	if (JSON_STATUS != 1){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: JSON(X)");break;}
	DEVICE_X = (unsigned short)JSON_Long_Value;
//#--------------------------------------------------------------------------
	JSON_parse("Y");
	if (JSON_STATUS != 1){Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: JSON(Y)");break;}
	DEVICE_Y = (unsigned short)JSON_Long_Value;
//#--------------------------------------------------------------------------
//#	UPDATE SQL !!!
//#--------------------------------------------------------------------------
//	if(MySQL_UPDATE_DEVICE_OBJECTS(DEVICE_ID, DEVICE_X, DEVICE_Y, DEVICE_DESCRIPTION)!=0){
//		Sent_Error("UPDATE DEVICE","1","UPDATE DEVICE Error: Mysql");
//		break;
//	}
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX((unsigned long )SLOT_INDEX,1);//$
	SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)DEVICE_TYPE);//$
	SYS_API__PUT__DEVICE_X_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned short)DEVICE_X);//$
	SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned short)DEVICE_Y);//$
	SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX,DEVICE_DESCRIPTION);//$
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(DEVICE_TYPE){
		case TYPE_DE: EVENT_COUNTER__UPDATE_DEVICE__De ++; break;
		case TYPE_ME: EVENT_COUNTER__UPDATE_DEVICE__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__UPDATE_DEVICE__We ++; break;
		default:break;
	}
	EVENT_COUNTER__UPDATE_DEVICE ++;
	Sent_OK("UPDATE DEVICE");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#	inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,client_message_LEN,"{\"F\":\"1\",\"D\":\"%ld\",\"I\":\"%s\",\"T\":\"%ld\",\"X\":\"%ld\",\"Y\":\"%ld\",\"R\":\"%ld\",\"U\":\"%ld\"}"
			 , DEVICE_ID
			 , SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX)
			 , (unsigned long)SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_INDEX)
			 , (unsigned long)SYS_API__GET__DEVICE_X_By_SLOT_INDEX((unsigned long)SLOT_INDEX)
			 , (unsigned long)SYS_API__GET__DEVICE_Y_By_SLOT_INDEX((unsigned long)SLOT_INDEX)
			 , (unsigned long)SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX((unsigned long)SLOT_INDEX)
			 , USER_ID);
	//SYS_API__PUT__MESSEGE(IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#--------------------------------------------------------------------------
	break;



