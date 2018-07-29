


if(SYS_DEB==1)printf("--> SYS : %s\n\r",MAXIOT.Server_message);
SENT_TO_IOT("{\"N\":\"1\",\"D\":\"%ld\",\"V\":\"%s\"}"
		,(long)MAXIOT.DEV,MAXIOT.DEV_DESCRIPTION);

