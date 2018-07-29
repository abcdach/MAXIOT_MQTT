



int MySQL_DELETE_INTERCONN_OBJECTS(long DEVICE_1_ID, long OUTPUT_ID, long DEVICE_2_ID, long INPUT_ID){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : DELETE INTERCONN : %ld(%ld) - %ld(%ld) : "
				,DEVICE_1_ID, OUTPUT_ID, DEVICE_2_ID, INPUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"DELETE FROM `%s`.`INTERCONN` WHERE "
				"`INTERCONN`.`DEV_1_ID`=%ld and "
				"`INTERCONN`.`OUT_ID`=%ld and "
				"`INTERCONN`.`DEV_2_ID`=%ld and "
				"`INTERCONN`.`IN_ID`=%ld ;"
				,MySQL_DATABASE,DEVICE_1_ID, OUTPUT_ID, DEVICE_2_ID, INPUT_ID);
	//#-----------------------------------------------------------------------
		if (mysql_query(MySQL.CONN, MySQL.QUERY)){
			val =  mysql_errno(MySQL.CONN);
			Print_MySQL("ERROR\n\r");
			Print_MySQL("MySQL_ERROR : %d : %s\n\r",val,mysql_error(MySQL.CONN));
			MySQL_Close();
			return val;
		} else Print_MySQL("OK\n\r");
	//#-----------------------------------------------------------------------
		MySQL_Close();
		return 0;
	//#-----------------------------------------------------------------------
}



