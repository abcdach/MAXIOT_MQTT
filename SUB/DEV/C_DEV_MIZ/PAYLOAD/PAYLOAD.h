

void PAYLOAD_INIT(char *IOT_IP,int IOT_PORT);
void *PAYLOAD_SYSTEM(void *arg);
void *PAYLOAD_PING(void *arg);
int DATA_TO_PAYLOAD(unsigned char DEVICE,char *DATA);
int PAYLOAD_CRC(char *data, int length);

typedef struct {
	char DEV_DESCRIPTION[64];
	char IP[64];
	int  PORT;
	int  DEV;
	int  SOCK;
	unsigned char CONNECTION_STATUS;
	unsigned char RECONNECT;		// 1 - kavshiris gawyvetisas gadakoneqteba
	unsigned char TimeOUT_MAX;
	unsigned char TimeOUT;
	char client_message[2048];
	char Server_message[2048];
} PAYLOAD_STRUCT;


extern PAYLOAD_STRUCT PAYLOAD;
extern char PAYLOAD_DATA[256];
extern char PAYLOAD_DATA2[256];


