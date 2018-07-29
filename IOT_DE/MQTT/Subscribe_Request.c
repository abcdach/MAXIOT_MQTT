switch (MQTT.STEP) {
		case 0: if( MQTT.Data == isMQTT_Publish_Message ){MQTT.STEP++; TCPSoc.TimeOut = 0; break;}
		case 1:
			if((MQTT.Data & 0x80)==0){
				MQTT.Msg_Len = MQTT.Data;
				MQTT.STEP = 12;
			}else{
				MQTT.Msg_Len = (unsigned char)MQTT.Data - 128;
				MQTT.STEP++;
			}
			break;
		case 2:
			if( (MQTT.Data & 0x80) == 0 ){
				 MQTT.Msg_Len += (unsigned short)MQTT.Data*128;
				 MQTT.STEP = 12;
			}else{
				//eerrorr
			}
			break;

		case 12: MQTT.Message_Identifier = (unsigned short)MQTT.Data << 8; MQTT.STEP++; break;
		case 13: MQTT.Message_Identifier += MQTT.Data; MQTT.STEP++;
			DEB_DEV("... DE_SOC(%d) SUBSCRIBE : MQTT.Message_Identifier: %d\n\r",TCPSoc.Sock,MQTT.Message_Identifier);break;
		case 14: MQTT.Topic_Length = (unsigned short)MQTT.Data << 8; MQTT.STEP++; break;
		case 15: MQTT.Topic_Length += MQTT.Data; MQTT.FC = 0; MQTT.STEP++;
			DEB_DEV("... DE_SOC(%d) SUBSCRIBE : MQTT.Topic_Length: %d\n\r",TCPSoc.Sock,MQTT.Topic_Length);break;
		case 16:
			MQTT.Topic[MQTT.FC++] = MQTT.Data;
			if( MQTT.FC == MQTT.Topic_Length ){

				MQTT.Topic[MQTT.Topic_Length] = 0;
				DEB_DEV("... DE_SOC(%d) SUBSCRIBE : MQTT.Topic: %s\n\r",TCPSoc.Sock,MQTT.Topic);

				if( MQTT.Topic_Length != 0 ){ MQTT.FC = 0; MQTT.STEP++;}
				else { MQTT.STEP += 2; MQTT.Message_Type = 0; TCPSoc.TimeOut = 0;}
			}
			break;
		case 17:
			MQTT.QoS = MQTT.Data;
			DEB_DEV("... DE_SOC(%d) SUBSCRIBE : MQTT.QoS: %d\n\r",TCPSoc.Sock,MQTT.QoS);

			MQTT.Subscribe_Request_Status = 1;
			MQTT.Message_Type = 0;
			MQTT.STEP ++;
			TCPSoc.TimeOut = 0;
			break;
		case 18:
			break;
		default:
			break;
}
