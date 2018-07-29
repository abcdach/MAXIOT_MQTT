
int MySQL_READ_DEVICE(){
	long STATUS = 0;
	long SLOT_INDEX;
	long MySQL_ERROR = 0;
	//long i = 0;
	//long Temp = 0;
	MySQL_Device_Cou    = 0;
	///////////////////////////////


	//###############################################################################
	//##
	//##		SQL : READ device OBJECTS
	//##
	//###############################################################################
	long DEVICE_i;
	char DEVICE_DESCRIPTION[DEVICE_DESCRIPTION_LEN];
	long DEVICE_ID;
	long DEVICE_TYPE;
	long DEVICE_X;
	long DEVICE_Y;
	long DEVICE_ROOM;
	char DEVICE_DATA[DEVICE_DATA_LEN];

	if (STATUS==0){
		sprintf(MySQL.QUERY,"SELECT * FROM `DEVICE`;");
		////////////////////////////////////////////////////////////////////
		if (mysql_query(MySQL.CONN, MySQL.QUERY)){
			fprintf(stderr,"%s\n",mysql_error(MySQL.CONN));
			STATUS = -1;
		} else {
			MySQL.RES = mysql_use_result(MySQL.CONN);
			while ((MySQL.ROW = mysql_fetch_row(MySQL.RES)) != NULL){
				//#------------------------------------------------
					MySQL_Device_Cou ++;
				//#------------------------------------------------
					DEVICE_i				 = atol(MySQL.ROW[0]);
					DEVICE_ID			     = atol(MySQL.ROW[1]);
					sprintf(DEVICE_DESCRIPTION,"%s",MySQL.ROW[2]);
					DEVICE_TYPE			     = atol(MySQL.ROW[3]);
					DEVICE_X 			     = atol(MySQL.ROW[4]);
					DEVICE_Y 			     = atol(MySQL.ROW[5]);
					sprintf(DEVICE_DATA,"%s",       MySQL.ROW[6]);
					DEVICE_ROOM 		     = atol(MySQL.ROW[7]);
				//##################################################
					if(DEVICE_ID < 100){
						Print_MySQL("MySQL_ERROR : DEVICE(%ld) : DEVICE_ID < 100\n\r",DEVICE_ID);
						MySQL_ERROR = 1;break;
					}
					if(DEVICE_ID > 99999){
						Print_MySQL("MySQL_ERROR : DEVICE(%ld) : DEVICE_ID > 99999\n\r",DEVICE_ID);
						MySQL_ERROR = 1;break;
					}
				//##################################################

				//##################################################
					SYS_API__ADD__DEVICE_By_DEVICE_ID(DEVICE_ID);
					SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(DEVICE_ID);
					if(SLOT_INDEX != -1){
						SYS_API__CLEANING__DEVICE_By_SLOT_INDEX(SLOT_INDEX);
						SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX(SLOT_INDEX);
						SYS_API__PUT__DEVICE_USER_INDEX_By_SLOT_INDEX(SLOT_INDEX, 1);
						SYS_API__PUT__DEVICE_TYPE_By_SLOT_INDEX(SLOT_INDEX,DEVICE_TYPE);
						SYS_API__PUT__DEVICE_X_By_SLOT_INDEX(SLOT_INDEX, DEVICE_X);
						SYS_API__PUT__DEVICE_Y_By_SLOT_INDEX(SLOT_INDEX, DEVICE_Y);
						SYS_API__PUT__DEVICE_DESCRIPTION_By_SLOT_INDEX(SLOT_INDEX, DEVICE_DESCRIPTION);
						SYS_API__PUT__DEVICE_DATA_By_SLOT_INDEX(SLOT_INDEX, DEVICE_DATA);
						SYS_API__PUT__DEVICE_DATA_STATUS_By_SLOT_INDEX(SLOT_INDEX,DATA_NEW);
						SYS_API__PUT__DEVICE_ROOM_By_SLOT_INDEX(SLOT_INDEX, (char)DEVICE_ROOM);
					}else{
						Momxede_Me=1; // !!!!!!!!!!!!! SAGANGEBO MARKERI
					}
			} mysql_free_result(MySQL.RES);
		}
	}


	switch(MySQL_ERROR) {
		case 0 :
			Print_MySQL("MySQL_STATU : DEVICE : OK : FOUND(%ld)\n\r",MySQL_Device_Cou);
			break;
		case 1 :
			Print_MySQL("MySQL_STATU : MySQL DELETE : DEVICE_ID(%ld)\n\r",DEVICE_ID);
			sprintf(MySQL.QUERY,"DELETE FROM `%s`.`DEVICE` WHERE `i` = '%ld' ;",MySQL_DATABASE,DEVICE_i);
			if (mysql_query(MySQL.CONN, MySQL.QUERY)){
				Print_MySQL("MySQL_ERROR : DEVICE : MySQL DELETE ERROR\n\r");
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


