




		pthread_attr_init(&ATTR_STACK_SIZE);
		pthread_attr_setstacksize(&ATTR_STACK_SIZE, STACK_SIZE_128);
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
		if(Enable___Time_Counter == 1){
			pthread_t _Time_server;
			if( pthread_create( &_Time_server , &ATTR_STACK_SIZE ,  Time_server , NULL))
			{
				printf("Time_server>> could not create thread\n\r");
				return 1;
			}
		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
//		if(Enable___Virtula_Debug == 1){
//			SYS_BUSY = 1;
//			pthread_t _WebSocket_SYS_INFO_server;
//			if( pthread_create( &_WebSocket_SYS_INFO_server , &ATTR_STACK_SIZE ,  WebSocket_SYS_INFO_server , NULL))
//			{
//				printf("WebSocket_SYS_INFO_server>> could not create thread\n\r");
//				return 1;
//			}
//			while(SYS_BUSY) usleep(100000);
//		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
		if(Enable___STUDIO_Server == 1){
			SYS_BUSY = 1;
			pthread_t _IOT_STUDIO_SERVER;
			if( pthread_create( &_IOT_STUDIO_SERVER , &ATTR_STACK_SIZE ,  IOT_STUDIO_SERVER , NULL))
			{
				printf("IOT_STUDIO_SERVER >> could not create thread\n\r");
				return 1;
			}
			while(SYS_BUSY) usleep(100000);
		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
		if(Enable___DE_Server == 1){
			SYS_BUSY = 1;
			pthread_t _Socket_Devices_server;
			if( pthread_create( &_Socket_Devices_server , &ATTR_STACK_SIZE ,  Socket_Devices_server , NULL))
			{
				printf("DE_SERVER >> could not create thread\n\r");
				return 1;
			}
			while(SYS_BUSY) usleep(100000);
		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
//		if(Enable___WE_Server == 1){
//			SYS_BUSY = 1;
//			pthread_t _WE_pthread__Prossesor;
//			if( pthread_create( &_WE_pthread__Prossesor , &ATTR_STACK_SIZE ,  WE_pthread__Prossesor , NULL))
//			{
//				printf("WE_SERVER >> could not create thread\n\r");
//				return 1;
//			}
//			while(SYS_BUSY) usleep(100000);
//		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
		if(Enable___ME_Server == 1){
			SYS_BUSY = 1;
			pthread_t _ME_pthread__Prossesor;
			if( pthread_create( &_ME_pthread__Prossesor , &ATTR_STACK_SIZE ,  ME_pthread__Prossesor , NULL))
			{
				printf("MEDITOR >> could not create thread\n\r");
				return 1;
			}
			while(SYS_BUSY) usleep(100000);
		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
//		if(Enable___SocDEB_Server == 1){
//			SYS_BUSY = 1;
//			pthread_t _SocDEB_Devices_server;
//			if( pthread_create( &_SocDEB_Devices_server , &ATTR_STACK_SIZE ,  SocDEB_Devices_server , NULL))
//			{
//				printf("SocDEB >> could not create thread\n\r");
//				return 1;
//			}
//			while(SYS_BUSY) usleep(100000);
//		}
	//#-------------------------------------------------------------------
	//#
	//#-------------------------------------------------------------------
