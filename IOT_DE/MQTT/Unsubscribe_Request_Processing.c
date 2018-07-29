
DEV.A = 0;
DEV.B = 0;
DEV.C = 0;
DEV.E = 0;
DEV.Error  = 0;
DEV.D[0]   = 0;
DEV.Description[0]  = 0;
DEV.Description_len = 0;
DEV.InID = 0;


for( DEV.E = 0; DEV.E < MQTT.Topic_Length; DEV.E++ ){
	if( DEV.C == 0 ){
		if( isdigit(MQTT.Topic[DEV.E]) != 0){
			if( DEV.A > 15 ){ DEV.Error = 1; break; }
			DEV.D[DEV.A] = MQTT.Topic[DEV.E];
			DEV.A ++;
		}else{ DEV.C = 1; continue;}
	}
	if( DEV.C == 1 ){
		if( DEV.B > 63 ){ DEV.Error = 1; break; }
		DEV.Description[DEV.B] = MQTT.Topic[DEV.E];
		DEV.B ++;
	}
}
DEV.D[DEV.A] = 0;
if( DEV.A != 0 )DEV.InID = atol(DEV.D);
DEV.Description[DEV.B] = 0;
DEV.Description_len = DEV.B;



//if(DEV.Error == 0){
	DEB_DEV("... DE_SOC(%d) DEV.InID : %ld\n\r",TCPSoc.Sock,DEV.InID);
	DEB_DEV("... DE_SOC(%d) DEV.InDescription : %s\n\r",TCPSoc.Sock,DEV.Description);
//} else printf("DEV.Error !!!\n\r");

//#####################################################################
SYS_API__PUT__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(DEV.SLOT_INDEX, DEV.InID, IS_NOT_SUBSCRIBE);




