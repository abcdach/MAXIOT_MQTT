


unsigned long COUNTER = SYS_API__GET__LAST_OUTPUT_DATA_COUNTER_By_SLOT_INDEX(OUT_DEV_SLOT_INDEX, OUT_DEV_OUTPUT);
if(SAT.COUNTER != COUNTER){ SAT.COUNTER = COUNTER;

	//unsigned long TIME = SYS_API__GET__LAST_OUTPUT_DATA_TIME_By_SLOT_INDEX(OUT_DEV_SLOT_INDEX, OUT_DEV_OUTPUT);
	SYS_API__GET__LAST_OUTPUT_DATA_By_SLOT_INDEX(OUT_DEV_SLOT_INDEX, OUT_DEV_OUTPUT, Buffer);

	unsigned short Topic_Len = strlen(SAT.Topic);
	unsigned short Message_Len = strlen(Buffer);
	unsigned short Msg_Len = Topic_Len + Message_Len + 2;
	unsigned short Frame_Len = 0;
	char Frame[4096];
	unsigned short FP = 0;
	unsigned short COU = 0;

	if ( strlen(Buffer) != 0 ){

		//DEB_DEV("... DE_SOC(%d)(%ld)(%ld) %ld--> %s\n\r",SAT.Sock,TIME,COUNTER,SAT.DevInID,Buffer);

		//--------------------------------------------------------
		// MQTT
		//--------------------------------------------------------


			Frame[FP++] = 0x30;
			if( Msg_Len < 128 ){
				Frame[FP++] = Msg_Len; Frame_Len = 2;
			}else{
				Frame[FP++] = ( ( Msg_Len - ( (Msg_Len / 128) * 128 ) ) + 128 ) & 0x00FF;
				Frame[FP++] = ( Msg_Len / 128 ) & 0x00FF;
				Frame_Len = 3;
			}
			Frame[FP++] = Topic_Len >> 8;
			Frame[FP++] = Topic_Len & 0x00FF;
			for( COU = 0; COU < Topic_Len;   COU ++ ) Frame[FP++] = SAT.Topic[COU];
			for( COU = 0; COU < Message_Len; COU ++ ) Frame[FP++] = Buffer[COU];
			Frame_Len += Msg_Len;

		//############################################################################

			if( SAT.WSoc_Enable == 0 ) {
				write( SAT.Sock , Frame , Frame_Len );
			} else {
				//--------------------------------------------------------
				// MQTT -->  WEBSOCK
				//--------------------------------------------------------
					unsigned short DATA_Cou  = 0;
					unsigned  char DATA[10];

					if( SAT.WSoc_Binary_Format == 1 ) DATA[0] = 0x82;
					else DATA[0] = 0x81;

					if( Frame_Len <= 125 ){
						DATA[1] = (unsigned char) Frame_Len;
						DATA_Cou = 2;
					}else if( Frame_Len >= 126 && Frame_Len <= 65535 ){
						DATA[1] =  126;
						DATA[2] = (unsigned char)( Frame_Len >> 8 );
						DATA[3] = (unsigned char)( Frame_Len & 0x00FF );
						DATA_Cou = 4;
					}else{
						return 0;
					}
					unsigned short i = 0;
					unsigned short b = 0;
					for( i = 0; i < DATA_Cou; i++ ){
						Buffer[b] = DATA[i]; b++;
					}
					for( i = 0; i < Frame_Len; i++ ){
						Buffer[b] = Frame[i]; b++;
					}

					write( SAT.Sock , Buffer , DATA_Cou + Frame_Len );
				 //--------------------------------------------------------
			}
	 }
}


















