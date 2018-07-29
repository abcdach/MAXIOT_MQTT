#define CODE_FRAME_LEN		80
JSON_parse("SA");
if (JSON_STATUS == 1){
	if(JSON_Long_Value != 255){
		//#---------------------------------------------------
			if (JSON_Long_Value == 0) CODE_LEN = 0;
			unsigned long CODE_FRAME  = (unsigned long)JSON_Long_Value * CODE_FRAME_LEN;
		//#---------------------------------------------------
			JSON_s_parse("TE");
			if (JSON_STATUS += 1){
				for (i = 0; i < JSON_Len; i++){
						CODE_IN[CODE_FRAME] = JSON_Value[i];
						CODE_FRAME ++;
					} CODE_LEN += JSON_Len;
			} else {
				Sent_Error("WRITE InOut DATA","1","Error in JSON(TE)");
			}
	} else {
			CODE_IN[CODE_LEN]=0;
			unsigned char IN_OR_OUT_ID = 0;
			char IN_OR_OUT[10];
		//#--------------------------------------------------------------------------
			JSON_parse("DE");
			if (JSON_STATUS == 1){
				DEVICE_ID = (unsigned long)JSON_Long_Value;
			} else {
				Sent_Error("WRITE InOut DATA","1","Error in JSON(DE)");
				break;
			}
		 //#--------------------------------------------------------------------------
			SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
			if(SLOT_INDEX == -1){
				Sent_Error("WRITE InOut DATA","1","SLOT_INDEX Error");break;
			}
		 //#--------------------------------------------------------------------------
			JSON_parse("IN");
			if (JSON_STATUS == 1){
				IN_OR_OUT_ID = (unsigned char)JSON_Long_Value;
			} else {
				Sent_Error("WRITE InOut DATA","1","Error in JSON(IN)");break;
			}
		//#--------------------------------------------------------------------------
			JSON_s_parse("TY");
			if (JSON_STATUS == 1){
				snprintf(IN_OR_OUT,10,"%s",JSON_Value);
			} else {
				Sent_Error("WRITE InOut DATA","1","Error in JSON(TY)");break;
			}
		//#--------------------------------------------------------------------------
			if(MySQL_PUT_IN_OR_OUT_OBJECT_DATA(IN_OR_OUT, DEVICE_ID, IN_OR_OUT_ID, CODE_IN)!=0){
				//Sent_Error("WRITE InOut DATA","1","Mysql error");break;
			}
		//#--------------------------------------------------------------------------
		//#	Save to File
		//#--------------------------------------------------------------------------
			//FOBJECTS__Save_Objects();
		//#--------------------------------------------------------------------------
			Sent_OK("WRITE InOut DATA");
			break;
	}
	Sent_OK("WRITE InOut DATA");
	break;
} else {
	Sent_Error("WRITE InOut DATA","1","Error in JSON(SA)");
	break;
}









