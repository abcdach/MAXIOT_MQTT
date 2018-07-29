
int MySQL_PUT_IN_OR_OUT_OBJECT_DATA(char *IN_OR_OUT, long DEVICE_ID, long IN_OR_OUT_ID, char *DATA){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : PUT_IN_OR_OUT_OBJECT_DATA : %ld(%ld) : ",DEVICE_ID,IN_OR_OUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"UPDATE `%s`.`%s` SET `DATA` = '%s' WHERE `%s`.`DEV_ID` = '%ld' AND `%s`.`ID` = '%ld';"
							,MySQL_DATABASE ,IN_OR_OUT ,DATA ,IN_OR_OUT ,DEVICE_ID ,IN_OR_OUT ,IN_OR_OUT_ID);
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
