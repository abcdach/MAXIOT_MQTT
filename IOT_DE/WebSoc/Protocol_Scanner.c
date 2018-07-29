







unsigned short  WebSocket_Key_Pos = dach_instr(TCPSoc.RxFRAME,0,TCPSoc.FRAME_LEN,"Sec-WebSocket-Key: ",0,19);
unsigned short  WebSocket_Protocol_Pos = dach_instr(TCPSoc.RxFRAME,0,TCPSoc.FRAME_LEN,"Sec-WebSocket-Protocol: mqttv3.1",0,32);

if( WebSocket_Key_Pos < 65000){

		for ( i = 0; i < 24; i++ ) SHA1_InPut[i] = TCPSoc.RxFRAME[WebSocket_Key_Pos+i+19];
		MySHA1_CALCULATOR();

		if( WebSocket_Protocol_Pos < 65000){
			sprintf(TCPSoc.TxFRAME, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\nSec-WebSocket-Protocol: mqttv3.1\r\n\r\n",SHA1_OutPut);
			WSoc.Binary_Format = 1;
		} else {
			sprintf(TCPSoc.TxFRAME, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n",SHA1_OutPut);
			WSoc.Binary_Format = 0;
		}
		write(TCPSoc.Sock , TCPSoc.TxFRAME , strlen(TCPSoc.TxFRAME));
		WSoc.Enable = 1;
		break;
}









