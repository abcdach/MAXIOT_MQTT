//#------------------------------------------------------------------------
	JSON_parse("READ_INDEX1");
//#------------------------------------------------------------------------
	if (JSON_STATUS == 1){
			long INDEX =  JSON_Long_Value;
			DEVICE_NAME = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(INDEX);//d0
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);//d1

			if(SLOT_INDEX != -1){
				sprintf(data,"{\"INDEX1\":\"%ld\",\"d0\":\"%ld\",\"d1\":\"%ld\",\"d2\":\"%ld\",\"d3\":\"%ld\",\"d4\":\"%ld\",\"d5\":\"%ld\",\"d6\":\"%s\"}"
						, INDEX
						, DEVICE_NAME
						, SLOT_INDEX
						, SYS_API__GET__DEVICE_USER_INDEX_By_SLOT_INDEX(SLOT_INDEX)
						, (long)SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX)
						, (long)SYS_API__GET__DEVICE_X_By_SLOT_INDEX(SLOT_INDEX)
						, (long)SYS_API__GET__DEVICE_Y_By_SLOT_INDEX(SLOT_INDEX)
						, SYS_API__GET__NAME_TEXT_By_SLOT_INDEX(SLOT_INDEX));
			//printf("WebSo(%d)>> %s\n\r",sock,data);
			} else {
				sprintf(data,"{\"INDEX1\":\"%ld\",\"d0\":\"%ld\",\"d1\":\"%ld\",\"d2\":\"%ld\",\"d3\":\"%ld\",\"d4\":\"%ld\",\"d5\":\"%ld\",\"d6\":\"%ld\"}"
						, INDEX
						, (long)-1
						, (long)-1
						, (long)-1
						, (long)-1
						, (long)-1
						, (long)-1
						, (long)-1);
			}


			WebSock_Sent(data);
			break;
	}

//#------------------------------------------------------------------------
