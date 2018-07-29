
//########################################################################################################
//#
//#		M A I N   S T R U C T !!!!!
//#
//########################################################################################################
	typedef struct {
		unsigned char 	STATUS;									// 1 - enable , 0 -disable
		char			DESCRIPTION[INPUT_DESCRIPTION_LEN];		//
		unsigned long	LISTEN_DEVICE_NAME; 					// mowyobilobis saxeli romesac usmens
		unsigned char	LISTEN_DEVICE_OUTPUT_INDEX; 			// mowyobilobis gamosasvlelis indexi romesac usmens
		unsigned char	LISTEN_STATUS; 							// 1(ismineba) , 0(ar ismineba)
		char			CONFIG_DATA[CONFIG_DATA_LEN];			// inaxeba komfiguracia web elementistvis
		unsigned char 	MQTT_SUBSCRIBE_STATUS;					// 1 - IS_SUBSCRIBE , 0 - IS_NOT_SUBSCRIBE
	} _INPUT;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct {
		unsigned char 	STATUS;									// 1(Enable) , 0(Disable)
		char			DESCRIPTION[OUTPUT_DESCRIPTION_LEN];	// gamosasvlelis fuqciis agwera
		char			LAST_DATA[Messege_Len];					// aq inaxeba mowyobilobis gamosasvlelze mosuli bolo monacemebi
		unsigned long	LAST_DATA_TIME;							// aq inaxeba mowyobilobis gamosasvlelze mosuli bolo monacemebis dro
		unsigned long	LAST_DATA_COUNTER;						// aq inaxeba mowyobilobis gamosasvlelze mosuli bolo monacemebi raodenoba (anu mtvlelia)
		char			CONFIG_DATA[CONFIG_DATA_LEN];			// inaxeba komfiguracia web elementistvis
	} _OUTPUT;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct {
		unsigned char	ROOM;									// otaxis nomeri romelshic imyofeba obieqti
		unsigned long 	USER_INDEX;								// SQL-shi momxmareblis indexi
		unsigned long 	ID;							    		// mowyobilobis saxeli(ricxvi)
		unsigned char 	TYPE;									// mowyobilobis tipi
		unsigned short 	X;										// mowyobilobis grafikuli X mdebareboa
		unsigned short 	Y;										// mowyobilobis grafikuli Y mdebareboa
		char 			DESCRIPTION[DEVICE_DESCRIPTION_LEN];	// mowyobilobis mokle agwera(NAME_TEXT)
		char 			DATA[DEVICE_DATA_LEN];					// mowyobilobis monacemebi ME(pytonis kodi sha64 formatshi)
		unsigned char	DATA_STATUS;							// 1(new) , 0(old)
	} _DEVICE;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct {
		unsigned char 	STATUS;							// 1(Enable) , 0(Disable)
		char			MEASUREMENT[50];				//
		char			UNIT[10];						//
	} _Socket_Devices;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct {
	  unsigned char  	STATUS;							// 1(gashvebulia) , 0(araa gashvebuli)
	  char				DATA[4][200];					//
	  long				DATA_STATUS[4];					//
	  unsigned char  	PUSH[4];						//
	  pthread_mutex_t 	mutex;							//
	  pthread_cond_t  	cond;							//
	} _MEDIATOR;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct {
	  long 				X;								// SLOT sistemuri
	  long				Y;								// SLOT sistemuri
	  pthread_mutex_t	Device_cond_mutex;				//
	  pthread_cond_t	Device_condition;				//
	  long   			MSG_Number;						// shetyobinebis nomeri
	  long   			MSG_Pointer;					// shetyobinebis texstze smimtitebeli
	  _DEVICE			DEVICE;							//
	  _INPUT			INPUT[INPUT_LEN];				//
	  _OUTPUT			OUTPUT[OUTPUT_LEN];				//
	  _MEDIATOR			MEDIATOR;						//
	  unsigned char 	RUN_STATUS;						// 1(kompnenti saqmeshia) , 0(kompnenti araa saqmeshi)
	  char				THE_LAST_DATA[512];				// yvelaze bolo mosuli monacemi
	} _SLOT;
//########################################################################################################



