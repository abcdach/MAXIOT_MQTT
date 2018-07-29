
if ((unsigned char)TA_STATUS==0){
	////////////////////////////////////////////////////////////////
	SATELIT[SATELIT_COUNTER].USER_ID = USER_ID;
	SATELIT[SATELIT_COUNTER].self	 = self;
	SATELIT[SATELIT_COUNTER].STATUS  = 1;
	SATELIT[SATELIT_COUNTER].INDEX   = SATELIT_COUNTER;
	SATELIT[SATELIT_COUNTER].SOCK    = sock;
	SATELIT[SATELIT_COUNTER].DEVICE_NAME = IOT_STUDIO_CHANNEL_DEVICE;
	////////////////////////////////////////////////////////////////
	pthread_t _WebSockets_Get_Sensor;
	if( pthread_create( &_WebSockets_Get_Sensor , &ATTR_STACK_SIZE ,  WebSockets_Get_Sensor , (void*) &SATELIT[SATELIT_COUNTER]) < 0){
	}
	////////////////////////////////////////////////////////////////
	SATELIT[SATELIT_COUNTER].STATUS=2;
	SATELIT_COUNTER++;
	////////////////////////////////////////////////////////////////
}
