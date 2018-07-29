
//#-------------------------------------------------------------------
	SYS_API__ADD__DEVICE_By_DEVICE_ID( 1 );
//#-------------------------------------------------------------------
	SYS_API__ADD__DEVICE_By_DEVICE_ID( IOT_STUDIO_CHANNEL_DEVICE );
	IOT_STUDIO_CHANNEL_INDEX = SYS_API__GET__SLOT_INDEX_By_DEVICE_ID( IOT_STUDIO_CHANNEL_DEVICE );
	Momxede_Me=1; // !!!!!!!!!!!!! SAGANGEBO MARKERI
	//if(SLOT_INDEX != -1){}///
	SYS_API__CLEANING__DEVICE_By_SLOT_INDEX(IOT_STUDIO_CHANNEL_INDEX);
	SYS_API__ADD__DEVICE_MUTEX_COND_By_SLOT_INDEX(IOT_STUDIO_CHANNEL_INDEX);
	//printf("SYS>> CREATE ( IOT STUDIO CHANNEL %ld INDEX:%ld )\n\r",(long)IOT_STUDIO_CHANNEL_DEVICE,IOT_STUDIO_CHANNEL_INDEX);
//#-------------------------------------------------------------------
