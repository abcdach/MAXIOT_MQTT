







//###############################################################################
//#
//###############################################################################
void WebSOC_RDATA_Processing( char *Output_Data, char *Input_Data )
{
	unsigned short WebSoc_Payload_Len = (unsigned char)Input_Data[1] & 0x7F;
	unsigned char  WebSoc_MaskIndex = 2;
	unsigned char  WebSoc_Masking_key[4];

	if(WebSoc_Payload_Len==126){
		WebSoc_MaskIndex = 4;
		WebSoc_Payload_Len = (unsigned char)Input_Data[2];
		WebSoc_Payload_Len = (WebSoc_Payload_Len << 8)+(unsigned char)Input_Data[3];
	}
	else if(WebSoc_Payload_Len==127){
		WebSoc_MaskIndex = 6;
		WebSoc_Payload_Len = 0;
	}

	printf("WebSoc_Payload_Len = %d\n\r",(unsigned short)WebSoc_Payload_Len);

	unsigned short i;
	for( i=0; i<4; i++){
		WebSoc_Masking_key[i] = (unsigned char)Input_Data[WebSoc_MaskIndex + i] ;
	}




	unsigned char WebSoc_DataStart = WebSoc_MaskIndex + 4;
	for( i=0; i<WebSoc_Payload_Len; i++){
		Output_Data[i] = (unsigned char)Input_Data[WebSoc_DataStart + i] ;
	}
	Output_Data[ WebSoc_Payload_Len ] = 0x00;



	for (i = 0; i < WebSoc_Payload_Len; i++){
		Output_Data[i] = Output_Data[i] ^ WebSoc_Masking_key[i % 4];
	}




}











