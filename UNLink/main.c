#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ourhdr.h"
#define BUFFSIZE 8192
int 
main(int argc, char* argv[])
{
	if(open("tempfile",O_RDWR) < 0){
		err_sys("open error");
	}

	if(unlink("tempfile") < 0){
		err_sys("unlink error");
	}

	printf("file unlinked\n");
	sleep(15);
	printf("done\n");

	exit(0);
	
}
