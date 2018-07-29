
int MySQL_READ_OUTPUT_OBJECTS(){

	long SLOT_INDEX;
	long MySQL_ERROR = 0;
	long i = 0;
	long Temp = 0;

	long OUTPUT_INDEX;
	long OUTPUT_DEVICE_ID;
	char OUTPUT_DESCRIPTION[OUTPUT_DESCRIPTION_LEN];
	long OUTPUT_ID;

	MySQL_Output_Cou = 0;

	sprintf(MySQL.QUERY,"SELECT * FROM `OUTPUT` ;");
	////////////////////////////////////////////////////////////////////
	if (mysql_query(MySQL.CONN, MySQL.QUERY)){
		Print_MySQL("MySQL_ERROR : INTERCONN : SELECT : %s\n",mysql_error(MySQL.CONN));
		MySQL_ERROR = 1;
	} else {
		MySQL.RES = mysql_use_result(MySQL.CONN);
		while ((MySQL.ROW = mysql_fetch_row(MySQL.RES)) != NULL){
			//#------------------------------------------------
				OUTPUT_INDEX 	  = atol(MySQL.ROW[0]);
				OUTPUT_DEVICE_ID  = atol(MySQL.ROW[1]);
				OUTPUT_ID		  = atol(MySQL.ROW[2]);
			//##################################################
				if(OUTPUT_DEVICE_ID < 100){
					Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) OUTPUT_DEVICE_ID < 100\n\r",OUTPUT_DEVICE_ID,OUTPUT_ID);
					MySQL_ERROR = 5;
					break;
				}
				if(OUTPUT_DEVICE_ID > 99999){
					Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) OUTPUT_DEVICE_ID > 99999\n\r",OUTPUT_DEVICE_ID,OUTPUT_ID);
					MySQL_ERROR = 6;
					break;
				}
			//##################################################
				if((OUTPUT_ID+1)>OUTPUT_LEN){
					Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) OUTPUT_ID > OUTPUT_LEN\n\r",OUTPUT_DEVICE_ID,OUTPUT_ID);
					MySQL_ERROR = 4;
					break;
				}
			//##################################################
				Temp = strlen(MySQL.ROW[3]);
				if((Temp+1) > OUTPUT_DESCRIPTION_LEN){
					Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) OUTPUT_DESCRIPTION_LEN(%ld) >= %d \n\r"
							,OUTPUT_DEVICE_ID,OUTPUT_ID,Temp+1,OUTPUT_DESCRIPTION_LEN);
					sprintf(OUTPUT_DESCRIPTION,"undefined");
				}else{
					sprintf(OUTPUT_DESCRIPTION,"%s",MySQL.ROW[3]);
				}
			//##################################################
				VALUE_1[MySQL_Output_Cou] = OUTPUT_DEVICE_ID;
				VALUE_2[MySQL_Output_Cou] = OUTPUT_ID;
				if (MySQL_Output_Cou != 0){
					//Print_MySQL("\n\r");
					for (i = 0; i < MySQL_Output_Cou; i++){
						//Print_MySQL("MySQL_STATU : OUTPUT : %ld : %ld(%ld) - %ld(%ld)\n\r",i,VALUE_1[i],VALUE_2[i],VALUE_1[MySQL_Output_Cou],VALUE_2[MySQL_Output_Cou]);
						if(VALUE_1[i]==VALUE_1[MySQL_Output_Cou] ){
							if(VALUE_2[i]==VALUE_2[MySQL_Output_Cou] ){
								Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) FOUND DUPLICATE OUTPUT\n\r",OUTPUT_DEVICE_ID,OUTPUT_ID);
								MySQL_ERROR = 3;break;
							}
						}
					}
				}if(MySQL_ERROR != 0)break;
			//##################################################
				SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUTPUT_DEVICE_ID);
				if(SLOT_INDEX != -1){
					SYS_API__PUT__OUTPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)OUTPUT_ID, ENABLE );
					SYS_API__PUT__OUTPUT_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)OUTPUT_ID,OUTPUT_DESCRIPTION);
				} else {
					Print_MySQL("MySQL_ERROR : OUTPUT : DEVICE_ID(%ld)(%ld) NOT FOUND\n\r",OUTPUT_DEVICE_ID,OUTPUT_ID);
					MySQL_ERROR = 2;
					break;
				}
			//#------------------------------------------------
				MySQL_Output_Cou ++;
			//#------------------------------------------------
		}mysql_free_result(MySQL.RES);
	}


	switch(MySQL_ERROR) {
		case 0 :
			Print_MySQL("MySQL_STATU : OUTPUT : OK : FOUND(%ld)\n\r",MySQL_Output_Cou);
			break;
		case 1 :
			return -1;
			break;
		case 2 :// DEVICE_ID NOT FOUND
		case 3 :// FOUND DUPLICATE
		case 4 :// OUTPUT_ID > OUTPUT_LEN
		case 5 :// OUTPUT_DEVICE_ID < 100
		case 6 :// OUTPUT_DEVICE_ID > 99999
			Print_MySQL("MySQL_STATU : MySQL DELETE : OUTPUT(%ld) : DEVICE_ID(%ld)(%ld)\n\r",OUTPUT_INDEX,OUTPUT_DEVICE_ID,OUTPUT_ID);
			sprintf(MySQL.QUERY,"DELETE FROM `%s`.`OUTPUT` WHERE `i` = '%ld' ;",MySQL_DATABASE,OUTPUT_INDEX);
			if (mysql_query(MySQL.CONN, MySQL.QUERY)){
				Print_MySQL("MySQL_ERROR : OUTPUT : MySQL DELETE ERROR\n\r");
				return -1;
			} else {
				Print_MySQL("MySQL_STATU : MySQL DELETE : OK\n\r");
				return 1;
			}
			break;
		default :
			break;
	}
	return 0;
}

