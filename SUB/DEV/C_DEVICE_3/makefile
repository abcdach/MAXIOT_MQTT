

#export PS1='> '

Files=001.c \
TOOLS/json/JSON.c \
MAXIOT/MAXIOT.c



CC=gcc
CCFLAGS= -g -std=c99 -Wall -Werror -pthread
OUTPUT= test

all:
	$(CC) $(CCFLAGS) ${Files} -o ${OUTPUT}  

