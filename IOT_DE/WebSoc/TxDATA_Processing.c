

unsigned short DATA_Cou  = 0;
unsigned  char DATA[10];

if( WSoc.Binary_Format == 1 ) DATA[0] = 0x82;
else DATA[0] = 0x81;

if(MQTT.OutData_Len <= 125){
	DATA[1] = (unsigned char) MQTT.OutData_Len;
	DATA_Cou = 2;
}else if(MQTT.OutData_Len >= 126 && MQTT.OutData_Len <= 65535){
	DATA[1] =  126;
	DATA[2] = (unsigned char)(MQTT.OutData_Len >> 8);
	DATA[3] = (unsigned char)(MQTT.OutData_Len & 0x00FF);
	DATA_Cou = 4;
}else{
	return 0;
}
unsigned short i = 0;
unsigned short b = 0;
for( i = 0; i < DATA_Cou; i++ ){
	MQTT_InData[b] = DATA[i]; b++;
}
for( i = 0; i < MQTT.OutData_Len; i++ ){
	MQTT_InData[b] = MQTT_OutData[i]; b++;
}

unsigned short Len = DATA_Cou + MQTT.OutData_Len;

