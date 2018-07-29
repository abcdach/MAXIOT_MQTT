





if (TCPSoc.Protocol == 0) {
	if(TCPSoc.FRAME_LEN > 0){
		if( TCPSoc.RxFRAME[0] == '{' ){ printf("... DE_SOC(%d) is JSON_Protocol\n\r",TCPSoc.Sock);
			TCPSoc.Protocol = 1;
			TCPSoc.TimeOut_MAX = 10;
			PJSON_Enable = 1;
		}
		else if (TCPSoc.RxFRAME[0] == 0x10 ){ printf("... DE_SOC(%d) is MQTT_Protocol\n\r",TCPSoc.Sock);
			TCPSoc.Protocol = 1;
			TCPSoc.TimeOut_MAX = 60;
			MQTT.STEP = 0;
			MQTT.Enable = 1;
		}
		else{ printf("... DE_SOC(%d) is UNKNOWN_Protocol\n\r",TCPSoc.Sock);TA_STATUS = 255; break; }
	}
}





