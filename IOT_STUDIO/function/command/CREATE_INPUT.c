//#-----------------------------------------------------
	JSON_parse("D");
	if (JSON_STATUS != 1){Sent_Error("CREATE INPUT","1","CREATE INPUT Error: JSON(D)");break;}
	DEVICE_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_Error("CREATE INPUT","1","CREATE INPUT Error: DEVICE_ID < 100");break;}
	if(DEVICE_ID > 99999){Sent_Error("CREATE INPUT","1","CREATE INPUT Error: DEVICE_ID > 99999");break;}
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1) {Sent_Error("CREATE INPUT","1","CREATE INPUT Error: SLOT_INDEX");break;}
//#-----------------------------------------------------
	JSON_parse("I");
	if (JSON_STATUS != 1){Sent_Error("CREATE INPUT","1","CREATE INPUT Error: JSON(I)");break;}
	INPUT_ID = (unsigned char)JSON_Long_Value;
	if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)INPUT_ID)==ENABLE){Sent_OK("CREATE INPUT");break;}
	if((INPUT_ID+1)>INPUT_LEN){Sent_Error("CREATE INPUT","1","CREATE INPUT Error: INPUT_ID > INPUT_LEN");break;}
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__PUT__INPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)INPUT_ID, ENABLE);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX)){
		case TYPE_DE: EVENT_COUNTER__CREATE_INPUT__De ++; SYS_Signal_Counter__Add_Sensor_Input ++; break;
		case TYPE_ME: EVENT_COUNTER__CREATE_INPUT__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__CREATE_INPUT__We ++; break;
		default:break;
	}
	EVENT_COUNTER__CREATE_INPUT ++;
	Sent_OK("CREATE INPUT");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#	inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,Server_message_LEN,"{\"F\":\"2\",\"D\":\"%ld\",\"I\":\"%ld\"}"
			,(unsigned long)DEVICE_ID
			,(unsigned long)INPUT_ID);
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#------------------------------------------------
	break;
