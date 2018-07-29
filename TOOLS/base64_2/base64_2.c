#include<stdio.h>
#include<string.h>
///////////////////////////////////////////////////////
#include"base64_2.h"


/* ---- Base64 Encoding/Decoding Table --- */
char _b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


void b64_test(void)
{

	  //char mysrc[] = "My bonnie is over the ocean...";
	  char mysrc[] = "David chkhaidze";
	  char myb64[1024] = "";
	  char mydst[1024] = "";

	  _b64_encode(mysrc, myb64);
	  printf("The string\n[%s]\nencodes into base64 as:\n[%s]\n", mysrc, myb64);
	  printf("\n");
	  _b64_decode(myb64, mydst);
	  printf("The string\n[%s]\ndecodes from base64 as:\n[%s]\n", myb64, mydst);

}






/* decodeblock - decode 4 '6-bit' characters into 3 8-bit binary bytes */
void _decodeblock(unsigned char in[], char *clrstr) {
  char out[4];
  out[0] = in[0] << 2 | in[1] >> 4;
  out[1] = in[1] << 4 | in[2] >> 2;
  out[2] = in[2] << 6 | in[3] >> 0;
  out[3] = '\0';
  strncat(clrstr, out, sizeof(out));
}

void _b64_decode(char *b64src, char *clrdst) {
  int c, phase, i;
  unsigned char in[4];
  char *p;

  clrdst[0] = '\0';
  phase = 0; i=0;
  while(b64src[i]) {
    c = (int) b64src[i];
    if(c == '=') {
      _decodeblock(in, clrdst);
      break;
    }
    p = strchr(_b64, c);
    if(p) {
      in[phase] = p - _b64;
      phase = (phase + 1) % 4;
      if(phase == 0) {
        _decodeblock(in, clrdst);
        in[0]=in[1]=in[2]=in[3]=0;
      }
    }
    i++;
  }
}

/* encodeblock - encode 3 8-bit binary bytes as 4 '6-bit' characters */
void _encodeblock( unsigned char in[], char b64str[], int len ) {
    char out[5];
    out[0] = _b64[ in[0] >> 2 ];
    out[1] = _b64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? _b64[ ((in[1] & 0x0f) << 2) |
             ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? _b64[ in[2] & 0x3f ] : '=');
    out[4] = '\0';
    strncat(b64str, out, sizeof(out));
}

/* encode - base64 encode a stream, adding padding if needed */
void _b64_encode(char *clrstr, char *b64dst) {
  unsigned char in[3];
  int i, len = 0;
  int j = 0;

  b64dst[0] = '\0';
  while(clrstr[j]) {
    len = 0;
    for(i=0; i<3; i++) {
     in[i] = (unsigned char) clrstr[j];
     if(clrstr[j]) {
        len++; j++;
      }
      else in[i] = 0;
    }
    if( len ) {
      _encodeblock( in, b64dst, len );
    }
  }
}

