

void MAXIOT_INIT(char *IOT_IP,int IOT_PORT);
void *MAXIOT_SYSTEM(void *arg);
void *MAXIOT_PING(void *arg);
int DATA_TO_IOT(unsigned char SLOT, char *DATA);

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
} MAXIOT_STRUCT;


extern MAXIOT_STRUCT MAXIOT;



