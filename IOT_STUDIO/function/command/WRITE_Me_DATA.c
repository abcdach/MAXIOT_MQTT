JSON_parse("W");
if (JSON_STATUS == 1){
	if(JSON_Long_Value != 255){
		//#---------------------------------------------------
			if (JSON_Long_Value == 0) CODE_LEN = 0;
			unsigned long CODE_FRAME  = (unsigned long)JSON_Long_Value * CODE_FRAME_LEN;
		//#---------------------------------------------------
			JSON_s_parse("T");
			if (JSON_STATUS == 1){
				for (i = 0; i < JSON_Len; i++){
					CODE_IN[CODE_FRAME] = JSON_Value[i];
					CODE_FRAME ++;
				}
				CODE_LEN += JSON_Len;
				Sent_OK("WRITE Me DATA");
				break;
			} else {
				Sent_Error("WRITE Me DATA","1","Error in JSON(T)");
				break;
			}
	} else {
			CODE_IN[CODE_LEN]  = 0;
			unsigned long UPDATE_DEVICE = 0;
			JSON_parse("T");
			if (JSON_STATUS == 1){
				UPDATE_DEVICE = (unsigned long)JSON_Long_Value;
			} else {
				Sent_Error("WRITE Me DATA","1","Error in JSON(T)");break;
			}
		//#--------------------------------------------------------------------------
			SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)UPDATE_DEVICE);
			if(SLOT_INDEX == -1){
				Sent_Error("WRITE Me DATA","1","SLOT_INDEX Error");break;
			}
			SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX, CODE_IN);
			SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,DATA_NEW);
		//#--------------------------------------------------------------------------
		//#	Save to File
		//#--------------------------------------------------------------------------
			FOBJECTS__Save_Objects();
		//#--------------------------------------------------------------------------
			Sent_OK("WRITE Me DATA");
			break;
		//#--------------------------------------------------------------------------
	}
} else {
	Sent_Error("WRITE Me DATA","1","Error in JSON(W)");
	break;
}









