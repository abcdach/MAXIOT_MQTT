







pthread_attr_t is_STACK_SIZE;
void *MQTT_Publish_Message_Tread(void *arg);


typedef struct {
  //pthread_t self;
		   int		Sock;
  	  	   long 	DevID;
  	  	   long 	DevInID;
  	  	   char		Topic[256];
  unsigned char 	WSoc_Enable ;
  unsigned char 	WSoc_Binary_Format;
} _MQTT_PARG;
_MQTT_PARG	MQTT_PARG;











