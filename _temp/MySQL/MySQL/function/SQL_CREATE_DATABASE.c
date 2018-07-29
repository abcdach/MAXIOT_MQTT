
int MySQL_CREATE_DATABASE(){

	int val = 0;
	MYSQL *con = mysql_init(NULL);
	char QUERY[512];

	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CONNECT : ");
	if (!mysql_real_connect(con, MySQL_SERVER, MySQL_USER, MySQL_PASSWORD, NULL, 0, NULL, 0)) {
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
		mysql_close(con);
		return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CREATE DATABASE : %s : ",MySQL_DATABASE);
	sprintf(QUERY,"CREATE DATABASE `%s` ;",MySQL_DATABASE);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : USE DB : %s : ",MySQL_DATABASE);
	sprintf(QUERY,"USE `%s` ;",MySQL_DATABASE);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CREATE TABLE : DEVICE : ");
	sprintf(QUERY,"CREATE TABLE DEVICE"
			"("
			" i INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
			" ID INT(11) UNSIGNED NOT NULL,"
			" DESCRIPTION VARCHAR(128) NOT NULL,"
			" TYPE INT(11) UNSIGNED NOT NULL,"
			" X INT(11) UNSIGNED NOT NULL,"
			" Y INT(11) UNSIGNED NOT NULL,"
			" DATA VARCHAR(4096) NOT NULL,"
			" ROOM INT(11) UNSIGNED NOT NULL"
			");"
	);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CREATE TABLE : INPUT : ");
	sprintf(QUERY,"CREATE TABLE INPUT"
			"("
			" i INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
			" DEV_ID INT(11) UNSIGNED NOT NULL,"
			" ID INT(11) UNSIGNED NOT NULL,"
			" DESCRIPTION VARCHAR(128) NOT NULL,"
			" DATA VARCHAR(2048) NOT NULL"
			");"
	);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CREATE TABLE : OUTPUT : ");
	sprintf(QUERY,"CREATE TABLE OUTPUT"
			"("
			" i INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
			" DEV_ID INT(11) UNSIGNED NOT NULL,"
			" ID INT(11) UNSIGNED NOT NULL,"
			" DESCRIPTION VARCHAR(128) NOT NULL,"
			" DATA VARCHAR(2048) NOT NULL"
			");"
	);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////
	Print_MySQL("MySQL_STATU : CREATE TABLE : INTERCONN : ");
	sprintf(QUERY,"CREATE TABLE INTERCONN"
			"("
			" i INT(11) UNSIGNED AUTO_INCREMENT PRIMARY KEY,"
			" DEV_1_ID INT(11) UNSIGNED NOT NULL,"
			" OUT_ID INT(11) UNSIGNED NOT NULL,"
			" DEV_2_ID INT(11) UNSIGNED NOT NULL,"
			" IN_ID INT(11) UNSIGNED NOT NULL"
			");"
	);
	if (mysql_query(con, QUERY)){
		val = mysql_errno(con);
		Print_MySQL("ERROR\n\r");
		Print_MySQL("MySQL_ERROR : %s\n\r",mysql_error(con));
	    mysql_close(con);
	    return val;
	}Print_MySQL("OK\n\r");usleep(200);
	/////////////////////////////////////////////////////////////////////////////

	mysql_close(con);
	return val;
}



