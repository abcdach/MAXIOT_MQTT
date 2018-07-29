
int MySQL_DELETE_INPUT_OBJECTS(long DEVICE_ID, long INPUT_ID){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : DELETE INPUT : %ld(%ld) : ",DEVICE_ID, INPUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"DELETE FROM `%s`.`INPUT` WHERE "
				"`INPUT`.`DEV_ID` = %ld and "
				"`INPUT`.`ID` = %ld ;"
				,MySQL_DATABASE,DEVICE_ID, INPUT_ID);
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
