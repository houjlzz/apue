#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

#include "ourhdr.h"

static void sig_cld();

int 
main(int argc, char* argv[])
{
	pid_t pid;

	if(signal(SIGCLD,sig_cld) == -1)
		perror("signal error");

	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid == 0)
	{
		sleep(2);
		_exit(0);
	}
	pause();
	exit(0);
}

static void
sig_cld()
{
	pid_t pid;
	int   status;

	printf("SIGCLD received\n");

	if(signal(SIGCLD,sig_cld) == -1)
		perror("signal error");

	if((pid = wait(&status)) < 0)
		perror("wait error");

	printf("pid = %d\n",pid);
	return;
}