

int MySQL_CREATE_DEVICE_OBJECTS(long DEVICE_ID, char *DEVICE_DESCRIPTION, long DEVICE_TYPE, char *DEVICE_DATA, long DEVICE_ROOM){


	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : CREATE DEVICE : %ld : ",DEVICE_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"INSERT INTO `%s`.`DEVICE` "
				"(`i`,`ID`,`DESCRIPTION`,`TYPE`,`X`,`Y`,`DATA`,`ROOM`) "
				"VALUES "
				"(NULL,'%ld','%s','%ld','50','100','%s','%ld');"
				, MySQL_DATABASE
				, DEVICE_ID
				, DEVICE_DESCRIPTION
				, DEVICE_TYPE
				, DEVICE_DATA
				, DEVICE_ROOM);
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
