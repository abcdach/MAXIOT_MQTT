    //###############################################################################
    //## WebSocket Client sent Handshake ...
    //###############################################################################
	TA_STATUS = 0;
    ret = poll(&fd, 1, 10000);
    switch (ret) {// Get JSON from client
        case -1:// Error
        	printf("WebSo(%d)>> Get JSON from client Error !!!\n\r",sock);
        	TA_STATUS = 255;
            break;
        case 0:// Timeout
        	printf("WebSo(%d)>> Get JSON from client Timeout !!!\n\r",sock);
        	TA_STATUS = 255;
        	break;
        default:
        	read_size = recv(sock, client_message , 2000 , 0);
        	client_message[read_size]=0;
        	printf("----------------------\n\r%s\n\r",client_message);
            TA_STATUS = 0;
        	break;
    }
    //###############################################################################
    //## WebSocket Server response Handshake ...
    //###############################################################################
    if ((unsigned char)TA_STATUS==0){
    	unsigned short  WebSocket_Key_Pos = dach_instr(client_message,0,read_size,"Sec-WebSocket-Key: ",0,19);
    	printf("WebSocket_Key_Pos:%d\n\r",WebSocket_Key_Pos);
		if( WebSocket_Key_Pos < 65000){
			for ( i = 0; i < 24; i++ ){
				SHA1_InPut[i]=client_message[WebSocket_Key_Pos+i+19];
			}
			MySHA1_CALCULATOR();


			unsigned short  WebSocket_Protocol_Pos = dach_instr(client_message,0,read_size,"Sec-WebSocket-Protocol: mqttv3.1",0,32);
			printf("WebSocket_Protocol_Pos:%d\n\r",WebSocket_Protocol_Pos);
			if( WebSocket_Protocol_Pos < 65000){
				sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\nSec-WebSocket-Protocol: mqttv3.1\r\n\r\n",SHA1_OutPut);
			} else {
				sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n",SHA1_OutPut);
			}


			//sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n",SHA1_OutPut);
			//sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nupgrade: websocket\r\nconnection: upgrade\r\nsec-websocket-accept: %s\r\nsec-websocket-protocol: mqttv3.1\r\n\r\n",SHA1_OutPut);

			//sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\nSec-WebSocket-Protocol: mqttv3.1\r\n\r\n",SHA1_OutPut);

			printf("----------------------\n\r%s\n\r",Server_message);
			write(sock , Server_message , strlen(Server_message));
			TA_STATUS = 0;
		}else{
			TA_STATUS = 255;
		}
    }


    //HTTP/1.1 101 Switching Protocols\r\nupgrade: websocket\r\nconnection: upgrade\r\nsec-websocket-accept: rBWFW9cuoZBIH8/T6B8yFSFCQlk=\r\n
	//sec-websocket-protocol: mqttv3.1\r\n









