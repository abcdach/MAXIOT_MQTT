

#export PS1='> '

Files=sslconnect.c

CC=gcc
#CCFLAGS= -g -std=c99 -Wall -Werror -pthread -lssl -lcrypto
CCFLAGS =  -Wall -o client  -L/usr/lib -lssl -lcrypto
OUTPUT= test

all:
	$(CC) $(CCFLAGS) ${Files} -o ${OUTPUT}  

# gcc -Wall -o client  Client.c -L/usr/lib -lssl -lcrypto