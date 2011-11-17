#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>

#ifndef _STRINGFUNCTIONS_H_
#include "source/StringFunctions.h"
#define _STRINGFUNCTIONS_H_
#endif

#ifndef _COREFUNCTIONS_H_
#include "source/CoreFunctions.h"
#define _COREFUNCTIONS_H_
#endif

pid_t shell_pgid;
int shell_terminal, stdin_bak, stdout_bak;
struct termios shell_tmodes_stdin, shell_tmodes_stdout;

void initShell();
void prompt();
void resetIO();

int main(){

        initShell();
        initProcessList();
        initHistory();

	pid_t pid = shell_pgid;

	while(1 && pid == shell_pgid){
		
		//Exibe o prompt
		prompt();

        newProcess = (Process_Object *)malloc(sizeof(Process_Object));
        addProcess(newProcess);

        //Faz o parser da linha de comando
        parser(readLine(),0);

        //Roda o job
        runProcess(newProcess);
        
        //Reseta a E/S padrao
		pid = getpid();
        if ( pid == shell_pgid ) {
			resetIO();
		}
    }
}

//Inicia o shell, colocando em seu proprio grupo de processos
void initShell(){
    shell_terminal = STDIN_FILENO;

    signal (SIGINT, ctrlc);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTSTP, ctrlz);
    signal (SIGTTIN, SIG_IGN);
    signal (SIGTTOU, SIG_IGN);
    signal (SIGCHLD, SIG_IGN);

    shell_pgid = getpid ();
    if (setpgid (shell_pgid, shell_pgid) < 0)
     {
       perror ("Falha ao tentar inserir a shell em seu proprio grupo de processos");
       exit (1);
     }

    tcsetpgrp (shell_terminal, shell_pgid);

    stdin_bak = dup(STDIN_FILENO);
    stdout_bak = dup(STDOUT_FILENO);
    
}

//Funcao que exibe o prompt
void prompt(){
    pwd(0);
    printf("%s> ",workingDirectory);
}

//Funcao que reseta a E/S padrao
void resetIO(){
    fflush(stdin);
    fflush(stdout);

    dup2(stdin_bak,STDIN_FILENO);
    dup2(stdout_bak,STDOUT_FILENO);
}
