	DEB_DE_Sent("--> DE_SOC(%d) %s\n\r",TCPSoc.Sock,JSON_FRAME);
	JSON_parse("N");
	if (JSON_STATUS == 1){
		N_Vel = (char)JSON_Long_Value;
		switch (N_Vel){
			//0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_
			case 0:
				if(START == 1){
					//#------------------------------------------------
						long TEST_SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);
						if(TEST_SLOT_INDEX == -1){
							TA_STATUS = 255; E_Vel = 14; break;//"Device deleted from system"
						}
					//#------------------------------------------------
						JSON_parse("S");
						if (JSON_STATUS == 1){
							S_Vel = (char)JSON_Long_Value;
							if(S_Vel > 7) {TA_STATUS = 255; E_Vel = 11; break;}//"S Value > 7"
						} else {
							TA_STATUS = 255; E_Vel = 10; break;//"S - name not found in JSON Object"
						}
					//#------------------------------------------------
						JSON_s_parse("V");
						if (JSON_STATUS == 1){
							sprintf(V_Vel,"%s",JSON_Value);
						} else V_Vel[0]=0;
					//#------------------------------------------------
					//# SAVE LAST DATA
					//#------------------------------------------------
						SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)S_Vel, V_Vel);
					//#------------------------------------------------
					//# IOT STUDIOSTVIS SHETYOBINEBA
					//#------------------------------------------------
						sprintf(Sensor_message, "{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"%d\",\"V\":\"%s\"}",DEVICE_NAME,S_Vel,V_Vel);
						DEB_DE_Sent("k.. DE_SOC(%d) %s\n\r",TCPSoc.Sock,Sensor_message);
					//#------------------------------------------------
						//SYS_API__PUT__MESSEGE(SLOT_INDEX,Sensor_message);
						SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,Sensor_message);
						pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
						pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
						pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
					//#------------------------------------------------
				} else {
					TA_STATUS = 255; E_Vel  =  9; break;//"Handshake failed"
				}
				break;

			//1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_
			case 1:
				JSON_parse("D");
				if (JSON_STATUS == 1){
					//####################################################################################
					//# “Device registration”
					//####################################################################################
						DEVICE_NAME = JSON_Long_Value;
						SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_NAME);
						if(SLOT_INDEX == -1){TA_STATUS = 255; E_Vel  =  3; break;}
						if(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX) != TYPE_DE){
							TA_STATUS = 255; E_Vel  =  4; break;//"Device type is wrong"
						}
						if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX) == IS_RUN){
							TA_STATUS = 255; E_Vel  =  5; break;//"Device is already in system"
						}
						//DEB_DE_Sent("... DE_SOC(%d) DEVICE(%ld) REGISTERED IN IOT SERVER\n\r",TCPSoc.Sock,DEVICE_NAME);
					//#-----------------------------------------------------------------
						SYS_API__PUT__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX,IS_RUN);
					//#-----------------------------------------------------------------
						//if(DE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,55,DEVICE_NAME,0);//debugger!!!
					//####################################################################################
					//# “Device Description”
					//####################################################################################
						JSON_s_parse("V");
						if (JSON_STATUS == 1){
							//#------------------------------------------------
								sprintf(Sensor_message, "{\"C\":\"4\",\"D\":\"%ld\",\"V\":\"%s\"}",DEVICE_NAME,JSON_Value );
								DEB_DE_Sent("... DE_SOC(%d) %s\n\r",TCPSoc.Sock,Sensor_message);
							//#------------------------------------------------
								//SYS_API__PUT__MESSEGE(SLOT_INDEX,Sensor_message);
								SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX(SLOT_INDEX,Sensor_message);
								pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
								pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
								pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
							//#------------------------------------------------
								SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX, JSON_Value);
							//#------------------------------------------------
						}

						//############################################################################
						//# sand last OUTPUT data
						//############################################################################
