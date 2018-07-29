JSON_parse("RE");
if (JSON_STATUS == 1){
	if(JSON_Long_Value != 255){
		//#---------------------------------------------
			unsigned long CODE_FAME = (unsigned long)JSON_Long_Value * CODE_FRAME_LEN;
			unsigned long FAME = (unsigned long)JSON_Long_Value;
		//#---------------------------------------------
			JSON_parse("TE");
			if (JSON_STATUS == 1){
				unsigned long THIS_FAME_LEN = (unsigned long)JSON_Long_Value;
				if((unsigned long)THIS_FAME_LEN > CODE_FRAME_LEN )break;
			//#---------------------------------------------
				char CODE_data[CODE_FRAME_LEN+16];
				for (i = 0; i < THIS_FAME_LEN; i++){
					CODE_data[i] = CODE_IN[CODE_FAME];
					CODE_FAME ++;
				}CODE_data[THIS_FAME_LEN]=0;
			//#---------------------------------------------
				STU_Sent("{\"F\":\"6\",\"R\":\"%ld\",\"T\":\"%s\"}"
						,(unsigned long)FAME
						,CODE_data);
		} else {
			Sent_Error("READ InOut DATA","1","Error in JSON(TE)");
			break;
		}
	} else {
	//#---------------------------------------------
		unsigned char IN_OR_OUT_ID = 0;
		char IN_OR_OUT[10];
	//#---------------------------------------------
		JSON_parse("DE");
		if (JSON_STATUS == 1){
			DEVICE_ID = (unsigned long)JSON_Long_Value;
		} else {
			Sent_Error("READ InOut DATA","1","Error in JSON(DE)");
			break;
		}
	//#--------------------------------------------------------------------------
		SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
		if(SLOT_INDEX == -1){
			Sent_Error("READ InOut DATA","1","SLOT_INDEX Error");break;
		}
	//#---------------------------------------------
		JSON_parse("IN");
		if (JSON_STATUS == 1){
			IN_OR_OUT_ID = (unsigned char)JSON_Long_Value;
		} else {
			Sent_Error("READ InOut DATA","1","Error in JSON(IN)");
			break;
		}
	//#---------------------------------------------
		JSON_s_parse("TY");
		if (JSON_STATUS == 1){
			snprintf(IN_OR_OUT,10,"%s",JSON_Value);
		} else {
			Sent_Error("READ InOut DATA","1","Error in JSON(TY)");
			break;
		}
	//#---------------------------------------------
		if(MySQL_GET_IN_OR_OUT_OBJECT_DATA(IN_OR_OUT, DEVICE_ID, IN_OR_OUT_ID, CODE_IN)!=0){
			Sent_Error("READ InOut DATA","1","Mysql error");
			break;
		}
		STU_Sent("{\"F\":\"6\",\"R\":\"255\",\"T\":\"%ld\"}",(unsigned long)strlen(CODE_IN));
		usleep(2000);
	}
	Sent_OK("READ InOut DATA");
	break;
} else {
	Sent_Error("READ InOut DATA","1","Error in JSON(RE)");
	break;
}
