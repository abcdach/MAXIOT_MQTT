

int MySQL_CREATE_OUTPUT_OBJECTS(long DEVICE_ID, long OUTPUT_ID){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : CREATE OUTPUT : %ld(%ld) : ",DEVICE_ID, OUTPUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"INSERT INTO `%s`.`OUTPUT` "
				"(`i`, `DEV_ID`, `ID`, `DESCRIPTION`, `DATA`) "
				"VALUES "
				"(NULL, '%ld', '%ld', 'undefined', '');"
				,MySQL_DATABASE,DEVICE_ID, OUTPUT_ID);
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
