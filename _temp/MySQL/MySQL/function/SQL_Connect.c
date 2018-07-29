
int MySQL_Connect(){
	MySQL.SERVER   = MySQL_SERVER;
	MySQL.USER 	   = MySQL_USER;
	MySQL.PASSWORD = MySQL_PASSWORD;
	MySQL.DATABASE = MySQL_DATABASE;
	MySQL.CONN     = mysql_init(NULL);
	///////////////////////////////
	int value = 0;
	///////////////////////////////
	usleep(500);
	Print_MySQL("MySQL_STATU : CONNECT : ");
	if (!mysql_real_connect(MySQL.CONN, MySQL.SERVER, MySQL.USER, MySQL.PASSWORD, MySQL.DATABASE, 0, NULL, 0)) {
		value = mysql_errno(MySQL.CONN);
		Print_MySQL("ERROR !!!\n\r");
		Print_MySQL("MySQL_ERROR : %d : %s\n\r",value,mysql_error(MySQL.CONN));
	} else Print_MySQL("OK !!!\n\r");usleep(200);
	return value;
}
