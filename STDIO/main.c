#include <errno.h>
#include "ourhdr.h"

void pr_stdio(const char* name,FILE *fp);

int 
main(int argc, char* argv[])
{
	FILE  *fp;

	fputs("enter any charactor\n",stdout);
	if(getchar() == EOF)
		err_sys("getchar error");

	fputs("one line to standard error\n",stderr);

	pr_stdio("stdin",stdin);
	pr_stdio("stdout",stdout);
	pr_stdio("stderr",stderr);

	if((fp = fopen("/etc/motd","r")) == NULL){
		err_sys("fopen error");
	}

	if(getc(fp) == EOF){
		err_sys("getc error");
	}

	pr_stdio("/etc/motd",fp);

	exit(0);
}

void pr_stdio(const char* name,FILE *fp)
{
	printf("stream = %s, ",name);

	if(fp->_flag & _IONBF)  printf("unbuffered");
	else if(fp->__flag & _IOLBF) printf("line buffered");
	else printf("fully buffered");

	printf(", buffer size = %d\n", fp->_bufsiz);
}
