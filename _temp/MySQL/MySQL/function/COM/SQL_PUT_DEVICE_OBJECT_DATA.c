
int MySQL_PUT_DEVICE_OBJECT_DATA(long DEVICE_ID, char *DATA){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : PUT_DEVICE_OBJECT_DATA : %ld : ",DEVICE_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"UPDATE `%s`.`DEVICE` SET `DATA`='%s' WHERE `DEVICE`.`ID`=%ld;"
						,MySQL_DATABASE ,DATA ,DEVICE_ID);
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
