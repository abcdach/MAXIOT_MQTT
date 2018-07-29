
	//DEB_WE_Sent("--> WE_SOC(%d) %s\n\r",sock,WE_Client_Message);
	JSON_parse("N");
	if (JSON_STATUS == 1){
		N_Vel = (unsigned char)JSON_Long_Value;
		switch ((unsigned char)N_Vel){
			//#################################################################################
			case 0:
				DEB_WE_Sent("--> WE_SOC(%d) %s\n\r",sock,WE_Client_Message);
				if(START == 1){
//					//#------------------------------------------------
//						long TEST_SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_NAME);
//						if(TEST_SLOT_INDEX == -1){
//							TA_STATUS = 255; E_Vel = 14; break;//"Device deleted from system"
//						}
					//#------------------------------------------------
						JSON_parse("S");
						if (JSON_STATUS == 1){
							S_Vel = (unsigned char)JSON_Long_Value;
							if(S_Vel > 7) {TA_STATUS = 255; E_Vel = 11; break;}//"S Value > 7"
						} else {
							TA_STATUS = 255; E_Vel = 10; break;//"S - name not found in JSON Object"
						}
					//#------------------------------------------------
						JSON_s_parse("V");
						if (JSON_STATUS == 1){
							snprintf(V_Vel,V_Vel_LEN,"%s",JSON_Value);
						} else V_Vel[0]=0;
					//#------------------------------------------------
					//# SAVE LAST DATA
					//#------------------------------------------------
						SYS_API__PUT__LAST_OUTPUT_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)S_Vel, V_Vel);
					//#------------------------------------------------
					//# IOT STUDIOSTVIS SHETYOBINEBA
					//#------------------------------------------------
						snprintf(Server_message,Server_message_LEN, "{\"C\":\"0\",\"D\":\"%ld\",\"S\":\"%d\",\"V\":\"%s\"}"
								,(unsigned long)DEVICE_NAME,(unsigned char)S_Vel,V_Vel);
						DEB_WE_Sent("... WE_SOC(%d) %s\n\r",sock,Server_message);
					//#------------------------------------------------
						//SYS_API__PUT__MESSEGE((long)SLOT_INDEX,Server_message);
						SYS_API__PUT__THE_LAST_DATA_By_SLOT_INDEX((long)SLOT_INDEX,Server_message);
						pthread_mutex_lock( &SLOT[SLOT_INDEX].Device_cond_mutex );
						pthread_cond_broadcast( &SLOT[SLOT_INDEX].Device_condition );
						pthread_mutex_unlock( &SLOT[SLOT_INDEX].Device_cond_mutex );
					//#------------------------------------------------

				} else {
					TA_STATUS = 255; E_Vel  =  9; break;//"Handshake failed"
				}
				break;

			//#################################################################################
			case 1:
				DEB_WE_Sent("--> WE_SOC(%d) %s\n\r",sock,WE_Client_Message);
				JSON_parse("D");
				if (JSON_STATUS == 1){
					//############################################################################
					//##	Device registration
					//############################################################################
						DEVICE_NAME = (unsigned long)JSON_Long_Value;
						SLOT_INDEX  = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)DEVICE_NAME);
						if(SLOT_INDEX == -1){TA_STATUS = 255; E_Vel  =  3; break;}
						if(SYS_API__GET__DEVICE_TYPE_By_SLOT_INDEX((unsigned long)SLOT_INDEX) != TYPE_WE){
							TA_STATUS = 255; E_Vel  =  4; break;//"Device type is wrong"
						}
					//############################################################################
					//##	FINDE FREE SATELIT LOCKAL SLOT
					//############################################################################
						char Temp = 0;
						pthread_mutex_lock(&WE_DEVICE_mutex);
						for (i = 0; i < WE_DEVICE_NUMBER; i++){
							if(WE_DEVICE[i].WE_DEVICE__BUSY_STATUS == 0){
								Temp = 1; MY_WE_DEVICE = (unsigned long)i;
								WE_DEVICE[MY_WE_DEVICE].WE_DEVICE__BUSY_STATUS = 1;
								break;
							}
						}
						pthread_mutex_unlock(&WE_DEVICE_mutex);
						if(Temp==0){
							TA_STATUS = 255; E_Vel  =  15; break;//"ALL SATELIT ARE BUSY"
						} else {
							for (i = 0; i < 16; i++){
								WE_DEVICE[MY_WE_DEVICE].INPUT[i] = 0;
							}
						}
					//############################################################################
					//# WE_virtual_debugger
					//############################################################################
						//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,77,DEVICE_NAME,0);//debugger!!!
						//if(Temp_DB==1)printf("... WE_SOC(%d) -------------------(%d)START\n\r",sock,(int)DEVICE_NAME);
					//############################################################################
					//# ( create self liten task ....)
					//############################################################################
						WE_ARG.BUSY = 1;
						WE_ARG.SOCK = sock;
						WE_ARG.self = self;
						WE_ARG.MY_WE_DEVICE 		= (unsigned long)MY_WE_DEVICE;
						WE_ARG.IN_DEV__INPUT  		= (unsigned char)0;
						WE_ARG.IN_DEV__SLOT_INDEX   = (unsigned long)SLOT_INDEX;
						WE_ARG.IN_DEV__NAME 		= (unsigned long)DEVICE_NAME;
						WE_ARG.OUT_DEV__NAME 		= (unsigned long)DEVICE_NAME;
						WE_ARG.OUT_DEV__OUTPUT 		= 0;
					//#-----------------------------------------------------------------
						pthread_t _WE_pthread__GET_OUTPUT_DATA;
						if( pthread_create( &_WE_pthread__GET_OUTPUT_DATA , &ATTR_STACK_SIZE ,  WE_pthread__GET_OUTPUT_DATA , (void*) &WE_ARG) < 0){
							printf("... WE_SOC(%d) could not create thread\n\r",sock);
							TA_STATUS = 255;
						}
					//#-----------------------------------------------------------------
						while(WE_ARG.BUSY) usleep(1000);
					//############################################################################
					//# sand last OUTPUT data
					//############################################################################
						for (i = 0; i < INPUT_LEN; i++){
							if(SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i)>0){
								SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i,V_Vel);
								WE_Sent("{\"N\":\"3\",\"S\":\"%ld\",\"V\":\"%s\"}",(unsigned long)i,V_Vel);
								usleep(10000);
							}
						}
					//############################################################################
					//# sand last INPUT data
					//############################################################################
						for (i = 0; i < INPUT_LEN; i++){
							if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i) == ENABLE){
								unsigned long OUT_DEV_NAME   = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i);
								unsigned char OUT_DEV_OUTPUT = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX((unsigned long)SLOT_INDEX,(unsigned char)i);
								if(OUT_DEV_NAME != 0){
									long OUT_DEV_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID((unsigned long)OUT_DEV_NAME);
									if(OUT_DEV_INDEX != -1){
										if(SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX((unsigned long)OUT_DEV_INDEX,(unsigned char)OUT_DEV_OUTPUT)>0){
											SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX((unsigned long)OUT_DEV_INDEX,(unsigned char)OUT_DEV_OUTPUT,V_Vel);
											WE_Sent("{\"N\":\"4\",\"S\":\"%ld\",\"V\":\"%s\"}",(unsigned long)i,V_Vel);
											usleep(10000);
										}
									}
								}
							}
						}
					//############################################################################
					//# gadascem klient rom kavshiri dadasturebulia da mowyobiloba daregistrirebuli
					//############################################################################
						WE_Sent("{\"N\":\"2\",\"V\":\"%s\"}\n",SYS_API__GET__DEVICE_DESCRIPTION_By_SLOT_INDEX((unsigned long)SLOT_INDEX));
					//#-----------------------------------------------------------------------
						START = 1;
						//if(WE_virtual_debugger==1)SYS_INFO_WebSocket_Append((int)self,(int)parent_self,77,DEVICE_NAME,0);//debugger!!!
						//if(Temp_DB==1)printf("... WE_SOC(%d) -------------------(%d)START\n\r",sock,(int)DEVICE_NAME);

						My_EVENT_COUNTER__DELETE_INTERCONN__We = EVENT_COUNTER__DELETE_INTERCONN__We;
						DEB_WE_Sent("... WE_SOC(%d) REGISTERED DEVICE(%ld) WE_INDEX(%ld)\n\r"
								,sock
								,(unsigned long)DEVICE_NAME
								,(unsigned long)MY_WE_DEVICE);
					//#-----------------------------------------------------------------------
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
				//TA_STATUS = 255; E_Vel  =  0;
				break;
			case 6:
				break;
			case 7:// "PONG"
				break;
			case 8:// "PING"
				if(START == 1){WE_Sent("{\"N\":\"7\",\"i\":\"PONG\"}\n");}
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
	if(TA_STATUS == 255){
		switch ((unsigned char)E_Vel){
			case 0:break;
			case 1:snprintf(E_Vel_Text,E_Vel_Text_LEN, "N - name not found in JSON Object");break;
			case 2:snprintf(E_Vel_Text,E_Vel_Text_LEN, "D - name not found in JSON Object");break;
			case 3:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Device not found");break;
			case 4:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Device type is wrong");break;
			case 5:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Device is already in system");break;
			case 6:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Could not create thread");break;
			case 7:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Device was deleted from system");break;
			case 8:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Wrong device name");break;
			case 9:snprintf(E_Vel_Text,E_Vel_Text_LEN, "Handshake failed");break;
			case 10:snprintf(E_Vel_Text,E_Vel_Text_LEN,"S - name not found in JSON Object");break;
			case 11:snprintf(E_Vel_Text,E_Vel_Text_LEN,"S Value > 7");break;
			case 12:snprintf(E_Vel_Text,E_Vel_Text_LEN," ");break;
			case 13:snprintf(E_Vel_Text,E_Vel_Text_LEN," ");break;
			case 14:snprintf(E_Vel_Text,E_Vel_Text_LEN,"Device deleted from system");break;
			case 15:snprintf(E_Vel_Text,E_Vel_Text_LEN,"ALL SATELIT ARE BUSY");break;
			default:
				E_Vel = 0;
				snprintf(E_Vel_Text,E_Vel_Text_LEN," ");
				break;
		}
		WE_Sent("{\"N\":\"9\",\"E\":\"%d\",\"i\":\"Error(%s)\"}",(unsigned char)E_Vel,E_Vel_Text);
	}
//#------------------------------------------------

