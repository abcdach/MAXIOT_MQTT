#include <stdio.h>
#include <string.h>

#include"JSON.h"

long JSON_Parser(char *JSON_String, char *JSON_Name , char *JSON_Value )
{
	long x1,x2;
	long JSON_String_len = strlen(JSON_String);

	x1=dach_instr(JSON_String,0,JSON_String_len,JSON_Name,0,strlen(JSON_Name));
	if (x1!=(-1)){
		x1=dach_instr(JSON_String,x1,JSON_String_len,":",0,1);
		x1=dach_instr(JSON_String,x1,JSON_String_len,"\"",0,1);
		x2=dach_instr(JSON_String,x1+1,JSON_String_len,"\"",0,1);
		long a=0;
		long i=0;
		for( a = x1+1; a < x2; a ++ ){
			JSON_Value[i]=JSON_String[a];i++;
		}
		JSON_Value[i]=0;
		return strlen(JSON_Value);
	}else{
		JSON_Value[0]=0;
		return  -1;
	}
}


int JSON_Test()
{
	//char JSON_STRING[1000] ="{\"device\": \"0060001\", \"admin\": \"www.data2iot.com\", \"uid\": \"127.0.0.1\"}";
	char JSON_STRING[1000] ="{\"CREATE_INTERCONN\":\"31084\",\"OUTPUT\":\"1\",\"DEVICE_2\":\"300\",\"INPUT\":\"0\"}";




	char JSON_Value[1000];
	long JSON_Len;

	if ((JSON_Len= JSON_Parser(JSON_STRING,"CREATE_INTERCONN",JSON_Value))!=(-1)){
		printf("CREATE_INTERCONN - %s(%ld)\n",JSON_Value,JSON_Len);
	}else{
		printf("Error\n");
	}
	if ((JSON_Len= JSON_Parser(JSON_STRING,"OUTPUT",JSON_Value))!=(-1)){
		printf("OUTPUT - %s(%ld)\n",JSON_Value,JSON_Len);
	}else{
		printf("Error\n");
	}
	if ((JSON_Len= JSON_Parser(JSON_STRING,"DEVICE_2",JSON_Value))!=(-1)){
		printf("DEVICE_2 - %s(%ld)\n",JSON_Value,JSON_Len);
	}else{
		printf("Error\n");
	}
	if ((JSON_Len= JSON_Parser(JSON_STRING,"INPUT",JSON_Value))!=(-1)){
		printf("INPUT - %s(%ld)\n",JSON_Value,JSON_Len);
	}else{
		printf("Error\n");
	}return 0;
}



long dach_instr( char * String1, long String1_Start_Position, long String1_LEN ,char * String2, long String2_Start_Position,long String2_LEN )
{
    if ( String2_LEN > String1_LEN ) return -1;
    long x;long y;long z=0;long c=0;
    for( x=String1_Start_Position; x < String1_LEN + String1_Start_Position - (String2_LEN - 1) ; x++){
        z=0;c=0;
        for( y=String2_Start_Position; y < String2_LEN + String2_Start_Position ; y++){
            if (String1[x+z] == String2[y]){
                c++;
                if(c==String2_LEN){
                    return (x+z )- (String2_LEN - 1);
                }
            }else{
                break;
            }z++;
        }
    }return -1;
}
