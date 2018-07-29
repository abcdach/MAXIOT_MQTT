


int MySQL_DELETE_DEVICE_OBJECTS( long DEVICE_ID ){
	//FOBJECTS__DELETE_DEVICE_OBJECT(DEVICE_ID);

	return 0;

	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : DELETE DEVICE : %ld : ",DEVICE_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"DELETE FROM `%s`.`DEVICE` WHERE "
				"`DEVICE`.`ID` = %ld ;",MySQL_DATABASE,DEVICE_ID);
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

