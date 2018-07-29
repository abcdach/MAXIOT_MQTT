




switch (MQTT.STEP) {
		case 0: if(MQTT.Data==isMQTT_Connect_Command)MQTT.STEP++; break;
		//case 1: MQTT.Msg_Len = MQTT.Data; MQTT.STEP++; TCPSoc.TimeOut=0; break;
		case 1: MQTT.STEP++; TCPSoc.TimeOut=0; break;
		case 2: MQTT.Protocol_Name_Length = (unsigned short)MQTT.Data << 8; MQTT.STEP++; break;
		case 3: MQTT.Protocol_Name_Length += MQTT.Data; MQTT.FC = 0; MQTT.STEP++;
			DEB_DEV("... DE_SOC(%d) MQTT.Protocol_Name_Length: %d\n\r",TCPSoc.Sock,MQTT.Protocol_Name_Length);
			break;
		case 4:
			MQTT.Protocol_Name[MQTT.FC++] = MQTT.Data;
			if(MQTT.FC==MQTT.Protocol_Name_Length){
				MQTT.Protocol_Name[MQTT.Protocol_Name_Length]=0;
				DEB_DEV("... DE_SOC(%d) MQTT.Protocol_Name: %s\n\r",TCPSoc.Sock,MQTT.Protocol_Name);
				MQTT.STEP++;
			}
			break;
		case 5:
			MQTT.Version  = MQTT.Data;
			if(MQTT.Version ==0x04){
				DEB_DEV("... DE_SOC(%d) Version: MQTT v3.1.1 \n\r",TCPSoc.Sock);
			}MQTT.STEP++;
			break;
		case 6:
			MQTT.Connect_Flags = MQTT.Data;
			DEB_DEV("... DE_SOC(%d) MQTT.Connect_Flags: 0x%02X\n\r",TCPSoc.Sock,MQTT.Connect_Flags);
			MQTT.STEP++;
			break;
		case 7: MQTT.Keep_Alive = (unsigned short)MQTT.Data << 8; MQTT.STEP++; break;
		case 8: MQTT.Keep_Alive += MQTT.Data; MQTT.FC = 0; MQTT.STEP++;
			TCPSoc.TimeOut_MAX = MQTT.Keep_Alive;
			DEB_DEV("... DE_SOC(%d) MQTT.Keep_Alive: %d\n\r",TCPSoc.Sock,MQTT.Keep_Alive);
			break;
		case 9: MQTT.Client_ID_Length = (unsigned short)MQTT.Data << 8; MQTT.STEP++; break;
		case 10: MQTT.Client_ID_Length += MQTT.Data;
			DEB_DEV("... DE_SOC(%d) Client_ID_Length: %d\n\r",TCPSoc.Sock,MQTT.Client_ID_Length);
			if(MQTT.Client_ID_Length != 0){
				MQTT.FC = 0; MQTT.STEP++;
			}else {MQTT.STEP += 2; MQTT.Message_Type = 0; MQTT.Message_Status=1; TCPSoc.TimeOut=0;}
			break;
		case 11:
			MQTT.Client_ID[MQTT.FC++] = MQTT.Data;
			if(MQTT.FC==MQTT.Client_ID_Length){
				MQTT.Protocol_Name[MQTT.Protocol_Name_Length]=0;
				DEB_DEV("... DE_SOC(%d) Client_ID: %s\n\r",TCPSoc.Sock,MQTT.Client_ID);
				MQTT.STEP++; MQTT.Message_Type = 0; MQTT.Message_Status=1; TCPSoc.TimeOut=0;
			}
			break;
		case 12:
			break;
		default:
			break;
}

















