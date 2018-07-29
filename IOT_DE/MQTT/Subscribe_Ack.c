



MQTT_OutData[0]  = isMQTT_Subscribe_Ack;
MQTT_OutData[1]  = 0x03;
MQTT_OutData[2]  = (unsigned char)( MQTT.Message_Identifier >> 8 );
MQTT_OutData[3]  = (unsigned char)( MQTT.Message_Identifier & 0x00FF );
MQTT_OutData[4]  = MQTT.QoS;
MQTT.OutData_Len = 5;
MQTT.TxStatus    = 1;

DEB_DEV("... DE_SOC(%d) Message Type: *** Subscribe Ack \n\r",TCPSoc.Sock);



