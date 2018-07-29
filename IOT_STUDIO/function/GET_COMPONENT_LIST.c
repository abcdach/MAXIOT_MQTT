


if ((unsigned char)TA_STATUS==0){
	//#####################################################################
	//# DEVICE
	//#####################################################################
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 STU_Sent("{\"F\":\"1\",\"D\":\"%ld\",\"I\":\"%s\",\"T\":\"%ld\",\"X\":\"%ld\",\"Y\":\"%ld\",\"R\":\"%ld\"}"
						 , (unsigned long)DEVICE_ID
						 , SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_X_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_Y_By_SLOT_INDEX((unsigned long )SLOT_INDEX)
						 , (unsigned long)SYS_API__GET__DEVICE_ROOM_By_SLOT_INDEX((unsigned long )SLOT_INDEX));
				 usleep(2000);

				 if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX) == IS_RUN){
					 STU_Sent("{\"C\":\"5\",\"D\":\"%ld\",\"V\":\"1\"}",(unsigned long)DEVICE_ID);
				 }
				 usleep(2000);
			}
	}

	//#####################################################################
	//# INPUT
	//#####################################################################
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < INPUT_LEN; ii++){
					 if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long )SLOT_INDEX, (unsigned char)ii)==ENABLE){
							 STU_Sent("{\"F\":\"2\",\"D\":\"%ld\",\"S\":\"%ld\",\"V\":\"%s\"}"
									 ,(unsigned long )DEVICE_ID
									 ,(unsigned long )ii
									 ,SYS_API__GET__INPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii));
							 usleep(2000);
					 }
				 }
			}
	}
	//#####################################################################
	//# OUTPUT
	//#####################################################################
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < OUTPUT_LEN; ii++){
					if(SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii)==ENABLE){
						 STU_Sent("{\"F\":\"3\",\"D\":\"%ld\",\"S\":\"%ld\",\"V\":\"%s\"}"
								 ,(unsigned long)DEVICE_ID
								 ,(unsigned long)ii
								 ,SYS_API__GET__OUTPUT_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii));
						 usleep(2000);
						 //#####################################################################
						 SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii, CODE_IN);
						 STU_Sent("{\"F\":\"17\",\"D\":\"%ld\",\"S\":\"%ld\",\"I\":\"%s\"}"
								 ,(unsigned long)DEVICE_ID
								 ,(unsigned long)ii
								 ,CODE_IN);
						 usleep(2000);
						 //#####################################################################
						 STU_Sent("{\"F\":\"18\",\"D\":\"%ld\",\"S\":\"%ld\",\"I\":\"%ld\"}"
								 ,(unsigned long)DEVICE_ID
								 ,(unsigned long)ii
								 ,SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX((unsigned long)SLOT_INDEX, (unsigned char)ii));
						 usleep(2000);
					} else break;
				 }
			}
	}
	//#####################################################################
	//# INTERCONN
	//#####################################################################
	for (i = 0; i < SYS_API__GET__SLOTSYS_USED_SLOTS_NUMBER(); i++){
		//#------------------------------------------------------------------
			DEVICE_ID = SYS_API__GET__DEVICE_ID_By_DEVICE_INDEX((unsigned long )i);//$
			if (DEVICE_ID < 100)continue;
			SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long )DEVICE_ID);//$
		//#------------------------------------------------------------------
			if(SLOT_INDEX != -1){
				 for (ii = 0; ii < INPUT_LEN; ii++){
					 if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long )SLOT_INDEX, (unsigned char)ii)==ENABLE){//$
							unsigned long LISTEN_DEVICE_ID = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii);
							unsigned char LISTEN_DEVICE_OUTPUT_INDEX = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long )SLOT_INDEX,(unsigned char)ii);
							if(LISTEN_DEVICE_ID != 0){
								STU_Sent("{\"F\":\"4\",\"D1\":\"%ld\",\"OU\":\"%ld\",\"D2\":\"%ld\",\"IN\":\"%ld\"}"
										 ,(unsigned long)LISTEN_DEVICE_ID
										 ,(unsigned long)LISTEN_DEVICE_OUTPUT_INDEX,DEVICE_ID
										 ,(unsigned long)ii );
								usleep(2000);
							}
					 } else break;
				 }
			}
	}
	//#####################################################################
	//# END
	//#####################################################################
	STU_Sent("{\"F\":\"9\",\"i\":\"CONFIGURATION COMPLETED\"}");
}



