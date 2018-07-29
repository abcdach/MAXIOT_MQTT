////////////////////////////////////////////////////////////
struct DevInfo {
    long 	Device_Name;		// mowyobilobis saxeli
    long 	Device_Value;		// napomni nomershi mowyobiobis saxeli
    long 	Device_Position;	// napovni nomris pozicia
};
///////////////////////////////////////////////////////
extern long DEVSYS__Devices_Buffer[];
extern long DEVSYS__SLOT_Pointer[];
extern long DEVSYS__Devices_Numer_in_Devices_Buffer;
///////////////////////////////////////////////////////
void DEVSYS__init();
long DEVSYS__Finde_device(long Device_Name);
long DEVSYS__Add_device(long Device_Name);
void DEVSYS__Delate_device(long Device_Num);
long DEVSYS__list_check(void);
///////////////////////////////////////////////////////
struct DevInfo _DEVSYS__Get_Device_Info(long Device_Name);
long _DEVSYS__Add_device(struct DevInfo *_DevInfo);
///////////////////////////////////////////////////////


