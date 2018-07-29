


int MySQL_READ_INTERCONN_OBJECTS(){

	long SLOT_INDEX;
	long MySQL_ERROR = 0;
	long i = 0;
	long Temp = 0;

	long INTERCONN_ID;
	long INTERCONN_DEVICE_1_ID;
	long INTERCONN_DEVICE_2_ID;
	long INTERCONN_OUTPUT_INDEX;
	long INTERCONN_INPUT_INDEX;

	MySQL_Interconn_Cou = 0;

	sprintf(MySQL.QUERY,"SELECT * FROM `INTERCONN` ;");
	////////////////////////////////////////////////////////////////////
	if (mysql_query(MySQL.CONN, MySQL.QUERY)){
		Print_MySQL("MySQL_ERROR : INTERCONN : SELECT : %s\n",mysql_error(MySQL.CONN));
		MySQL_ERROR = 1;
	} else {
		MySQL.RES = mysql_use_result(MySQL.CONN);
		MySQL_Interconn_Cou = 0;
		while ((MySQL.ROW = mysql_fetch_row(MySQL.RES)) != NULL){
			//#------------------------------------------------
				INTERCONN_ID 		   = atol(MySQL.ROW[0]);
				INTERCONN_DEVICE_1_ID  = atol(MySQL.ROW[1]);
				INTERCONN_OUTPUT_INDEX = atol(MySQL.ROW[2]);
				INTERCONN_DEVICE_2_ID  = atol(MySQL.ROW[3]);
				INTERCONN_INPUT_INDEX  = atol(MySQL.ROW[4]);
			//##################################################
			//##################################################
				if((INTERCONN_OUTPUT_INDEX+1)>OUTPUT_LEN){
					Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld)(%ld) OUTPUT_ID > OUTPUT_LEN\n\r"
							,INTERCONN_ID,INTERCONN_DEVICE_1_ID,INTERCONN_OUTPUT_INDEX);
					MySQL_ERROR = 4;
					break;
				}
			//##################################################
				if((INTERCONN_INPUT_INDEX+1)>INPUT_LEN){
					Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld)(%ld) INPUT_ID > INPUT_LEN\n\r"
							,INTERCONN_ID,INTERCONN_DEVICE_2_ID,INTERCONN_INPUT_INDEX);
					MySQL_ERROR = 2;
					break;
				}
			//##################################################
				VALUE_1[MySQL_Interconn_Cou] = INTERCONN_DEVICE_1_ID;
				VALUE_2[MySQL_Interconn_Cou] = INTERCONN_OUTPUT_INDEX;
				VALUE_3[MySQL_Interconn_Cou] = INTERCONN_DEVICE_2_ID;
				VALUE_4[MySQL_Interconn_Cou] = INTERCONN_INPUT_INDEX;
				if (MySQL_Input_Cou != 0){
					//Print_MySQL("\n\r");
					for (i = 0; i < MySQL_Interconn_Cou; i++){
						//Print_MySQL("MySQL_STATU : INTERCONN : %ld : %ld(%ld)%ld(%ld) - %ld(%ld)%ld(%ld)\n\r"
								//,i,VALUE_1[i],VALUE_2[i],VALUE_3[i],VALUE_4[i]
								//,VALUE_1[MySQL_Interconn_Cou],VALUE_2[MySQL_Interconn_Cou]
								//,VALUE_3[MySQL_Interconn_Cou],VALUE_4[MySQL_Interconn_Cou]);
						if(VALUE_1[i]==VALUE_1[MySQL_Interconn_Cou] ){
							if(VALUE_2[i]==VALUE_2[MySQL_Interconn_Cou] ){
								if(VALUE_3[i]==VALUE_3[MySQL_Interconn_Cou] ){
									if(VALUE_4[i]==VALUE_4[MySQL_Interconn_Cou] ){
										Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : (%ld)(%ld) - (%ld)(%ld) FOUND DUPLICATE INTERCONN\n\r"
												,INTERCONN_ID,INTERCONN_DEVICE_1_ID,INTERCONN_OUTPUT_INDEX,INTERCONN_DEVICE_2_ID,INTERCONN_INPUT_INDEX);
										MySQL_ERROR = 2;break;
									}
								}
							}
						}
						if(VALUE_3[i]==VALUE_3[MySQL_Interconn_Cou] ){
							if(VALUE_4[i]==VALUE_4[MySQL_Interconn_Cou] ){
								Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : (%ld)(%ld) - (%ld)(%ld) FOUND DUPLICATE INPUT\n\r"
										,INTERCONN_ID,INTERCONN_DEVICE_1_ID,INTERCONN_OUTPUT_INDEX,INTERCONN_DEVICE_2_ID,INTERCONN_INPUT_INDEX);
								MySQL_ERROR = 2;break;
							}
						}
					}
				}if(MySQL_ERROR != 0)break;
			//##################################################
				SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(INTERCONN_DEVICE_2_ID);
				if(SLOT_INDEX != -1){
					Temp = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(INTERCONN_DEVICE_1_ID);
					if(Temp != -1){
						if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX,(unsigned char) INTERCONN_INPUT_INDEX)== ENABLE){
							if(SYS_API__GET__OUTPUT_STATUS_By_SLOT_INDEX(Temp, (unsigned char)INTERCONN_OUTPUT_INDEX)== ENABLE){
								SYS_API__PUT__LISTEN_DEVICE_ID_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) INTERCONN_INPUT_INDEX, INTERCONN_DEVICE_1_ID);
								SYS_API__PUT__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX, (unsigned char) INTERCONN_INPUT_INDEX, INTERCONN_OUTPUT_INDEX);
							} else {
								Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld)(%ld) OUTPUT NOT FOUND\n\r"
										,INTERCONN_ID,INTERCONN_DEVICE_1_ID,INTERCONN_OUTPUT_INDEX);
								MySQL_ERROR = 2;
								break;
							}
						} else {
							Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld)(%ld) INPUT NOT FOUND\n\r"
									,INTERCONN_ID,INTERCONN_DEVICE_2_ID,INTERCONN_INPUT_INDEX);
							MySQL_ERROR = 2;
							break;
						}
					} else {
						Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld) NOT FOUND\n\r"
								,INTERCONN_ID,INTERCONN_DEVICE_1_ID);
						MySQL_ERROR = 2;
						break;
					}
				} else {
					Print_MySQL("MySQL_ERROR : INTERCONN(%ld) : DEVICE_ID(%ld) NOT FOUND\n\r"
							,INTERCONN_ID,INTERCONN_DEVICE_2_ID);
					MySQL_ERROR = 2;
					break;
				}
				//##################################################
					MySQL_Interconn_Cou ++;
				//#------------------------------------------------
		}mysql_free_result(MySQL.RES);
	}


	switch(MySQL_ERROR) {
		case 0 :
			Print_MySQL("MySQL_STATU : INTERCONN : OK : FOUND(%ld)\n\r",MySQL_Output_Cou);
			break;
		case 1 :
			return -1;
			break;
		case 2 :// DEVICE_ID NOT FOUND
		case 3 :// FOUND DUPLICATE
		case 4 :// OUTPUT_INDEX > OUTPUT_LEN
		case 5 :// OUTPUT_DEVICE_ID < 100
		case 6 :// OUTPUT_DEVICE_ID > 99999
			Print_MySQL("MySQL_STATU : MySQL DELETE : INTERCONN(%ld) : (%ld)(%ld) - (%ld)(%ld)\n\r"
					,INTERCONN_ID,INTERCONN_DEVICE_1_ID,INTERCONN_OUTPUT_INDEX,INTERCONN_DEVICE_2_ID,INTERCONN_INPUT_INDEX);
			sprintf(MySQL.QUERY,"DELETE FROM `%s`.`INTERCONN` WHERE `i` = '%ld' ;",MySQL_DATABASE,INTERCONN_ID);
			if (mysql_query(MySQL.CONN, MySQL.QUERY)){
				Print_MySQL("MySQL_ERROR : INTERCONN : MySQL DELETE ERROR\n\r");
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
