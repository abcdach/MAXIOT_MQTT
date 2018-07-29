

int MySQL_DB_TO_STRUCTURE(){
	return 0;
	long Temp = 0;



	while(1){
		//Print_MySQL("\n\r");
		MySQL_Connect();
		Temp = MySQL_READ_DEVICE();
		MySQL_Close();
		if(Temp != 1)break;
	}
	while(1){
		Print_MySQL("\n\r");
		MySQL_Connect();
		Temp = MySQL_READ_INPUT_OBJECTS();
		MySQL_Close();
		if(Temp != 1)break;
	}
	while(1){
		Print_MySQL("\n\r");
		MySQL_Connect();
		Temp = MySQL_READ_OUTPUT_OBJECTS();
		MySQL_Close();
		if(Temp != 1)break;
	}
	while(1){
		Print_MySQL("\n\r");
		MySQL_Connect();
		Temp = MySQL_READ_INTERCONN_OBJECTS();
		MySQL_Close();
		if(Temp != 1)break;
	}
	return 0;
}

