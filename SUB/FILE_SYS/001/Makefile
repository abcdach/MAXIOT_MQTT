#tests: tests.o ubasic.o tokenizer.o
#use-ubasic: use-ubasic.o ubasic.o tokenizer.o
#clean:
#	rm *.o tests use-ubasic
	
	
	
	
	#export PS1='> '

Files=test.c\
#ubasic.c \
#tokenizer.c \
#use-ubasic.c \
#core/tools/json/JSON.c  \
#core/buffers/slot_system/SLOT_Buffer_System.c 


CC=gcc
CCFLAGS= -g -std=c99 -Wall -Werror -pthread  -I/usr/include/python2.7 -lpython2.7
OUTPUT= test


all:
	$(CC) $(CCFLAGS) ${Files} -o ${OUTPUT}  

	
