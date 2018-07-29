
DEV.A = 0;
DEV.B = 0;
DEV.C = 0;
DEV.E = 0;
DEV.Error  = 0;
DEV.D[0]   = 0;
DEV.Description[0]  = 0;
DEV.Description_len = 0;
DEV.InID = 0;


for( DEV.E = 0; DEV.E < MQTT.Topic_Length; DEV.E++ ){
	if( DEV.C == 0 ){
		if( isdigit(MQTT.Topic[DEV.E]) != 0){
			if( DEV.A > 15 ){ DEV.Error = 1; break; }
			DEV.D[DEV.A] = MQTT.Topic[DEV.E];
			DEV.A ++;
		}else{ DEV.C = 1; continue;}
	}
	if( DEV.C == 1 ){
		if( DEV.B > 63 ){ DEV.Error = 1; break; }
		DEV.Description[DEV.B] = MQTT.Topic[DEV.E];
		DEV.B ++;
	}
}
DEV.D[DEV.A] = 0;
DEV.Description[DEV.B] = 0;
DEV.Description_len = DEV.B;
//if( DEV.A != 0 )DEV.InID = atol(DEV.D);




//#####################################################################
// tu slotis nomeri araa mititebuli
if( DEV.A == 0 ){
	DEB_DEV("... DE_SOC(%d) SUBSCRIBE : Error : input slot number is not defined !!!\n\r",TCPSoc.Sock);
	DEV.Error = 1;
} else {
	DEV.InID = atol(DEV.D);
}

// sloti nomeri didia
if( DEV.Error == 0 && DEV.InID > INPUT_LEN ){
	DEB_DEV("... DE_SOC(%d) SUBSCRIBE : Error : input slot number > %d !!!\n\r",TCPSoc.Sock,INPUT_LEN);
	DEV.Error = 1;
}

// sloti ukve misubsqraibebulia
if( DEV.Error == 0 && SYS_API__GET__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.InID) == IS_SUBSCRIBE){
	DEB_DEV("... DE_SOC(%d) SUBSCRIBE : Error : is already subscribed !!!\n\r",TCPSoc.Sock);
	DEV.Error = 1;
}
//#####################################################################
if( DEV.Error == 0 ){
	DEB_DEV("... DE_SOC(%d) SUBSCRIBE : INPUT : %ld\n\r",TCPSoc.Sock,DEV.InID);
	DEB_DEV("... DE_SOC(%d) SUBSCRIBE : Description : %s\n\r",TCPSoc.Sock,DEV.Description);

	SYS_API__PUT__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.InID, IS_SUBSCRIBE);

	//MQTT_PARG.self = self;
	MQTT_PARG.Sock    = TCPSoc.Sock;
	MQTT_PARG.DevID   = DEV.ID;
	MQTT_PARG.DevInID = DEV.InID;
	sprintf(MQTT_PARG.Topic,"%s",MQTT.Topic);
	MQTT_PARG.WSoc_Enable = WSoc.Enable;
	MQTT_PARG.WSoc_Binary_Format = WSoc.Binary_Format;

	pthread_t _MQTT_Publish_Message_Tread;
	if( pthread_create( &_MQTT_Publish_Message_Tread , &is_STACK_SIZE ,  MQTT_Publish_Message_Tread , (void*) &MQTT_PARG) < 0){
		TA_STATUS = 255;
	}else{
		DEB_DEV("... DE_SOC(%d) SUBSCRIBE : pthread_create : OK\n\r",TCPSoc.Sock);
	}
}DEV.Error = 0;






