//#------------------------------------------------
	JSON_parse("D");
	if (JSON_STATUS != 1){Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: JSON(D)");break;}
	DEVICE_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: DEVICE_ID < 100");break;}
	if(DEVICE_ID > 99999){Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: DEVICE_ID > 99999");break;}
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX != -1) {Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: This device is already present in system");break;}
//#------------------------------------------------
	JSON_parse("T");
	if (JSON_STATUS != 1){Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: JSON(T)");break;}
	DEVICE_TYPE = (unsigned char)JSON_Long_Value;
//#------------------------------------------------
	JSON_parse("R");
	if (JSON_STATUS != 1){Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: JSON(R)");break;}
	DEVICE_ROOM = (unsigned char)JSON_Long_Value;
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__ADD__DEVICE_By_DEVICE_ID((unsigned long)DEVICE_ID);
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1){Sent_Error("CREATE DEVICE","1","CREATE DEVICE Error: SYSTEM RAM");break;}

	SYS_API__CLEANING__DEVICE_By_SLOT_INDEX((unsigned long)SLOT_INDEX);
	SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX((unsigned long)SLOT_INDEX); /// !!!! mutexis gasawmendi xom araa !!!!
	SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX((unsigned long)SLOT_INDEX, 1);
	SYS_API__PUT__DEVICE_X_By_SLOT_INDEX((unsigned long)SLOT_INDEX, 50);
	SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX((unsigned long)SLOT_INDEX, 100);
	SYS_API__PUT__DEVICE_ROOM_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)DEVICE_ROOM);
	SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX, "Undefined !!!");
	switch(DEVICE_TYPE){
		case TYPE_ME:
			SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX, Default_Python_Code);break;
		default:
			SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX, "");break;
	}
	SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,DATA_NEW);
	SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)DEVICE_TYPE);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	EVENT_COUNTER__CREATE_DEVICE ++;
	switch(DEVICE_TYPE){
		case TYPE_DE: EVENT_COUNTER__CREATE_DEVICE__De ++; break;
		case TYPE_ME: EVENT_COUNTER__CREATE_DEVICE__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__CREATE_DEVICE__We ++; break;
		default:break;
	}
	Sent_OK("CREATE DEVICE");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#	inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,Server_message_LEN,"{\"F\":\"1\",\"D\":\"%ld\",\"I\":\"%s\",\"T\":\"%ld\",\"X\":\"%ld\",\"Y\":\"%ld\",\"R\":\"%ld\",\"U\":\"1\"}"
		,(unsigned long)DEVICE_ID
		,"undefined"
		,(unsigned long)DEVICE_TYPE
		,(unsigned long)50
		,(unsigned long)100
		,(unsigned long)DEVICE_ROOM);
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#--------------------------------------------------------------------------
	break;




