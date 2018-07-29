//------------------------------------------------------------
	JSON_parse("X");
	if (JSON_STATUS == 1){ JSON_Long_X = (unsigned long)JSON_Long_Value;
	} else {
		Sent_Error("READ File","1","Error in JSON(X)");
		break;
	}
//------------------------------------------------------------
	JSON_parse("Y");
	if (JSON_STATUS == 1){ JSON_Long_Y = (unsigned long)JSON_Long_Value;
	} else {
		Sent_Error("READ File","1","Error in JSON(Y)");
		break;
	}
//------------------------------------------------------------
	JSON_s_parse("Z");
	if (JSON_STATUS == 1){
		if( strlen(JSON_Value) > 0 ){
			_b64_decode(JSON_Value, FILE_PATH);
		} else {
			Sent_Error("READ File","1","Error in FILE_PATH");
			break;
		}
	} else {
		Sent_Error("READ File","1","Error in JSON(Z)");
		break;
	}
//------------------------------------------------------------
	_b64_decode(JSON_Value, FILE_PATH);
//------------------------------------------------------------
	if(JSON_Long_X == 0){
		if(JSON_Long_Y == 0){
			long F_LEN = SYS_API__GET__FILE_Len_By_FILE_Path(FILE_PATH);
			STU_Sent("{\"F\":\"20\",\"X\":\"0\",\"Y\":\"0\",\"Z\":\"%ld\"}",F_LEN);
			break;
		}
	}
//------------------------------------------------------------
	FILE *fp;
	fp = fopen(FILE_PATH,"r");
	if( fp == NULL ){
		Sent_Error("READ File","1","Error in JSON(Z)");
		break;
	}
	fseek( fp, JSON_Long_X, SEEK_SET );
	for (i = 0; i < JSON_Long_Y; i++)JSON_Value[i] = fgetc(fp);
	JSON_Value[JSON_Long_Y] = 0;
	fclose(fp);
//------------------------------------------------------------
	_b64_encode(JSON_Value,CODE_IN);
//------------------------------------------------------------
	STU_Sent("{\"F\":\"20\",\"X\":\"%ld\",\"Y\":\"%ld\",\"Z\":\"%s\"}",JSON_Long_X,JSON_Long_Y,CODE_IN);
//------------------------------------------------------------
	break;










