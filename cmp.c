#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"
#include "stdio.h"

int main(int argc,char *argv[]){
	int fs1, fs2;
	if(argc < 3) exit();

	fs1 = open(argv[1], 0);
	fs2 = open(argv[2], 0);

	char byte1, byte2;
	int n1 = 0, n2 = 0, line = 1, nbytes = 0, isline = 0;
	while( (n1 = read(fs1, &byte1, sizeof(byte1))) > 0 && (n2 = read(fs2, &byte2, sizeof(byte2))) > 0){
		if(isline == 1){
			line++;
			isline = 0;
		}

		if(byte1 == '\n' && byte2 == '\n') {
			isline = 1;
		}

		nbytes++;
		if(byte1 != byte2){
			printf(1, "%s %s differ: byte %d, line %d\n", argv[1], argv[2], nbytes, line);
			exit();
		}
	}
		
	if(n1 > n2){
		if(nbytes != 0) printf(1, "cmp: EOF on %s after byte %d, in line %d\n", argv[2], nbytes, line);
		else printf(1, "cmp: EOF on %s which is empty\n", argv[2]);
		exit();
	}
	else if((n2 = read(fs2, &byte2, sizeof(byte2))) && n1 < n2){
		if(nbytes != 0) printf(1, "cmp: EOF on %s after byte %d, in line %d\n", argv[1], nbytes, line);
		else printf(1, "cmp: EOF on %s which is empty\n", argv[1]);
		exit();
	}

	close(fs1);
	close(fs2);

	exit();
}