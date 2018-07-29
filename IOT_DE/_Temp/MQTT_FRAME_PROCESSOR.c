

for( ii = 0; ii < TCPSoc.FRAME_LEN; ii++ ){


	Data = TCPSoc.FRAME[ii];

	//printf("0x%02X\n",Data);


	if ( MQTT_Message_Type == 0 ){
		MQTT_Message_Type = Data; MQTT_STEP = 0; MQTT_Message_Status = 0;


		if(MQTT_Message_Type == isMQTT_Connect_Command)printf("... DE_SOC(%d) Message_Type *** isMQTT_Connect_Command ***\n\r",TCPSoc.Sock);
		if(MQTT_Message_Type == isMQTT_Publish_Message)printf("... DE_SOC(%d) Message_Type *** isMQTT_Publish_Message ***\n\r",TCPSoc.Sock);
		if(MQTT_Message_Type == isMQTT_Disconnect_Req) printf("... DE_SOC(%d) Message_Type *** isMQTT_Disconnect_Req ***\n\r",TCPSoc.Sock);

	}



	switch (MQTT_Message_Type){

		case isMQTT_Connect_Command:
			#include "MQTT/Connect_Command.c"
			if(MQTT_Message_Status==1){ MQTT_Message_Status = 0;
				#include "MQTT/Device_registration.c"
			}
			break;

		case isMQTT_Publish_Message:
			#include "MQTT/Publish_Message.c"
			if(MQTT_Publish_Message_Status==1){ MQTT_Publish_Message_Status = 0;
				#include "MQTT/Message_Processing.c"
			}
			break;

		case isMQTT_Ping_Request:
			#include "MQTT/Ping_Response.c"
			break;

		case isMQTT_Disconnect_Req:
			TA_STATUS=255;
			break;

		default:
			break;
	}

}











