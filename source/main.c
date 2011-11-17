#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>
#include "StringFunctions.h"
#include "CoreFunctions.h"

pid_t shell_pgid;
int shell_terminal;
struct termios shell_tmodes_stdin, shell_tmodes_stdout;

void initShell();
void prompt();

int main(){

        initShell();
        initProcessList();

	while(1){
		prompt(); //substituir por variavel - para mostra o diretorio que esta

                newProcess = (Process_Object *)malloc(sizeof(Process_Object));

                parser();

                runProcess(newProcess);

                //resetAttributes();
       }
}

void initShell(){
    shell_terminal = STDIN_FILENO;

    signal (SIGINT, SIG_IGN);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTSTP, SIG_IGN);
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

    tcgetattr (shell_terminal, &shell_tmodes_stdin);
    tcgetattr (STDOUT_FILENO, &shell_tmodes_stdout);
}

void prompt(){
    pwd(0);
    printf("%s> ",workingDirectory);
}

void resetAttributes(){
    tcsetattr(shell_terminal, TCSANOW, &shell_tmodes_stdin);
    //tcsetattr(STDOUT_FILENO, TCSANOW, &shell_tmodes_stdout);
}
