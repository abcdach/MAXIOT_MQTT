
int MySQL_GET_IN_OR_OUT_OBJECT_DATA(char *IN_OR_OUT, long DEVICE_ID, long IN_OR_OUT_ID, char *DATA){
	//#-----------------------------------------------------------------------
		int val = 0;
	//#-----------------------------------------------------------------------
		if (MySQL_Connect()!=0)return -1;
	//#-----------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : GET_IN_OR_OUT_OBJECT_DATA : %ld(%ld) : ",DEVICE_ID,IN_OR_OUT_ID);
	//#-----------------------------------------------------------------------
		sprintf(MySQL.QUERY,"SELECT * FROM `%s` WHERE `DEV_ID` = '%ld' AND `ID` = '%ld';"
				,IN_OR_OUT ,DEVICE_ID ,IN_OR_OUT_ID);
	//#-----------------------------------------------------------------------
		if (mysql_query(MySQL.CONN, MySQL.QUERY)){
			val =  mysql_errno(MySQL.CONN);
			Print_MySQL("ERROR\n\r");
			Print_MySQL("MySQL_ERROR : %d : %s\n\r",val,mysql_error(MySQL.CONN));
			MySQL_Close();
			return val;
		} else {
			MySQL.RES = mysql_use_result(MySQL.CONN);
			while ((MySQL.ROW = mysql_fetch_row(MySQL.RES)) != NULL){
				//#------------------------------------------------
					sprintf(DATA,"%s",MySQL.ROW[4]);
				//#------------------------------------------------
			} mysql_free_result(MySQL.RES);
			Print_MySQL("OK\n\r");
		}
	//#-----------------------------------------------------------------------
		MySQL_Close();
		return 0;
}
