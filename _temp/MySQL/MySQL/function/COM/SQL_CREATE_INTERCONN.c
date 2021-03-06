



int MySQL_CREATE_INTERCONN_OBJECTS(long DEVICE_1_ID, long OUTPUT_ID, long DEVICE_2_ID, long INPUT_ID){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : CREATE INTERCONN : %ld(%ld) - %ld(%ld) : "
				,DEVICE_1_ID, OUTPUT_ID, DEVICE_2_ID, INPUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"INSERT INTO `%s`.`INTERCONN` "
				"(`i`,`DEV_1_ID`,`OUT_ID`,`DEV_2_ID`,`IN_ID`) "
				"VALUES "
				"(NULL,'%ld','%ld','%ld','%ld');"
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

