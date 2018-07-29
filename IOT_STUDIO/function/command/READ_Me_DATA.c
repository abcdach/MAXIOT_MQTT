//------------------------------------------------------------
	JSON_parse("X");
	if (JSON_STATUS == 1){ JSON_Long_X = (unsigned long)JSON_Long_Value;
	} else {
		Sent_Error("READ Me DATA","1","Error in JSON(X)");
		break;
	}
//------------------------------------------------------------
	JSON_parse("Y");
	if (JSON_STATUS == 1){ JSON_Long_Y = (unsigned long)JSON_Long_Value;
	} else {
		Sent_Error("READ Me DATA","1","Error in JSON(Y)");
		break;
	}
//------------------------------------------------------------
	JSON_parse("Z");
	if (JSON_STATUS == 1){ DEVICE_ID = (unsigned long)JSON_Long_Value;
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1){
		Sent_Error("READ Me DATA","1","SLOT_INDEX Error");
		break;
	}
	} else {
		Sent_Error("READ Me DATA","1","Error in JSON(Z)");
		break;
	}
//------------------------------------------------------------
	if(JSON_Long_X == 0){
		if(JSON_Long_Y == 0){
			snprintf(CODE_IN,CODE_IN_LEN,"%s",SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX));
			STU_Sent("{\"F\":\"5\",\"X\":\"0\",\"Y\":\"0\",\"Z\":\"%ld\"}",(unsigned long)strlen(CODE_IN));
			usleep(2000);
			break;
		}
	}
//------------------------------------------------------------
	for (i = 0; i < JSON_Long_Y; i++) JSON_Value[i] = CODE_IN[JSON_Long_X++];
	JSON_Value[JSON_Long_Y] = 0;
	STU_Sent("{\"F\":\"5\",\"X\":\"%ld\",\"Y\":\"%ld\",\"Z\":\"%s\"}",JSON_Long_X,JSON_Long_Y,JSON_Value);

	break;
//------------------------------------------------------------



