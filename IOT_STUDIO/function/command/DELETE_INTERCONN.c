//#-----------------------------------------------------
	JSON_parse("D1");
	if (JSON_STATUS != 1){Sent_Error("DELETE INTERCONN","1","Error in JSON(I)");break;}
	DEVICE_1_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_1_ID < 100)  {Sent_Error("DELETE INTERCONN","1","DELETE INTERCONN Error: DEVICE_1_ID < 100");break;}
	if(DEVICE_1_ID > 99999){Sent_Error("DELETE INTERCONN","1","DELETE INTERCONN Error: DEVICE_1_ID > 99999");break;}
//#-----------------------------------------------------
	JSON_parse("OU");
	if (JSON_STATUS != 1){Sent_Error("DELETE INTERCONN","1","Error in JSON(I)");break;}
	OUTPUT_ID = (unsigned char)JSON_Long_Value;
//#-----------------------------------------------------
	JSON_parse("D2");
	if (JSON_STATUS != 1){Sent_Error("DELETE INTERCONN","1","Error in JSON(I)");break;}
	DEVICE_2_ID = JSON_Long_Value;
	if(DEVICE_2_ID < 100)  {Sent_Error("DELETE INTERCONN","1","DELETE INTERCONN Error: DEVICE_2_ID < 100");break;}
	if(DEVICE_2_ID > 99999){Sent_Error("DELETE INTERCONN","1","DELETE INTERCONN Error: DEVICE_2_ID > 99999");break;}
	SLOT_1_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_2_ID);
	if(SLOT_1_INDEX == -1){Sent_Error("DELETE DEVICE","1","SLOT_1_INDEX Error");break;}
//#-----------------------------------------------------
	JSON_parse("IN");
	if (JSON_STATUS != 1){Sent_Error("DELETE INTERCONN","1","Error in JSON(I)");break;}
	INPUT_ID = (unsigned char)JSON_Long_Value;
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX((unsigned long)SLOT_1_INDEX,(unsigned char)INPUT_ID, 0);
	SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long)SLOT_1_INDEX,(unsigned char)INPUT_ID, 0);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_1_INDEX)){
		case TYPE_DE: EVENT_COUNTER__DELETE_INTERCONN__De ++; break;
		case TYPE_ME: EVENT_COUNTER__DELETE_INTERCONN__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__DELETE_INTERCONN__We ++; break;
		default:break;
	}
	EVENT_COUNTER__DELETE_INTERCONN ++;
	Sent_OK("DELETE INPUT");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#		inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,Server_message_LEN,"{\"F\":\"13\",\"D1\":\"%ld\",\"OU\":\"%ld\",\"D2\":\"%ld\",\"IN\":\"%ld\"}"
			 ,(unsigned long)DEVICE_1_ID
			 ,(unsigned long)OUTPUT_ID
			 ,(unsigned long)DEVICE_2_ID
			 ,(unsigned long)INPUT_ID);
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );**/
//#--------------------------------------------------------------------------
	break;


