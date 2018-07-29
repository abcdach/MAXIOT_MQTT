JSON_parse("R");
if (JSON_STATUS == 1){
	if(JSON_Long_Value == 255){
		JSON_parse("T");
		if (JSON_STATUS == 1){
			DEVICE_ID = (unsigned long)JSON_Long_Value;
		} else {
			Sent_Error("READ FILE DATA","1","Error in JSON(T)");
			break;
		}
	   //#--------------------------------------------------------------------------
		SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
		if(SLOT_INDEX == -1){
			Sent_Error("READ Me DATA","1","SLOT_INDEX Error");break;
		}
		snprintf(CODE_IN,CODE_IN_LEN,"%s",SYS_API__GET__DEVICE_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX));

		STU_Sent("{\"F\":\"20\",\"R\":\"255\",\"T\":\"%ld\"}",(unsigned long)0);
		usleep(2000);
	} else {
		unsigned long FAME = (unsigned long)JSON_Long_Value;
		JSON_parse("T");
		if (JSON_STATUS == 1){
			unsigned long CODE_FAME = FAME * CODE_FRAME_LEN;
		//#---------------------------------------------
			unsigned long THIS_FAME_LEN = (unsigned long)JSON_Long_Value;
			//if((unsigned long)THIS_FAME_LEN > CODE_FRAME_LEN )break;
		//#---------------------------------------------
			char CODE_data[THIS_FAME_LEN+16];
			for (i = 0; i < THIS_FAME_LEN; i++){
				CODE_data[i] = CODE_IN[CODE_FAME];
				CODE_FAME ++;
			}CODE_data[THIS_FAME_LEN]=0;
		//#---------------------------------------------
			STU_Sent("{\"F\":\"5\",\"R\":\"%ld\",\"T\":\"%s\"}",(unsigned long)FAME,CODE_data);
		} else {
			Sent_Error("READ Me DATA","1","Error in JSON(T)");
			break;
		}

	}
	Sent_OK("READ Me DATA");
	break;

} else {
	Sent_Error("READ Me DATA","1","Error in JSON(R)");
	break;
}


