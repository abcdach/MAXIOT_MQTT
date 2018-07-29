switch (MQTT.STEP){
	case 0:
		MQTT.STEP++; break;
	case 1:
		MQTT.STEP++;
		MQTT.Message_Type = 0;
		MQTT.Ping_Request_Status = 1;
		TCPSoc.TimeOut = 0;
		break;
	default:
		break;
}

