




void *MQTT_Publish_Message_Tread(void *arg){

	typedef struct {
				 int	Sock;
				 long	DevID;
				 long	DevInID;
		unsigned long	COUNTER;
				 char	Topic[256];
		unsigned char	WSoc_Enable ;
		unsigned char	WSoc_Binary_Format;

	} _SAT; _SAT SAT;
	//----------------------------------------------------------
		_MQTT_PARG* ARG = (_MQTT_PARG*)arg;
	//----------------------------------------------------------
		SAT.Sock    = ARG -> Sock;
		SAT.DevID   = ARG -> DevID;
		SAT.DevInID = ARG -> DevInID;
		sprintf(SAT.Topic,"%s",ARG->Topic);
		SAT.WSoc_Enable =  ARG -> WSoc_Enable;
		SAT.WSoc_Binary_Format = ARG -> WSoc_Binary_Format;
	//----------------------------------------------------------
		//pthread_t parent_self = ARG -> self;
	//----------------------------------------------------------
		pthread_t self = pthread_self();
	//----------------------------------------------------------
		DEB_DEV("... DE_SOC(%d) --> MQTT_Publish_Message_Tread\n\r",SAT.Sock);
		DEB_DEV("... DE_SOC(%d) --> SAT.DevID: %ld\n\r",SAT.Sock,SAT.DevID);
		DEB_DEV("... DE_SOC(%d) --> SAT.DevInID: %ld\n\r",SAT.Sock,SAT.DevInID);
		DEB_DEV("... DE_SOC(%d) --> SAT.Topic: %s\n\r",SAT.Sock,SAT.Topic);
	//----------------------------------------------------------
		struct timeval  xtv;
		struct timespec xts;

		long SLOT_INDEX = 0;
		long OUT_DEV_ID = 0;
		char OUT_DEV_OUTPUT = 0;
		long OUT_DEV_SLOT_INDEX = 0;
		char Buffer[4096];
	//----------------------------------------------------------



		while(1){

		//--------------------------------------------------------------------------------------------------------------------
			//patroni mowyobiloba washlilia mowyobiobata siebidan
			SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(SAT.DevID);
			if(SLOT_INDEX == -1){
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld SLOT_INDEX(-1) is not found !!!\n\r",SAT.Sock,SAT.DevID);
				break;
			}
		//--------------------------------------------------------------------------------------------------------------------
			//patroni mowyobiloba moertebeulia ?
			if(SYS_API__GET__DEVICE_RUN_STATUS_By_SLOT_INDEX(SLOT_INDEX) == IS_NOT_RUN){
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld RUN_STATUS IS == IS_NOT_RUN  !!!\n\r",SAT.Sock,SAT.DevID);
				break;
			}
		//--------------------------------------------------------------------------------------------------------------------
			//patroni mowyobiloba gadawyvita abortis gaketeba
			if(SYS_API__GET__INPUT_MQTT_SUBSCRIBE_STATUS_By_SLOT_INDEX(SLOT_INDEX,SAT.DevInID) == IS_NOT_SUBSCRIBE){
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld MQTT_SUBSCRIBE_STATUS IS == IS_NOT_SUBSCRIBE  !!!\n\r",SAT.Sock,SAT.DevID);
				break;
			}
		//--------------------------------------------------------------------------------------------------------------------
			//sheqmnilia tu ara mowyobilobis shesasvleli (input)
			if(SYS_API__GET__INPUT_STATUS_By_SLOT_INDEX(SLOT_INDEX, SAT.DevInID) == DISABLE){
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld INPUT: %ld  STATUS IS == DISABLE  !!!\n\r",SAT.Sock,SAT.DevID,SAT.DevInID);
				usleep(1000000); continue;
			}
		//--------------------------------------------------------------------------------------------------------------------
			/** es funqcia ar mushaobs !!!!! ar reagirebs
			if(SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(SLOT_INDEX, SAT.DevInID) == IS_NOT_LISTEN){
				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld INPUT: %ld  LISTEN_STATUS IS == IS_NOT_LISTEN  !!!\n\r",SAT.Sock,SAT.DevID,SAT.DevInID);
				//break;
			} else {

				DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld INPUT: %ld  LISTEN_TO ............ !!!\n\r",SAT.Sock,SAT.DevID,SAT.DevInID);
			}**/
		//--------------------------------------------------------------------------------------------------------------------
			OUT_DEV_ID = SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(SLOT_INDEX, SAT.DevInID);
			//DEB_DEV("... DE_SOC(%d) --> DEVICE_ID: %ld INPUT: %ld  OUT_DEV_ID: %ld !!!\n\r",SAT.Sock,SAT.DevID,SAT.DevInID,OUT_DEV_ID);
			if( OUT_DEV_ID !=0 ){
				OUT_DEV_OUTPUT = SYS_API__GET__LISTEN_DEVICE_OUTPUT_INDEX_By_SLOT_INDEX(SLOT_INDEX,SAT.DevInID);
				//DEB_DEV("... DE_SOC(%d) --> OUT_DEV_OUTPUT: %d !!!\n\r",SAT.Sock,OUT_DEV_OUTPUT);
				OUT_DEV_SLOT_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUT_DEV_ID);
				if(SLOT_INDEX == -1) { usleep(1000000); continue; }
			} else { usleep(1000000); continue; }
		//--------------------------------------------------------------------------------------------------------------------


			//if(SYS_API__GET__DEVICE_INPUT_LISTEN_STATUS_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT) == IS_NOT_LISTEN)break;
			//if(SYS_API__GET__LISTEN_DEVICE_NAME_By_SLOT_INDEX(IN_DEV__SLOT_INDEX, (unsigned char)IN_DEV__INPUT) == 0)break;
			//if(SYS_API__GET__SLOT_INDEX_By_DEVICE_ID(OUT_DEV__NAME)==-1)break;
		//--------------------------------------------------------------------------------------------------------------------
			gettimeofday(&xtv, NULL);
			xts.tv_sec = xtv.tv_sec;
			xts.tv_nsec = xtv.tv_usec*1000;
			xts.tv_sec += 3;

			pthread_mutex_lock(&SLOT[OUT_DEV_SLOT_INDEX].Device_cond_mutex);
			int cond = pthread_cond_timedwait(&SLOT[OUT_DEV_SLOT_INDEX].Device_condition,&SLOT[OUT_DEV_SLOT_INDEX].Device_cond_mutex, &xts);
			pthread_mutex_unlock(&SLOT[OUT_DEV_SLOT_INDEX].Device_cond_mutex);
		//--------------------------------------------------------------------------------------------------------------------
			if(cond == 0){
				#include "INPUT_DATA_PROCESSOR.c"
			} else {
				// TimeOUT //
				//DEB_DEV("... DE_SOC(%d) -->  TimeOUT\n\r",SAT.Sock);
			}
		}




		DEB_DEV("... DE_SOC(%d) --> MQTT_Publish_Message_Tread EXIT !!!\n\r",SAT.Sock);
		fflush(stdout);
		pthread_detach(self);
		return 0;
}






