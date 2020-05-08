#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"
#include "stdio.h"

int main(int argc,char *argv[]){
	printf(1, "%s %s\n", argv[0], argv[1]);
    if(argc > 2){
    	printf(1, "cd: too many arguments\n");
    	exit();
    }

    if(argc < 2){
    	chdir("/");
        exit();
    }

    struct stat st;
    int res = stat(argv[1], &st);

    if(res < 0) printf(1, "cd: %s: No such file or directory\n", argv[1]);
    if(st.type != 1) printf(1, "%s: Not a directory\n", argv[1]);

    res = chdir(argv[1]);
    if(res < 0){
    	printf(1, "cd: Unexpected Error");
        exit();
    }
}