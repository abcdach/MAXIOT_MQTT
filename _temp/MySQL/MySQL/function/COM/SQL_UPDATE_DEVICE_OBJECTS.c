
int MySQL_UPDATE_DEVICE_OBJECTS(long DEVICE_ID, long DEVICE_X, long DEVICE_Y, char *DEVICE_DESCRIPTION){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : UPDATE_DEVICE_OBJECTS : %ld : ",DEVICE_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"UPDATE `%s`.`DEVICE` SET `DESCRIPTION`='%s',`X`='%ld',`Y`='%ld' WHERE `DEVICE`.`ID` = %ld;"
				,MySQL_DATABASE,DEVICE_DESCRIPTION ,DEVICE_X, DEVICE_Y, DEVICE_ID);
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
}
