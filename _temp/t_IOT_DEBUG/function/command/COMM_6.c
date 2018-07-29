
/**
//#------------------------------------------------------------------------
	JSON_parse("INDEX");
//#------------------------------------------------------------------------
	if (JSON_STATUS == 1){

			if(JSON_Long_Value==0) SYS_INFO_WebSocket_Reset();

			sprintf(data,"{\"COMM\":\"6\",\"INDEX\":\"%ld\",\"d0\":\"%ld\"}"
					,JSON_Long_Value, SYS_INFO_WebSocket_Read());
			WebSock_Sent(data);
			break;
	}

//#------------------------------------------------------------------------
**/

//#------------------------------------------------------------------------
	JSON_parse("INDEX");
//#------------------------------------------------------------------------
	if (JSON_STATUS == 1){
			////////////////////////////////////////////////////////////////////////////
			if(JSON_Long_Value==0) SYS_INFO_WebSocket_Reset();
			long temp = 1000;// whilidan gamosvis dazgveva
			long SNAPSHOT[1000][5];
			long SNAPSHOT_COU = 0;
			SYS_INFO_lock();
			while(temp){
				temp --;
				long x_data = SYS_INFO_WebSocket_Read_Data();
				if(x_data != -1){
					SNAPSHOT[SNAPSHOT_COU][0] = x_data;
					SNAPSHOT[SNAPSHOT_COU][1] = (long)SYS_INFO_WebSocket_Read_D0();
					SNAPSHOT[SNAPSHOT_COU][2] = (long)SYS_INFO_WebSocket_Read_D1();
					SNAPSHOT[SNAPSHOT_COU][3] = (long)SYS_INFO_WebSocket_Read_D2();
					SNAPSHOT[SNAPSHOT_COU][4] = (long)SYS_INFO_WebSocket_Read_D3();
					SNAPSHOT_COU++;
					SYS_INFO_WebSocket_Read_Next();
				} else {
					break;
				}
			}
			SYS_INFO_unlock();
			////////////////////////////////////////////////////////////////////////////
			for (i = 0; i < SNAPSHOT_COU; i++){
				sprintf(data,"{\"COMM\":\"6\",\"INDEX\":\"1\",\"d0\":\"%ld\",\"d1\":\"%ld\",\"d2\":\"%ld\",\"d3\":\"%ld\",\"d4\":\"%ld\"}"
					, SNAPSHOT[i][0]
					, SNAPSHOT[i][1]
					, SNAPSHOT[i][2]
					, SNAPSHOT[i][3]
					, SNAPSHOT[i][4]);

					WebSock_Sent(data);
					usleep(5000);
			}
			usleep(5000);
			sprintf(data,"{\"COMM\":\"6\",\"INDEX\":\"222\",\"d0\":\"-1\",\"d1\":\"-1\",\"d2\":\"-1\",\"d3\":\"-1\",\"d4\":\"-1\"}");
			WebSock_Sent(data);
			////////////////////////////////////////////////////////////////////////////
			break;
	}

//#------------------------------------------------------------------------
























