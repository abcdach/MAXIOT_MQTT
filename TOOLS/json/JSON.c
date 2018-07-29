#include <stdio.h>
#include <string.h>

#include"JSON.h"


long JSON_Parser(char *JSON_String, char *JSON_Name , char *JSON_Value){
	long JSON_String_len = 0;
	long JSON_Name_len = 0;
	long i,ii,iii,Temp;
	for (i = 0; i < 3000; i++){if(JSON_String[i]==0){JSON_String_len = i;break;}}
	for (i = 0; i < 3000; i++){if(JSON_Name[i]==0){JSON_Name_len = i;break;}}
	Temp = JSON_Name_len + 4;
	if(JSON_String_len>Temp){
		Temp = JSON_String_len - Temp;
		i=0;
		while (1){
			if(JSON_String[i]=='"'){
				ii = i + JSON_Name_len + 1;
				if(JSON_String[ii]=='"'){
					ii++;
					if(JSON_String[ii]==':'){
						ii = i+1;
						for (iii = 0; iii < JSON_Name_len; iii++){
							if(JSON_String[ii]!=JSON_Name[iii]) break;
							ii ++;
						}
						if(iii==JSON_Name_len){
							i = i+JSON_Name_len+3;
							if(JSON_String[ii]=='"'){
								ii = 0;
								while (1){
									i++;
									if(JSON_String[i]=='"'){
										JSON_Value[ii]=0;
										return ii;
									}
									JSON_Value[ii]=JSON_String[i];
									ii ++;
									if(i>=JSON_String_len) return -1;
								}return 0;
							}else return -1;
						}i++;
					}else i++;
				}else i++;
			}else i++;
			if(i>=Temp)break;
		}return -1;
	}else return -1;
}


long dach_instr( char * String1, long String1_Start_Position, long String1_LEN ,char * String2, long String2_Start_Position,long String2_LEN )
{
    if ( String2_LEN > String1_LEN ) return -1;
    long x,y,z,c;
    for( x=String1_Start_Position; x < String1_LEN + String1_Start_Position - (String2_LEN - 1) ; x++){
        z=0;c=0;
        for( y=String2_Start_Position; y < String2_LEN + String2_Start_Position ; y++){
            if (String1[x+z] == String2[y]){
                c++;
                if(c==String2_LEN) return (x+z )- (String2_LEN - 1);
            }else break;
            z++;
        }
    }return -1;
}
