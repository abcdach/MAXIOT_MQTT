


if( DEV.Error == 0 ){
	MQTT_OutData[0]  = isMQTT_Connect_Ack;
	MQTT_OutData[1]  = 0x02;
	MQTT_OutData[2]  = 0x00;
	MQTT_OutData[3]  = 0x00;
	MQTT.OutData_Len = 4;
	MQTT.TxStatus    = 1;

	DEB_DEV("... DE_SOC(%d) Message Type: *** Connect Ack \n\r",TCPSoc.Sock);
}


