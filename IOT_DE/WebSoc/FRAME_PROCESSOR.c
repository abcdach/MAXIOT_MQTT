
DEB_DEV("... DE_SOC(%d) *** WebSoc_Stream_Processingn\n\r",TCPSoc.Sock);
WSoc.InPUT_Frame_Len = WSoc_InData_Len;
WSoc.Error = 0;
for( WSoc.i = 0; WSoc.i < WSoc.InPUT_Frame_Len; WSoc.i++ ){
	WSoc.Byte = WSoc_InData[WSoc.i];
	switch (WSoc.Step) {
		case 0:
			DEB_DEV("... DE_SOC(%d) WSoc.Byte: %d \n\r",TCPSoc.Sock,WSoc.Byte);
			if( WSoc.Byte == 129 ){WSoc.Step++; break;}
			if( WSoc.Byte == 130 ){WSoc.isDataBinary = 1; WSoc.Step++; break;} //binaruli
			TA_STATUS = 255; break;
		case 1:
			WSoc.Payload_Len = WSoc.Byte & 0x7F;
			if( WSoc.Payload_Len <= 125 ){ WSoc.Step = 4; break;}
			if( WSoc.Payload_Len == 126 ){ WSoc.Step ++ ; break;}
			TA_STATUS = 255; break;
		case 2: WSoc.Payload_Len =    WSoc.Byte; WSoc.Step++; break;
		case 3: WSoc.Payload_Len =  ( WSoc.Payload_Len << 8 ) + WSoc.Byte; WSoc.Step++; break;
		case 4: WSoc.Masking_key[0] = WSoc.Byte; WSoc.Step++; break;
		case 5: WSoc.Masking_key[1] = WSoc.Byte; WSoc.Step++; break;
		case 6: WSoc.Masking_key[2] = WSoc.Byte; WSoc.Step++; break;
		case 7: WSoc.Masking_key[3] = WSoc.Byte; WSoc.Step++;
			DEB_DEV("... DE_SOC(%d) WSoc.Payload_Len : %d\n\r",TCPSoc.Sock,WSoc.Payload_Len);
			if( WSoc.Payload_Len == 0 ){TA_STATUS=255; break;}
			WSoc.DataCou = 0; break;
		case 8:
			WSoc_OutData[WSoc.DataCou] = WSoc.Byte ^ WSoc.Masking_key[WSoc.DataCou % 4];
			WSoc.DataCou ++;
			if( WSoc.DataCou == WSoc.Payload_Len ){
				WSoc.Data_Ready = 1;
				WSoc.Step = 0;
				DEB_DEV("... DE_SOC(%d) WSoc_Data_ready \n\r",TCPSoc.Sock);
				break;
			}
			break;
		default:
			break;
	}if( TA_STATUS == 255 ) break;
}


