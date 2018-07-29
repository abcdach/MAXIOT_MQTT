JSON_parse("D");
//------------------------------------------------------------------------
if (JSON_STATUS == 1){
	////////////////////////////////////////////////////////////////
	DEVICE_ID = (unsigned long)JSON_Long_Value;
	if(DEVICE_ID < 100)  {Sent_OK("START STREAMING");break;}
	if(DEVICE_ID > 99999){Sent_OK("START STREAMING");break;}
	SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_ID);
	if(SLOT_INDEX == -1) {Sent_OK("START STREAMING");break;}
	////////////////////////////////////////////////////////////////
	SATELIT[SATELIT_COUNTER].USER_ID = USER_ID;
	SATELIT[SATELIT_COUNTER].self	 = self;
	SATELIT[SATELIT_COUNTER].STATUS  = 1;
	SATELIT[SATELIT_COUNTER].INDEX   = SATELIT_COUNTER;
	SATELIT[SATELIT_COUNTER].SOCK    = sock;
	SATELIT[SATELIT_COUNTER].DEVICE_NAME = DEVICE_ID;
	////////////////////////////////////////////////////////////////
	pthread_t _WebSockets_Get_Sensor;
	if( pthread_create( &_WebSockets_Get_Sensor , &ATTR_STACK_SIZE ,  WebSockets_Get_Sensor , (void*) &SATELIT[SATELIT_COUNTER]) < 0){
	}
	////////////////////////////////////////////////////////////////
	SATELIT[SATELIT_COUNTER].STATUS=2;
	SATELIT_COUNTER++;
	////////////////////////////////////////////////////////////////
	Sent_OK("START STREAMING");
	////////////////////////////////////////////////////////////////
	break;
} else {
	Sent_Error("START STREAMING","1","Error in JSON(D)");
}
