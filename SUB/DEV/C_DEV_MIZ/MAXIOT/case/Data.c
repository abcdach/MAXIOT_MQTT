


if(SYS_DEB==1)printf("--> SYS : %s\n\r",MAXIOT.Server_message);
JSON_parse("S");
if (JSON_STATUS == 1){
	char SLOT = JSON_Long_Value;
	char Buffer_1[300];

	JSON_s_parse("V");
	if (JSON_STATUS == 1){
		sprintf(Buffer_1, JSON_Value);
		switch(SLOT) {
			case 0:
				printf("-------------------------------------\n\r");
				printf("... SYS : IN0 : %s\n\r",Buffer_1);
				PAYLOAD_DATA2[0] = 3;//COMMAND
				PAYLOAD_DATA2[1] = 11;//DATA_LEN
				PAYLOAD_DATA2[2] = 1;//baratis wamkitxveli
				PAYLOAD_DATA2[3] = Buffer_1[0];
				PAYLOAD_DATA2[4] = Buffer_1[1];
				PAYLOAD_DATA2[5] = Buffer_1[2];
				PAYLOAD_DATA2[6] = Buffer_1[3];
				PAYLOAD_DATA2[7] = Buffer_1[4];
				PAYLOAD_DATA2[8] = Buffer_1[5];
				PAYLOAD_DATA2[9] = Buffer_1[6];
				PAYLOAD_DATA2[10]= Buffer_1[7];
				PAYLOAD_DATA2[11]= Buffer_1[8];
				PAYLOAD_DATA2[12]= Buffer_1[9];
				DATA_TO_PAYLOAD(0x01,PAYLOAD_DATA2);
				break;
			case 1: printf("... SYS : IN1 : %s\n\r",Buffer_1); break;
			case 2: printf("... SYS : IN2 : %s\n\r",Buffer_1); break;
			case 3: printf("... SYS : IN3 : %s\n\r",Buffer_1); break;
			case 4: printf("... SYS : IN4 : %s\n\r",Buffer_1); break;
			case 5: printf("... SYS : IN5 : %s\n\r",Buffer_1); break;
			case 6: printf("... SYS : IN6 : %s\n\r",Buffer_1); break;
			case 7: printf("... SYS : IN7 : %s\n\r",Buffer_1); break;
			default :
				break;
		}
	}
}


