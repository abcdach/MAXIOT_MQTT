


printf("--> SYS : %s\n\r",MAXIOT.Server_message);
//####################################################
MAXIOT.CONNECTION_STATUS = 1;
//####################################################
pthread_attr_t ATTR_STACK_SIZE;
pthread_attr_init(&ATTR_STACK_SIZE);
pthread_attr_setstacksize(&ATTR_STACK_SIZE, 128*1024);
//SATELIT.SOCK = sock;
pthread_t _MAXIOT_PING;
if( pthread_create( &_MAXIOT_PING , &ATTR_STACK_SIZE ,  MAXIOT_PING , NULL) < 0){
	printf("... SYS : could not create thread\n\r");
	MAXIOT.CONNECTION_STATUS = 0;
	STATUS=255;
}
//####################################################


