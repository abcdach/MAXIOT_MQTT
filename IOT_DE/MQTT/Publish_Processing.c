

if(DEV.START == 1){
		DEB_DEV("... DE_SOC(%d) ullaaaaa !!!!!!!! :))))) \n\r",TCPSoc.Sock);
		DEB_DEV("-----------------------------------------\n\r");
		DEB_DEV("... DE_SOC(%d) MQTT.Topic: %s\n\r",TCPSoc.Sock,MQTT.Topic);
		DEB_DEV("... DE_SOC(%d) MQTT.Message: %s\n\r",TCPSoc.Sock,MQTT.Message);
		DEB_DEV("... DE_SOC(%d) MQTT.Message_Length: %d\n\r",TCPSoc.Sock,MQTT.Message_Length);
		DEB_DEV("-----------------------------------------\n\r");


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
		if( DEV.A != 0 )DEV.InID = atol(DEV.D);
		DEV.Description[DEV.B] = 0;
		DEV.Description_len = DEV.B;
	//------------------------------------------------






		DEB_DEV("... DE_SOC(%d) DEV.InID : %ld\n\r",TCPSoc.Sock,DEV.InID);
		DEB_DEV("... DE_SOC(%d) DEV.InDescription : %s\n\r",TCPSoc.Sock,DEV.Description);
		DEB_DEV("-----------------------------------------\n\r");




	//-------------------------------------------------------------
		SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.InID, MQTT.Message);
	//-------------------------------------------------------------
	//--IOT STUDIO ------------------------------------------------
		sprintf(MQTT_OutData,"{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"%ld\",\"V\":\"%s\"}",DEV.ID ,DEV.InID ,MQTT.Message);
		SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(DEV.SLOT_INDEX,MQTT_OutData);
	//-------------------------------------------------------------
	//-------------------------------------------------------------
		pthread_mutex_lock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
		pthread_cond_broadcast( &SLOT[DEV.SLOT_INDEX].Device_condition );
		pthread_mutex_unlock( &SLOT[DEV.SLOT_INDEX].Device_cond_mutex );
	//-------------------------------------------------------------
}























