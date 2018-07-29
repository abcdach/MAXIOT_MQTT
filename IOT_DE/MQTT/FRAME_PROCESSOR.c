

for( MQTT.ii = 0; MQTT.ii < TCPSoc.FRAME_LEN; MQTT.ii++ ){


	MQTT.Data = MQTT_InData[MQTT.ii];

	//DEB_DEV("0x%02X\n",MQTT.Data);


	if ( MQTT.Message_Type == 0 ){
		MQTT.Message_Type = MQTT.Data; MQTT.STEP = 0; MQTT.Message_Status = 0;
		switch (MQTT.Message_Type){
			case isMQTT_Connect_Command:     DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Connect_Command\n\r",TCPSoc.Sock);break;
			case isMQTT_Publish_Message:     DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Publish_Message\n\r",TCPSoc.Sock);break;
			case isMQTT_Disconnect_Req:      DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Disconnect_Req\n\r",TCPSoc.Sock);break;
			case isMQTT_Subscribe_Request:   DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Subscribe_Request\n\r",TCPSoc.Sock);break;
			case isMQTT_Ping_Request:        DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Ping_Request\n\r",TCPSoc.Sock);break;
			case isMQTT_Unsubscribe_Request: DEB_DEV("... DE_SOC(%d) Message_Type: *** MQTT_Unsubscribe_Request\n\r",TCPSoc.Sock);break;
			default:
				DEB_DEV("... DE_SOC(%d) Message_Type: *** unknown 0x%02X\n\r",TCPSoc.Sock,MQTT.Message_Type);
				break;
		}
	}



	switch (MQTT.Message_Type){

		case isMQTT_Connect_Command:
			#include "Connect_Command.c"
			if(MQTT.Message_Status == 1){ MQTT.Message_Status = 0;
				#include "Connect_Processing.c"
				#include "Connect_Ack.c"
			}break;

		case isMQTT_Publish_Message:
			#include "Publish_Message.c"
			if(MQTT.Publish_Message_Status == 1){ MQTT.Publish_Message_Status = 0;
				#include "Publish_Processing.c"
			}break;

		case isMQTT_Ping_Request:
			#include "Ping_Request.c"
			if(MQTT.Ping_Request_Status == 1){ MQTT.Ping_Request_Status = 0;
				#include "Ping_Response.c"
			}break;

		case isMQTT_Subscribe_Request:
			#include "Subscribe_Request.c"
			if(MQTT.Subscribe_Request_Status == 1){ MQTT.Subscribe_Request_Status = 0;
				#include "Subscribe_Request_Processing.c"
				#include "Subscribe_Ack.c"
			}break;

		case isMQTT_Unsubscribe_Request:
			#include "Unsubscribe_Request.c"
			if(MQTT.Unsubscribe_Request_Status == 1){ MQTT.Unsubscribe_Request_Status = 0;
				#include "Unsubscribe_Request_Processing.c"
				#include "Unsubscribe_Ack.c"
			}break;

		case isMQTT_Disconnect_Req:
			TA_STATUS = 255;
			break;

		default:// unknown
			TA_STATUS = 255;
			break;
	}

}










