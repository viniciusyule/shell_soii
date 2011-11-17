#ifndef _COREFUNCTIONS_H_
#include "CoreFunctions.h"
#define _COREFUNCTIONS_H_
#endif

//Le a linha do teclado e a retorna "limpa" de espacos em branco
char * readLine(){
    char commandLine[100];
    char *trimmedCommandLine;
    
    fgets(commandLine,100,stdin);

    trimmedCommandLine = trim(commandLine);

    if(strcmp(trimmedCommandLine,"exit") == 0){ exit(0); }

    return (trimmedCommandLine);
}

//Interpreta a linha de comando de acordo com a gramatica exigida
void parser(char *commandLine,int historyMode){
    char * command, commandBak[100];
    char commandList[10][100];
    char *file = NULL, *ptr = NULL;
    int line;

    Job_Object * newJob;

    //Verifica se eh background
    if(commandLine[strlen(commandLine) - 1] == '&'){
        commandLine[strlen(commandLine) - 1] = '\0';
        background = 1;
    }

    //Separa os comandos pelo caracter |
    command = strtok(commandLine,"|");
    for(line = 0; (command != NULL) && (line < MAXARGS); line++){
            strcpy(commandList[line],trim(command));

            command = strtok(NULL,"|");
    }

    //Pega os argumentos e verifica se ha redirecionamento de i/o
    int i;
    for(i = 0; i < line; i++){
        
        newJob = (Job_Object *)malloc(sizeof(Job_Object));   
        strcpy(commandBak,commandList[i]);
        if((file = strstr(commandBak,">>")) != NULL){
            ptr = file;
            file = trim(file + 2);

            *ptr = '\0';

            (*newJob).ar = 1;
        }else if((file = strstr(commandBak,">")) != NULL){
            ptr = file;
            file = trim(file + 1);

            *ptr = '\0';

            (*newJob).or = 1;
        }else if((file = strstr(commandBak,"<")) != NULL){
            ptr = file;
            file = trim(file + 1);

            *ptr = '\0';

            (*newJob).ir = 1;
        }

	    if ( file ) {	
		   (*newJob).file = calloc(strlen(file),sizeof(char));
		   strcpy((*newJob).file, file);
	    }

        if(ptr && file){
            ptr = NULL;
            file = NULL;
        }

        int l, a; //l-length, a-arg
        char *p;
        char arg[100];

        //Separa os argumentos de um comando
        for (a = 0, p = trim(commandBak); *p && a < MAXARGS; p += l, a++) {
            sscanf(p, " %s%n", arg, &l);
            (*newJob).args[a] = calloc(l,sizeof(char));
            strcpy((*newJob).args[a],arg);
        }
	    (*newJob).args[a] = NULL;

        //Usado qdo o comando use eh digitado, parte do historico
        if(strcmp((*newJob).args[0],"use") == 0){
            //adicionar verificacao de variavel nao setada
            int index = atoi((*newJob).args[1]);
            char * cmdHist = getHistCommandAt(index);
            char * cmdHistBak;

            cmdHistBak = calloc(strlen(cmdHist),sizeof(char));
            strcpy(cmdHistBak,cmdHist);
            if(cmdHist != NULL){

                if((*newJob).ar){
                    strcat(cmdHistBak," >> ");
                    strcat(cmdHistBak,(*newJob).file);
                }else if((*newJob).or){
                    strcat(cmdHistBak," > ");
                    strcat(cmdHistBak,(*newJob).file);
                }else if((*newJob).ir){
                    strcat(cmdHistBak," < ");
                    strcat(cmdHistBak,(*newJob).file);
                }

                strcpy(commandList[i],cmdHistBak);

                parser(cmdHistBak,1);
            }
            //continue;
        }else{
            addJob(newProcess, newJob);
        }
    }
    
    //Se nao for  historyMode, o comando eh inserido no historico
    if(!historyMode){

        strcpy(commandLine,commandList[0]);
        for(i = 1; i < line; i++){
                strcat(commandLine," | ");
                strcat(commandLine,commandList[i]);
        }

        newHistoryNode = (History_Node *)malloc(sizeof(History_Node));
        (*newHistoryNode).args = calloc(strlen(commandLine),sizeof(char));
        strcpy((*newHistoryNode).args,commandLine);
        
        addToHistory(newHistoryNode);
    }
}

