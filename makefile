
#tar -cvf 102.tar iot/
#export PS1='> '

Files=core.c\
SYSTEM/File/FILE_SYS.c \
SYSTEM/Device/DEVSYS.c \
SYSTEM/Messege/MSGSYS.c \
SYSTEM/Slot/SLOTSYS.c \
SYSTEM/SYSTEM.c \
TOOLS/json/JSON.c \
TOOLS/base64/base64.c \
TOOLS/base64_2/base64_2.c \
TOOLS/AES/aes.c \
IOT_STUDIO/IOT_STUDIO.c \
IOT_DE/DE.c \
IOT_ME/ME.c \
IOT_STATISTICS/EVENT_COUNTER.c \
IOT_MENU/MENU.c \
TOOLS/sha1/MyBase64.c \
TOOLS/sha1/MySHA1.c \
TOOLS/sha1/SHA1_Calc.c \
IOT_FOBJECTS/FOBJECTS.c \

#MySQL/MySQL.c \
#IOT_DEBUG/IOT_DEBUG.c \
#IOT_DEBUG/SYS_INFO/SYS_INFO.c \
#IOT_DEBUG/SYS_INFO/Linked_List.c \
#IOT_SocDEB/SocDEB.c \
#IOT_FILE_DEBUG/FILE_DEBUG.c \


CC       = gcc
CCFLAGS0 = -g -Wall -Werror -std=gnu99
CCFLAGS1 = -pthread 
#CCFLAGS3 = `mysql_config --cflags --libs`
#CCFLAGS3 = -I/usr/include/mysql
#CCFLAGS4 = -lmysqlclient  
CCFLAGS5 = -I/usr/include/python2.7 
CCFLAGS6 = -lpython2.7
OUTPUT   = MAXIOT_SERVER

all:
	$(CC) $(CCFLAGS0) $(CCFLAGS1)  $(CCFLAGS5) ${Files} $(CCFLAGS6) -o ${OUTPUT}