//							for (i = 0; i < INPUT_LEN; i++){
//								if(SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)i)>0){
//									SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)i,V_Vel);
//
//									sprintf(Server_message, "{\"N\":\"3\",\"S\":\"%ld\",\"V\":\"%s\"}",i,V_Vel);
//									if(DEB_WE==1)printf("<-- WE_SOC(%d) %s\n\r",TCPSoc.Sock,Server_message);
//									WebSock_Sent(Server_message);
//									usleep(10000);
//								}
//							}
					//############################################################################
					//# sand last INPUT data
					//############################################################################
						for (i = 0; i < INPUT_LEN; i++){
							if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, i) == ENABLE){
								long OUT_DEV_NAME   = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)i);
								char OUT_DEV_OUTPUT = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)i);
								if(OUT_DEV_NAME != 0){
									long OUT_DEV_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUT_DEV_NAME);
									if(OUT_DEV_INDEX != -1){
										if(SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX(OUT_DEV_INDEX,(unsigned char)OUT_DEV_OUTPUT)>0){
											SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX(OUT_DEV_INDEX,(unsigned char)OUT_DEV_OUTPUT,V_Vel);
											DE_Sent("{\"N\":\"4\",\"S\":\"%ld\",\"V\":\"%s\"}",i,V_Vel);
											usleep(10000);
										}

									}
								}
							}
						}
					//####################################################################################
					//# “xxxxxDevice Description”
					//####################################################################################
						DE_Sent("{\"N\":\"2\",\"i\":\"Device registered\"}\n");
						START = 1;
				} else {
					TA_STATUS = 255; E_Vel  =  2;//"D - name not found in JSON Object"
				}
				break;

			case 2: // SERVER >> CLIENT (Registered)
				break;
			case 3: // SERVER >> CLIENT (Lasd data on client output)
				break;
			case 4: // SERVER >> CLIENT (Lasd data on client input)
				break;
			case 5: // SERVER <> CLIENT (Goodbye)
				TA_STATUS = 255; E_Vel  =  0;
				break;
			case 6:
				break;
			case 7:// "PONG"
				break;
			case 8:// "PING"
				if(START == 1){DE_Sent("{\"N\":\"7\",\"i\":\"PONG\"}\n");}
				break;
			case 9:
				break;
			default:
				break;
		}
	} else {
		TA_STATUS = 255; E_Vel  =  1;
	}
//#------------------------------------------------
	if((unsigned char)TA_STATUS == 255){
		switch (E_Vel){
			case 0:break;
			case 1:sprintf(E_Vel_Text, "N - name not found in JSON Object");break;
			case 2:sprintf(E_Vel_Text, "D - name not found in JSON Object");break;
			case 3:sprintf(E_Vel_Text, "Device not found");break;
			case 4:sprintf(E_Vel_Text, "Device type is wrong");break;
			case 5:sprintf(E_Vel_Text, "Device is already in system");break;
			case 6:sprintf(E_Vel_Text, "Could not create thread");break;
			case 7:sprintf(E_Vel_Text, "Device was deleted from system");break;
			case 8:sprintf(E_Vel_Text, "Wrong device name");break;
			case 9:sprintf(E_Vel_Text, "Handshake failed");break;
			case 10:sprintf(E_Vel_Text,"S - name not found in JSON Object");break;
			case 11:sprintf(E_Vel_Text,"S Value > 7");break;
			case 12:sprintf(E_Vel_Text," ");break;
			case 13:sprintf(E_Vel_Text," ");break;
			case 14:sprintf(E_Vel_Text,"Device deleted from system");break;
			default:
				E_Vel = 0;
				sprintf(E_Vel_Text, " ");
				break;
		}
		DE_Sent("{\"N\":\"9\",\"E\":\"%d\",\"i\":\"Error(%s)\"}"
				,E_Vel,E_Vel_Text );
	}
//#------------------------------------------------



