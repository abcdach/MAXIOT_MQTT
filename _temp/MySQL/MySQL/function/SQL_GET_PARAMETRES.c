
int MySQL_GET_PARAMETRES(){
	//#----------------------------------------------------------------------------------
		long Temp = 0;
		char Temp_S[256];
	//###########################################################################################
		char JSON_Value[128];
	//###########################################################################################
		Print_MySQL("MySQL_STATU : Check the Folder /etc/MAXIOT : ");
		Temp = SYS_API__GET__Folder_Status_By_Folder_Path("/etc/MAXIOT");
		if (Temp == -1){
			Print_MySQL("ERROR\n\r");
			Print_MySQL("MySQL_ERROR : Folder /etc/MAXIOT is not found\n\r");
			Print_MySQL("MySQL_STATU : Create Folder /etc/MAXIOT : ");
			Temp = SYS_API__PUT__Folder_By_Folder_Path("/etc/MAXIOT");
			if (Temp == -1){
				Print_MySQL("ERROR\n\r");
				return -1;
			//}else{
				//printf("OK\n\r");
				//printf("MySQL_STATU : Create File MySQL_Config : ");
				//sprintf(Temp_S,
				//"{"
				//"\n\t\"SERVER\":\"localhost\""
				//"\n\t\"USER\":\"pma\""
				//"\n\t\"PASSWORD\":\"dachdach\""
				//"\n}");
				//Temp = SYS_API__PUT__DATA_TO_FILE_By_FILE_Path("MAXIOT/MySQL_Config",Temp_S);
				//if (Temp == -1){
					//printf("ERROR\n\r");
					//return -1;
				//}else printf("OK\n\r");
			}else Print_MySQL("OK\n\r");
		}else Print_MySQL("OK\n\r");
	//###########################################################################################
		Print_MySQL("MySQL_STATU : Read File /etc/MAXIOT/MySQL.cnf : ");
		Temp = SYS_API__GET__DATA_FROM_FILE_By_FILE_Path("/etc/MAXIOT/MySQL.cnf",Temp_S);
		if (Temp == -1){
			Print_MySQL("ERROR\n\r");
			Print_MySQL("MySQL_STATU : Create File /etc/MAXIOT/MySQL.cnf : ");
			sprintf(Temp_S,
			"{"
			"\n\t\"SERVER\":\"localhost\""
			"\n\t\"USER\":\"pma\""
			"\n\t\"PASSWORD\":\"dachdach\""
			"\n}");
			Temp = SYS_API__PUT__DATA_TO_FILE_By_FILE_Path("/etc/MAXIOT/MySQL.cnf",Temp_S);
			if (Temp == -1){
				Print_MySQL("ERROR\n\r");
				return -1;
			}else Print_MySQL("OK\n\r");
		}else Print_MySQL("OK\n\r");
		Print_MySQL("MySQL_STATU : FILe :\n\r%s\n\r",Temp_S);
	//#----------------------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : SERVER : ");
		if((Temp=JSON_Parser(Temp_S,"SERVER",JSON_Value))!=-1){
			if (Temp>0){
				if(strlen(JSON_Value)<128){
					sprintf(MySQL_SERVER,"%s",JSON_Value);
					Print_MySQL("OK : %s \n\r",JSON_Value);
				}else{
					Print_MySQL("ERROR\n\r");return -1;
				}
			}else{
				Print_MySQL("ERROR\n\r");return -1;
			}
		}else{
			Print_MySQL("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : USER : ");
		if((Temp=JSON_Parser(Temp_S,"USER",JSON_Value))!=-1){
			if (Temp>0){
				if(strlen(JSON_Value)<128){
					sprintf(MySQL_USER,"%s",JSON_Value);
					Print_MySQL("OK : %s \n\r",JSON_Value);
				}else{
					Print_MySQL("ERROR\n\r");return -1;
				}
			}else{
				Print_MySQL("ERROR\n\r");return -1;
			}
		}else{
			Print_MySQL("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		Print_MySQL("MySQL_STATU : PASSWORD : ");
		if((Temp=JSON_Parser(Temp_S,"PASSWORD",JSON_Value))!=-1){
			if (Temp>0){
				if(strlen(JSON_Value)<128){
					sprintf(MySQL_PASSWORD,"%s",JSON_Value);
					Print_MySQL("OK : %s \n\r",JSON_Value);
				}else{
					Print_MySQL("ERROR\n\r");return -1;
				}
			}else{
				Print_MySQL("ERROR\n\r");return -1;
			}
		}else{
			Print_MySQL("ERROR\n\r");return -1;
		}
	//#----------------------------------------------------------------------------------
		sprintf(MySQL_DATABASE,"MAXIOT");
		return 0;
}



