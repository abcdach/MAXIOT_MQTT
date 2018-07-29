

typedef struct {
	unsigned char  Byte   ;
	unsigned char  Enable ;
	unsigned char  Binary_Format;
	unsigned char  Step   ;
	unsigned short i      ;
	unsigned char  Error  ;
	unsigned char  Data_Ready;
	unsigned short DataCou;
	unsigned short InPUT_Frame_Len ;
	unsigned short Payload_Len;
	//unsigned char  MaskIndex;
	unsigned char  Masking_key[4];
	unsigned char  Protocol_Scanner;
	unsigned char  isDataBinary;
} WebSoc_Stream;
WebSoc_Stream	WSoc;

WSoc.Enable     = 0;
WSoc.Step       = 0;
WSoc.Data_Ready = 0;
WSoc.Protocol_Scanner = 0;
WSoc.isDataBinary = 0;
WSoc.Binary_Format = 0;

#define WSoc_InData		 TCPSoc.RxFRAME
#define WSoc_OutData	 TCPSoc.TxFRAME

#define WSoc_InData_Len	 TCPSoc.FRAME_LEN

