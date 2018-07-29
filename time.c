



void *Time_servermmm( void *arg )
{
	pthread_t self = pthread_self();
	struct timeval tv;
	while(1){
	    gettimeofday(&tv, NULL);
	    SYS_TIME_SEC = tv.tv_sec;
	    //printf("Seconds since Jan. 1, 1970: %ld\n\r", SYS_TIME_SEC);
		usleep(500000);
	}

	fflush(stdout);
	pthread_detach(self);
	return 0;
}
