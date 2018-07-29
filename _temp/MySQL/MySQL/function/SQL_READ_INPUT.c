

int MySQL_READ_INPUT_OBJECTS(){

	long SLOT_INDEX;
	long MySQL_ERROR = 0;
	long i = 0;
	long Temp = 0;

	long INPUT_INDEX;
	long INPUT_DEVICE_ID;
	char INPUT_DESCRIPTION[INPUT_DESCRIPTION_LEN];
	long INPUT_ID;

	MySQL_Input_Cou = 0;

	sprintf(MySQL.QUERY,"SELECT * FROM `INPUT` ;");
	////////////////////////////////////////////////////////////////////
	if (mysql_query(MySQL.CONN, MySQL.QUERY)){
		Print_MySQL("MySQL_ERROR : INTERCONN : SELECT : %s\n",mysql_error(MySQL.CONN));
		MySQL_ERROR = 1;
	} else {
		MySQL.RES = mysql_use_result(MySQL.CONN);
		while ((MySQL.ROW = mysql_fetch_row(MySQL.RES)) != NULL){
			//#------------------------------------------------
				INPUT_INDEX 		= atol(MySQL.ROW[0]);
				INPUT_DEVICE_ID 	= atol(MySQL.ROW[1]);
				INPUT_ID			= atol(MySQL.ROW[2]);
			//##################################################
				if(INPUT_DEVICE_ID < 100){
					Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) INPUT_DEVICE_ID < 100\n\r",INPUT_DEVICE_ID,INPUT_ID);
					MySQL_ERROR = 5;
					break;
				}
				if(INPUT_DEVICE_ID > 99999){
					Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) INPUT_DEVICE_ID > 99999\n\r",INPUT_DEVICE_ID,INPUT_ID);
					MySQL_ERROR = 6;
					break;
				}
			//##################################################
				if((INPUT_ID+1)>INPUT_LEN){
					Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) INPUT_ID > INPUT_LEN\n\r",INPUT_DEVICE_ID,INPUT_ID);
					MySQL_ERROR = 4;
					break;
				}
			//##################################################
				Temp = strlen(MySQL.ROW[3]);
				if((Temp+1) > INPUT_DESCRIPTION_LEN){
					Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) INPUT_DESCRIPTION_LEN(%ld) >= %d \n\r"
							,INPUT_DEVICE_ID,INPUT_ID,Temp+1,INPUT_DESCRIPTION_LEN);
					sprintf(INPUT_DESCRIPTION,"undefined");
				}else{
					sprintf(INPUT_DESCRIPTION,"%s",MySQL.ROW[3]);
				}
			//##################################################
				VALUE_1[MySQL_Input_Cou] = INPUT_DEVICE_ID;
				VALUE_2[MySQL_Input_Cou] = INPUT_ID;
				if (MySQL_Input_Cou != 0){
					//Print_MySQL("\n\r");
					for (i = 0; i < MySQL_Input_Cou; i++){
						//Print_MySQL("MySQL_STATU : INPUT : %ld : %ld(%ld) - %ld(%ld)\n\r",i,VALUE_1[i],VALUE_2[i],VALUE_1[MySQL_Input_Cou],VALUE_2[MySQL_Input_Cou]);
						if(VALUE_1[i]==VALUE_1[MySQL_Input_Cou] ){
							if(VALUE_2[i]==VALUE_2[MySQL_Input_Cou] ){
								Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) FOUND DUPLICATE INPUT\n\r",INPUT_DEVICE_ID,INPUT_ID);
								MySQL_ERROR = 3;break;
							}
						}
					}
				}if(MySQL_ERROR != 0)break;
			//##################################################
				SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(INPUT_DEVICE_ID);
				if(SLOT_INDEX != -1){
					SYS_API__PUT__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, (unsigned char)INPUT_ID, ENABLE );
					SYS_API__PUT__INPUT_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX,(unsigned char)INPUT_ID,INPUT_DESCRIPTION);
				} else {
					Print_MySQL("MySQL_ERROR : INPUT : DEVICE_ID(%ld)(%ld) NOT FOUND\n\r",INPUT_DEVICE_ID,INPUT_ID);
					MySQL_ERROR = 2;
					break;
				}
			//#------------------------------------------------
				MySQL_Input_Cou ++;
			//#------------------------------------------------
		}mysql_free_result(MySQL.RES);
	}


	switch(MySQL_ERROR) {
		case 0 :
			Print_MySQL("MySQL_STATU : INPUT : OK : FOUND(%ld)\n\r",MySQL_Input_Cou);
			break;
		case 1 :
			return -1;
			break;
		case 2 :// DEVICE_ID NOT FOUND
		case 3 :// FOUND DUPLICATE
		case 4 :// INPUT_ID > INPUT_LEN
		case 5 :// INPUT_DEVICE_ID < 100
		case 6 :// INPUT_DEVICE_ID > 99999
			Print_MySQL("MySQL_STATU : MySQL DELETE : INPUT(%ld) : DEVICE_ID(%ld)(%ld)\n\r",INPUT_INDEX,INPUT_DEVICE_ID,INPUT_ID);
			sprintf(MySQL.QUERY,"DELETE FROM `%s`.`INPUT` WHERE `i` = '%ld' ;",MySQL_DATABASE,INPUT_INDEX);
			if (mysql_query(MySQL.CONN, MySQL.QUERY)){
				Print_MySQL("MySQL_ERROR : INPUT : MySQL DELETE ERROR\n\r");
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





