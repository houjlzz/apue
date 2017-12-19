#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include "ourhdr.h"

static void 
dopath(char* fullpath)
{
	struct stat     statbuf;
	struct dirent   *dirp;
	DIR             *dp;
	int             ret,n;

	if(lstat(fullpath,&statbuf) < 0){
		return;
	}
	if(S_ISDIR(statbuf.st_mode) == 0){
		printf("F: %s\n",fullpath);
		return;
	}else{
		printf("D: %s\n",fullpath);
	}

	if((dp = opendir(fullpath)) == NULL){
		printf("open dir error");
		return;
	}

	while((dirp = readdir(dp)) != NULL){
		if(strcmp(dirp->d_name,".") == 0 ||
		   strcmp(dirp->d_name,"..") == 0){
               continue;
		}
		
		int parentPathLength = strlen(fullpath);
		int childPathLength = strlen(dirp->d_name);

		char * childPath = (char*)malloc((parentPathLength + childPathLength + 2)*sizeof(char));
		memset(childPath,0,parentPathLength + childPathLength + 2);
		memcpy(childPath,fullpath,parentPathLength);

		if(fullpath[parentPathLength-1] == '/'){
			memcpy(childPath+parentPathLength,dirp->d_name,childPathLength);
		}
		else{
			childPath[parentPathLength]='/';
			memcpy(childPath+parentPathLength+1,dirp->d_name,childPathLength);
		}
	//	printf("D: %s\n",childPath);
		dopath(childPath);
		free(childPath); 

	}
	closedir(dp);
}



int 
main(int argc, char* argv[])
{
	if(argc < 2){
		printf("%s\n","input dirPath");
		return 0;
	}

	dopath(argv[1]);

	return 0;

}
