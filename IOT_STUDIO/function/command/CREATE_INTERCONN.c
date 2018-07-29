//#-----------------------------------------------------
	JSON_parse("D1");
	if (JSON_STATUS != 1){Sent_Error("CREATE INTERCONN","1","Error: JSON(D1)");break;}
	DEVICE_1_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_1_ID < 100)  {Sent_Error("CREATE INTERCONN","1","Error: DEVICE_1_ID < 100");break;}
	if(DEVICE_1_ID > 99999){Sent_Error("CREATE INTERCONN","1","Error: DEVICE_1_ID > 99999");break;}
	SLOT_1_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_1_ID);
	if(SLOT_1_INDEX == -1){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: SLOT_1_INDEX");break;}
//#-----------------------------------------------------
	JSON_parse("D2");
	if (JSON_STATUS != 1){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: JSON(D2)");break;}
	DEVICE_2_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_2_ID < 100)  {Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: DEVICE_2_ID < 100");break;}
	if(DEVICE_2_ID > 99999){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: DEVICE_2_ID > 99999");break;}
	SLOT_2_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_2_ID);
	if(SLOT_2_INDEX == -1){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: SLOT_2_INDEX");break;}
//#-----------------------------------------------------
	JSON_parse("OU");
	if (JSON_STATUS != 1){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: JSON(OU)");break;}
	OUTPUT_ID = (unsigned char)JSON_Long_Value;
	if(SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_1_INDEX,(unsigned char)OUTPUT_ID)!=ENABLE)
	{Sent_Error("CREATE INTERCONN","1","Error: OUTPUT_ID not found");break;}
	if((OUTPUT_ID+1)>OUTPUT_LEN){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: OUTPUT_ID > OUTPUT_LEN");break;}
//#-----------------------------------------------------
	JSON_parse("IN");
	if (JSON_STATUS != 1){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: JSON(IN)");break;}
	INPUT_ID = (unsigned char)JSON_Long_Value;
	if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_2_INDEX,(unsigned char)INPUT_ID)!=ENABLE)
	{Sent_Error("CREATE INTERCONN","1","Error: INPUT_ID not found");break;}
	if((INPUT_ID+1)>INPUT_LEN){Sent_Error("CREATE INTERCONN","1","CREATE INTERCONN Error: INPUT_ID > INPUT_LEN");break;}
//#-----------------------------------------------------
	// arsebobs ukve aseti kavshiri tu araa ????
	Momxede_Me  = 0; // !!!!!!!!!!!!! SAGANGEBO MARKERI
//#--------------------------------------------------------------------------
//#	UPDATE RAM !!!
//#--------------------------------------------------------------------------
	SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX((unsigned long)SLOT_2_INDEX,(unsigned char)INPUT_ID,(unsigned long)DEVICE_1_ID);
	SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long)SLOT_2_INDEX,(unsigned char)INPUT_ID,(unsigned char)OUTPUT_ID);
//#--------------------------------------------------------------------------
//#	UPDATE EVENT COUNTER !!!
//#--------------------------------------------------------------------------
	switch(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_2_INDEX)){
		case TYPE_DE: EVENT_COUNTER__CREATE_INTERCONN__De ++; SYS_Signal_Counter__Add_Sensor_Input ++;break;
		case TYPE_ME: EVENT_COUNTER__CREATE_INTERCONN__Me ++; break;
		case TYPE_WE: EVENT_COUNTER__CREATE_INTERCONN__We ++; break;
		default:break;
	}
	EVENT_COUNTER__CREATE_INTERCONN ++;
	Sent_OK("CREATE INTERCONN");
//#--------------------------------------------------------------------------
//#	Save to File
//#--------------------------------------------------------------------------
	FOBJECTS__Save_Objects();
//#--------------------------------------------------------------------------
//#	inform other members about it !!!
//#--------------------------------------------------------------------------
/**	usleep(10000);
	snprintf(Server_message,Server_message_LEN,"{\"F\":\"4\",\"D1\":\"%ld\",\"OU\":\"%ld\",\"D2\":\"%ld\",\"IN\":\"%ld\"}"
			 ,(unsigned long)DEVICE_1_ID
			 ,(unsigned long)OUTPUT_ID
			 ,(unsigned long)DEVICE_2_ID
			 ,(unsigned long)INPUT_ID);
	//SYS_API__PUT__MESSEGE((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)IOT_STUDIO_CHANNEL_INDEX,Server_message);
	pthread_mutex_lock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );
	pthread_cond_broadcast( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_condition );
	pthread_mutex_unlock( &SLOT[IOT_STUDIO_CHANNEL_INDEX].Device_cond_mutex );	**/
//#------------------------------------------------
	break;