//Executa o processo
int runJob(Process_Object *process, Job_Object job, pid_t pgid, int infile, int outfile, int background){

       /* Set the handling for job control signals back to the default.  */
       signal (SIGQUIT, SIG_DFL);
       signal (SIGTTIN, SIG_DFL);
       signal (SIGTTOU, SIG_DFL);
       signal (SIGCHLD, SIG_DFL);

	pid_t pid;

	pid = getpid ();
	if (pgid == 0) pgid = pid;
	setpgid (pid, pgid);
	//if (!background)
	//tcsetpgrp (shell_terminal, pgid);
	
       if(job.or){
           outfile = open(job.file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
       }else if(job.ar){
	   outfile = open(job.file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
       }else if(job.ir){
	   infile = open(job.file, O_RDONLY, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
       }

       if(outfile < 0){
           perror("open");
	   exit(1);
       }

       /* Set the standard input/output channels of the new process.  */
       if (infile != STDIN_FILENO)
         {
           dup2 (infile, STDIN_FILENO);
           close (infile);
         }
       if (outfile != STDOUT_FILENO)
         {
           dup2 (outfile, STDOUT_FILENO);
           close (outfile);
         }

       /* Exec the new process.  Make sure we exit.  */
	int i = 0;
       if(strcmp(job.args[0],"jobs") == 0){
           jobs();
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"cd") == 0) {
           cd(job.args);
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"pwd") == 0){
           pwd(1);
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"args") == 0){
           showArgs(job.args);
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"history") == 0){
           showHistory();
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"bg") == 0) {
	   bg();
	   rmProcess(process->parent->jid);
       }else if(strcmp(job.args[0],"fg") == 0) {
	   if ( job.args[1] ) {
	   	int a = atoi(job.args[1]);
	   	fg(a);
		rmProcess(process->parent->jid);
	   }
       }else{
           execvp (job.args[0], job.args);
           perror ("execvp");
           exit (1);
       }
}

//Executa o job
int runProcess(Process_Object * process){
    //jobIterator = process->list;
    
    pid_t pid;
    Jobs *jobIterator;
    int pp[2], infile, outfile, builtin;

    infile = process->stdin;
    process->lancado = 1;
    

    for(jobIterator = process->list; jobIterator; jobIterator = jobIterator->next){
        Job_Object job;
        job = *(jobIterator->task);

        //Seta pipes se necessario        
        if(jobIterator->next){
            if(pipe(pp) < 0){
                perror("pipe");
            }
            outfile = pp[1];
        }else{
            outfile = process->stdout;
        }

        builtin = isBuiltinCommand(job.args[0]);
        if(builtin){
            runJob(process,job,process->pgid, infile, outfile, background);
        }else{
	    pid = fork();
            if(pid == 0){
                runJob(process,job,process->pgid, infile, outfile, background);

            }else if(pid < 0){
                perror("fork");
                exit(1);
            }else{
                job.pid = pid;
                if(!process->pgid){
                    process->pgid = pid;
		    if ( !background ) fgProcess = process;
                }
                setpgid(pid,process->pgid);
            }
        }

        if(infile != process->stdin){
            close(infile);
        }
        if(outfile != process->stdout){
            close(outfile);
        }
        infile = pp[0];
    }

    if ( pid > 0 ) {
	    if(!builtin){
		if(background){
		    int statbg;
		    waitpid(pid,&statbg,WNOHANG);
		}else{
		    waitProcess(process);
		    fgProcess = NULL;
		}
	    }

	 background = 0;

    }

}
