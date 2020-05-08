#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"
#include "stdio.h"

char decbuf[4], enbuf[3];
const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char rev(char c){
	if(c >= 'A' && c <= 'Z') return(c - 'A');
	if(c >= 'a' && c <= 'z') return(26 + c - 'a');
	if(c >= '0' && c <= '9') return(52 + c - '0');
	switch(c){
		case '+' : return 62;
		case '/' : return 63;
	}
	return c;
}

int main(int argc,char *argv[]){
	if(argc > 3){
		printf(1,"Base64: Too many argument\n");
		exit();
	}

	int decode = 0;
	int filenum = 0;
	for(int i=1; i<argc; i++){
		if(*argv[i] == '-'){
			if(strcmp(argv[i], "-d") == 0){
				decode = 1;
			}
			else{
				printf(1, "Base64: Invalid option\n");
				exit();
			}
		}
		else{
			filenum = i;
		}
	}

	int fs = open(argv[filenum], 0);
	int n;
	if(decode){
		int v;
		char out[3];
		
		while( (n = read(fs, decbuf, sizeof(decbuf))) >0 ){
			uint len = 0;
			for(char *i = decbuf; *i!= '=' && i - decbuf < 4; i++) len++;

			//printf(1, "%d\n",len);
			v = (rev(decbuf[0]) << 2) + (rev(decbuf[1]) >> 4);
			out[0] = (char) v;
			
			v = rev(decbuf[1]) << 4;
			if(len > 2){
				v += rev(decbuf[2]) >> 2;
				out[1] = (char) v;
			} else {
				out[1] = (char) v;
				out[2] = '\0';
			}

			v = rev(decbuf[2]) << 6;
			if(len > 3){
				v += rev(decbuf[3]);
				out[2] = (char) v;
			} else {
				out[2] = (char) v; 
			}

			printf(1, "%s",out, decbuf);
			memset(decbuf, '\0', sizeof(decbuf));
		}
		printf(1,"\n");
	}
	else{
		int v;
		char out[5];
		while( (n = read(fs, enbuf, sizeof(enbuf))) >0){
			uint len = strlen(enbuf);
			v = enbuf[0] >> 2;
			out[0] = b64chars[v];

			v = ((enbuf[0] & 3) << 4);
			if(len > 1){
				v += (enbuf[1] >> 4);
				out[1] = b64chars[v];
			} else{
				out[1] = b64chars[v];
				out[2] = '=';
			}

			v = ((enbuf[1] & 15) << 2);
			if(len > 2){
				//printf(1, "v = %d\n", v);
				v += (enbuf[2] >> 6);
				out[2] = b64chars[v];
				out[3] = b64chars[enbuf[2] & 63];
			} else{
				out[3] = '=';
			}
			
			printf(1,"%s", out);
			memset(enbuf, '\0', sizeof(enbuf));
		}
		printf(1,"\n");
	}

	exit();
}