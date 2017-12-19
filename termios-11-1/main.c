#include <termios.h>
#include "ourhdr.h"

int 
main(int argc, char* argv[])
{
	struct termios term;
	long vdisables;

	if(isatty(STDIN_FILENO) == 0){
		err_quit("standard input is not a terminal device");
	} 

	if((vdisables = fpathconf(STDIN_FILENO,_PC_VDISABLE)) < 0){
		err_quit("fpathconf error or _PC_VDISABLE not in effect");
	}

	if(tcgetattr(STDIN_FILENO,&term) < 0){
		err_sys("tcgetattr error");
	}

	term.c_cc[VINTR] = vdisables;
	term.c_cc[VEOF] = 2;

	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&term) < 0){
		err_sys("tcsetattr error");
	}

	exit(0);
}
