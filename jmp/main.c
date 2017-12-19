#include <setjmp.h>
#include "ourhdr.h"

void func(int i);

static jmp_buf jmpbuffer;

int 
main(int argc, char* argv[])
{
	volatile int i = 0;
	for(;i<5;)
	{
		i++;
		printf("setjmp return = %d\n,i = %d",setjmp(jmpbuffer),i);
		func(i);
	}
}


void func(int i)
{
	sleep(1);
	longjmp(jmpbuffer,3);
}
