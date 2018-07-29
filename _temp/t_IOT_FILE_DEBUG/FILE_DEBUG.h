

extern char STATUS_BUF_MySQL[1024];

int FILE_DEBUG_init(void);
int SAVE_DATA_TO_MySQL_STATUS_FILE(char *DATA);



#define Print_MySQL(...)	sprintf(STATUS_BUF_MySQL,__VA_ARGS__);SAVE_DATA_TO_MySQL_STATUS_FILE(STATUS_BUF_MySQL);





