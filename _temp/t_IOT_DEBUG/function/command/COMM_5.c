//#------------------------------------------------------------------------
	JSON_parse("INDEX");
//#------------------------------------------------------------------------
	if (JSON_STATUS == 1){
			long INDEX =  JSON_Long_Value;
			DEVICE_NAME = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(INDEX);//d0
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);//d1

			sprintf(data,"{\"COMM\":\"5\",\"INDEX\":\"%ld\",\"d0\":\"%ld\",\"d1\":\"%ld\",\"d2\":\"%ld\",\"d3\":\"%ld\",\"d4\":\"%ld\",\"d5\":\"%ld\",\"d6\":\"%ld\",\"d7\":\"%ld\"}"
					, INDEX
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 4)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 4)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 5)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 5)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 6)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 6)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 7)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 7));
			WebSock_Sent(data);
			break;
	}

//#------------------------------------------------------------------------
