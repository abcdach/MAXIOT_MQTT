



//SYS_API__GET__MESSEGE(SLOT_INDEX,SENSOR_message);
SYS_API__GET__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,SENSOR_message);
if (strlen(SENSOR_message)>1){
	JSON_parse("C");
	if (JSON_STATUS == 1){
		if(JSON_Long_Value == 0){
			JSON_parse("S");
			if (JSON_STATUS == 1){
				if (JSON_Long_Value == OUT_DEV__OUTPUT){
					JSON_s_parse("V");
					if (JSON_STATUS == 1){
					//#---------------------------------------------------------------
						sprintf(SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.DATA[IN_DEV__INPUT],"%s",JSON_Value);
						SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.DATA_STATUS[IN_DEV__INPUT] = 1;

						if(SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.PUSH[IN_DEV__INPUT]==1){
							pthread_mutex_lock(&SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.mutex);
							pthread_cond_signal(&SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.cond);
							pthread_mutex_unlock(&SLOT[IN_DEV__SLOT_INDEX].MEDIATOR.mutex);
						}
					}
				}
			}
		}
	}
}




