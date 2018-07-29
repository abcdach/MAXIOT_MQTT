#define isMQTT_Connect_Command		0x10
#define isMQTT_Publish_Message		0x30
#define isMQTT_Ping_Request			0xC0
#define isMQTT_Disconnect_Req		0xE0
#define isMQTT_Subscribe_Request	0x82
#define isMQTT_Subscribe_Ack 		0x90
#define isMQTT_Connect_Ack			0x20
#define isMQTT_Unsubscribe_Request	0xA2
#define isMQTT_Unsubscribe_Ack	    0xB0



typedef struct {
	unsigned short FC;
			 char  Data;
	unsigned char  Message_Status;
	unsigned char  Message_Type;
	unsigned char  STEP;
	unsigned short Msg_Len;
	unsigned short Protocol_Name_Length;
			 char  Protocol_Name[16];
	unsigned char  Version;
	unsigned char  Connect_Flags;
	unsigned short Keep_Alive;
	unsigned short Client_ID_Length;
			 char  Client_ID[128];
	unsigned short Topic_Length;
			 char  Topic[256];
	unsigned short Message_Length;
			 char  Message[4092];
	unsigned short Message_Identifier;		//isMQTT_Publish_Message
	unsigned char  QoS;						//isMQTT_Publish_Message
	unsigned short Publish_Message_Status;
	unsigned short ii;
	unsigned char  Enable;
	unsigned short OutData_Len;
	unsigned short TxStatus;
	unsigned char  Protocol_Scanner;
	unsigned char  Subscribe_Request_Status;
	unsigned char  Unsubscribe_Request_Status;
	unsigned char  Ping_Request_Status;

} _MQTT; _MQTT	MQTT;

MQTT.FC = 0;
MQTT.Data = 0;
MQTT.Message_Status = 0;
MQTT.Message_Type = 0;
MQTT.STEP = 0;
MQTT.Msg_Len = 0;
MQTT.Protocol_Name_Length = 0;
MQTT.Protocol_Name[0] = 0;
MQTT.Version = 0;
MQTT.Connect_Flags = 0;
MQTT.Keep_Alive = 0;
MQTT.Client_ID_Length = 0;
MQTT.Client_ID[0] = 0;
MQTT.Topic_Length = 0;
MQTT.Topic[0] = 0;
MQTT.Message_Length = 0;
MQTT.Message[0] = 0;
MQTT.Message_Identifier = 0;
MQTT.QoS = 0;
MQTT.Publish_Message_Status = 0;
MQTT.ii = 0;
MQTT.Enable = 0;
MQTT.OutData_Len = 0;
MQTT.TxStatus = 0;
MQTT.Protocol_Scanner = 0;
MQTT.Subscribe_Request_Status = 0;
MQTT.Ping_Request_Status = 0;
MQTT.Unsubscribe_Request_Status = 0;

#define MQTT_InData		 	TCPSoc.RxFRAME
#define MQTT_OutData	 	TCPSoc.TxFRAME
#define MQTT_InData_Len		TCPSoc.FRAME_LEN
//#define MQTT_OutData_Len	TCPSoc.TxFRAME






//#####################################################################
//#####################################################################


typedef struct {
	unsigned char A;
	unsigned char B;
	unsigned char C;
	char          D[64];
	unsigned char E;
	unsigned char Error;
	unsigned char START;

	char Description[64];
	char Description_len;

	long ID;
	long InID;
	long SLOT_INDEX;

	//unsigned char Subscribe_Status[INPUT_LEN];


} _DEV; _DEV  DEV;

DEV.A = 0;
DEV.B = 0;
DEV.C = 0;
DEV.E = 0;
DEV.Error  = 0;
DEV.D[0]   = 0;
DEV.Description[0]  = 0;
DEV.Description_len = 0;
DEV.ID   = 0;
DEV.SLOT_INDEX = 0;
DEV.InID = 0;
DEV.START = 0;
//for (DEV.A = 0; DEV.A < INPUT_LEN; DEV.A++)Subscribe_Status[DEV.A]=0;




