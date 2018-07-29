    //###############################################################################
    //## WebSocket Client sent Handshake ...
    //###############################################################################
	STATUS = 0;
    ret = poll(&fd, 1, 10000);
    switch (ret) {// Get JSON from client
        case -1:// Error
        	printf("WebSo(%d)>> Get JSON from client Error !!!\n\r",sock);
        	STATUS = -1;
            break;
        case 0:// Timeout
        	printf("WebSo(%d)>> Get JSON from client Timeout !!!\n\r",sock);
        	STATUS = -2;
        	break;
        default:
        	read_size = recv(sock, client_message , 2000 , 0);
        	client_message[read_size]=0;
            STATUS = 0;
        	break;
    }
    //###############################################################################
    //## WebSocket Server response Handshake ...
    //###############################################################################
    if (STATUS==0){
		long  WebSocket_Key_Pos = dach_instr(client_message,0,read_size,"Sec-WebSocket-Key: ",0,19);
		if( WebSocket_Key_Pos < 65000){
			for ( i = 0; i < 24; i++ ){
				SHA1_InPut[i]=client_message[WebSocket_Key_Pos+i+19];
			}
			MySHA1_CALCULATOR();
			sprintf(Server_message, "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n",SHA1_OutPut);
			//printf("WebSo(%d)>> SENT:\n\r\n\r%s",sock,Server_message);
			write(sock , Server_message , strlen(Server_message));
			STATUS =  0;
		}else{
			STATUS = -1;
		}
    }
