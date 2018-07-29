//#------------------------------------------------------------------------
	JSON_parse("INDEX");
//#------------------------------------------------------------------------
	if (JSON_STATUS == 1){
			long INDEX =  JSON_Long_Value;
			DEVICE_NAME = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX(INDEX);//d0
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);//d1

			sprintf(data,"{\"COMM\":\"4\",\"INDEX\":\"%ld\",\"d0\":\"%ld\",\"d1\":\"%ld\",\"d2\":\"%ld\",\"d3\":\"%ld\",\"d4\":\"%ld\",\"d5\":\"%ld\",\"d6\":\"%ld\",\"d7\":\"%ld\"}"
					, INDEX
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 0)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 0)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 1)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 1)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 2)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 2)
					, SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, 3)
					, (long)SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, 3));
			WebSock_Sent(data);
			break;
	}

//#------------------------------------------------------------------------
