#ifndef _SIG_H_
#include "Signal.h"
#define _SIG_H_
#endif

//Espera pelo job reportar
void waitProcess( Process_Object *process ) {

	int status;
	pid_t pid;

	do {
	  pid = waitpid(process->pgid, &status, WUNTRACED);
	  //if (WIFEXITED(status) || WIFSIGNALED(status))
	   //	    rmProcess(process->parent->jid);
	}
	while ( !WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status) );

}

//Cuida do sinal emitido pelas teclas ctrl+c
void ctrlc(int signum) {

	if ( fgProcess != NULL ) {
		kill(fgProcess->pgid,SIGINT);
		fprintf(stderr, "\nJob finalizada por sinal.\n", NULL);
	}

}

//Cuida do sinal emitido pelas teclas ctrl+z
void ctrlz(int signum) {

	Jobs *j;

	if ( fgProcess != NULL ) {
		if ( fgProcess->lancado ) {
			fgProcess->lancado  = 0;
			kill(fgProcess->pgid,SIGTSTP);
			fprintf(stderr,"\nJob parada.\n",NULL);
		}
	}

}
