


printf("--> SYS : %s\n\r",MAXIOT.Server_message);
JSON_parse("S");
if (JSON_STATUS == 1){
	char SLOT = JSON_Long_Value;
	char Buffer_1[300];

	JSON_s_parse("V");
	if (JSON_STATUS == 1){
		sprintf(Buffer_1,"%s", JSON_Value);
		switch(SLOT) {
			case 0: printf("... SYS : IN0 : %s\n\r",Buffer_1); break;
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


