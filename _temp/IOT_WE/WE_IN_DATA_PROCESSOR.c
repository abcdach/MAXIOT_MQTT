//#----------------------------------------------------------
	//SYS_API__GET__MESSEGE((long)SLOT_INDEX,Buffer_0);
	SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX((long)SLOT_INDEX,Buffer_0);
//#----------------------------------------------------------
	if (strlen(Buffer_0)>1){
		JSON2_parse("C");
		if (JSON_STATUS == 1){
			if(JSON_Long_Value == 0){
				JSON2_parse("S");
				if (JSON_STATUS == 1){
					S_Velue = (unsigned char)JSON_Long_Value;

					JSON2_s_parse("V");
					if (JSON_STATUS == 1){
						snprintf(Buffer_1,Buffer_1_LEN,"%s",JSON_Value);
						if((unsigned long)OUT_DEV__NAME == (unsigned long)IN_DEV__NAME){// gadamrtvelis , slaideris agdgenisas - outputebis agdgenisas miaqcie yuradgeba S_Velue-us
							snprintf(Buffer_0,Buffer_0_LEN,"{\"N\":\"3\",\"S\":\"%ld\",\"V\":\"%s\"}\n"
									,(unsigned long)S_Velue ,Buffer_1);
							//DEB_WE_Sent("<-- WE_SOC(%d) %s\r",sock,Buffer_0);
							WebSOC_TDATA_Processing(Buffer_1,Buffer_0);
							write(sock , Buffer_1 , strlen(Buffer_1));
						}else{
							if((unsigned char)S_Velue == (unsigned char)OUT_DEV__OUTPUT){//*** FILTER(OUTPUT)
								snprintf(Buffer_0,Buffer_0_LEN,"{\"N\":\"0\",\"S\":\"%d\",\"V\":\"%s\"}\n"
										,(unsigned char)IN_DEV__INPUT
										,Buffer_1);
								//DEB_WE_Sent("xx<-- WE_SOC(%d) %s\n\r",sock,Buffer_0);
								WebSOC_TDATA_Processing(Buffer_1,Buffer_0);
								write(sock , Buffer_1 , strlen(Buffer_1));
							}
						}
					}
				}
			}
		}
	}





