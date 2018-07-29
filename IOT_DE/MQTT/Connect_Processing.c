DEV.A = 0;
DEV.B = 0;
DEV.C = 0;
DEV.E = 0;
DEV.Error  = 0;
DEV.D[0]  = 0;
DEV.Description[0]  = 0;
DEV.Description_len = 0;
DEV.ID = 0;


for( DEV.E = 0; DEV.E < MQTT.Client_ID_Length; DEV.E++ ){
	if( DEV.C == 0 ){
		if( isdigit(MQTT.Client_ID[DEV.E]) != 0){
			if( DEV.A > 15 ){ DEV.Error = 1; break; }
			DEV.D[DEV.A] = MQTT.Client_ID[DEV.E];
			DEV.A ++;
		}else{ DEV.C = 1; continue;}
	}
	if( DEV.C == 1 ){
		if( DEV.B > 63 ){ DEV.Error = 1; break; }
		DEV.Description[DEV.B] = MQTT.Client_ID[DEV.E];
		DEV.B ++;
	}
}
DEV.D[DEV.A] = 0;
if( DEV.A != 0 )DEV.ID = atol(DEV.D);
DEV.Description[DEV.B] = 0;
DEV.Description_len = DEV.B;



if(DEV.Error == 0){
	DEB_DEV("... DE_SOC(%d) DEV.ID : %ld\n\r",TCPSoc.Sock,DEV.ID);
	DEB_DEV("... DE_SOC(%d) DEV.Description : %s\n\r",TCPSoc.Sock,DEV.Description);
} else DEB_DEV("DEV.Error !!!\n\r");




if(DEV.Error == 0){
	DEV.SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEV.ID);
	if(DEV.SLOT_INDEX == -1){
		DEV.Error = 1;
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__SLOT_INDEX_By_DEVICE_ID : Error\n\r",TCPSoc.Sock);
	}else{
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__SLOT_INDEX_By_DEVICE_ID : OK\n\r",TCPSoc.Sock);
	}
}
if(DEV.Error == 0){
	if(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(DEV.SLOT_INDEX) != TYPE_DE){
		DEV.Error = 1;
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX : Error\n\r",TCPSoc.Sock);
	}else{
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX : OK\n\r",TCPSoc.Sock);
	}
}
if(DEV.Error == 0){
	if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX) == IS_RUN){
		DEV.Error = 1;
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX : Error\n\r",TCPSoc.Sock);
	}else{
		DEB_DEV("... DE_SOC(%d) SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX : OK\n\r",TCPSoc.Sock);
	}
}
if(DEV.Error == 0){
	SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX,IS_RUN);
	DEV.START = 1;
	DEB_DEV("... DE_SOC(%d) START : OK\n\r",TCPSoc.Sock);
}
if(DEV.Error == 0){
	if(DEV.Description_len!=0){

		//#---IOT STUDIO---------------------------------------------
			sprintf(MQTT_OutData,"{\"C\":\"5\",\"D\":\"%ld\",\"V\":\"1\"}",DEV.ID);
			DEB_DEV("... DE_SOC(%d) %s\n\r",TCPSoc.Sock,MQTT_OutData);
		//#------------------------------------------------
			SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(DEV.SLOT_INDEX,MQTT_OutData);
			pthread_mutex_lock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
			pthread_cond_broadcast( &SLOT[DEV.SLOT_INDEX].Device_condition );
			pthread_mutex_unlock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
		//#------------------------------------------------
			usleep(2000);

		//#---IOT STUDIO---------------------------------------------
			sprintf(MQTT_OutData, "{\"C\":\"4\",\"D\":\"%ld\",\"V\":\"%s\"}",DEV.ID,DEV.Description );
			DEB_DEV("... DE_SOC(%d) %s\n\r",TCPSoc.Sock,MQTT_OutData);
		//#------------------------------------------------
			SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(DEV.SLOT_INDEX,MQTT_OutData);
			pthread_mutex_lock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
			pthread_cond_broadcast( &SLOT[DEV.SLOT_INDEX].Device_condition );
			pthread_mutex_unlock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
		//#------------------------------------------------
			SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.Description);
		//#------------------------------------------------
	}
}


if(DEV.Error != 0){
	TA_STATUS=255;
}






