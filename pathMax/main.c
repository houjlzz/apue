#include <errno.h>
#include "ourhdr.h"
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

#define PATH_MAX_GUESS 1024

int 
main(int argc, char* argv[])
{
	char    *ptr;
	size_t  size;

	if(posix_version == 0){
		posix_version = sysconf(_SC_VERSION);
	}

	if(xsi_version == 0){
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	}
	printf("posix_version: %d   xsi_version: %d\n",posix_version,xsi_version);
	if(pathmax == 0){
		errno = 0;
		if((pathmax = pathconf("/",_PC_PATH_MAX)) < 0){
			if(errno == 0){
				pathmax = PATH_MAX_GUESS;
				printf("get path guess\n");
			}
			else{
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}
		else{
			pathmax++;
		}
	}

    if((posix_version < 200112L) && (xsi_version < 4)){
    	size = pathmax + 1;
    }
    else{
    	size = pathmax;
    }


    printf("path Max length: %d\n",size);
}
