


MQTT.Message_Type = 0;
TCPSoc.TimeOut    = 0;
MQTT_OutData[0]   = 0xd0;
MQTT_OutData[1]   = 0x00;
MQTT.OutData_Len  = 2;
MQTT.TxStatus = 1;

DEB_DEV("... DE_SOC(%d) Message Type: *** Ping Response \n\r",TCPSoc.Sock);









