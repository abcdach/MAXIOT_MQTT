
//SYS_API__GET__MESSEGE(SLOT_INDEX, Buffer_1);
SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX, Buffer_1);
if (strlen(Buffer_1)>1){
	JSON2_parse("C");
	if (JSON_STATUS == 1){
		if(JSON_Long_Value == 0){
			JSON2_parse("S");
			if (JSON_STATUS == 1){
				if(JSON_Long_Value == OUT_DEV__OUTPUT){
					JSON2_s_parse("V");
					if (JSON_STATUS == 1){
						sprintf(Buffer_1,"{\"N\":\"0\",\"S\":\"%d\",\"V\":\"%s\"}\n",IN_DEV__INPUT ,JSON_Value);
						DEB_DE_Sent("<-- DE_SOC(%d) %s\r",sock,Buffer_1);
						write(sock , Buffer_1 , strlen(Buffer_1));
					}
				}
			}
		}
	}
}
