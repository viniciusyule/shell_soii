#ifndef _BUILTIN_H_
#include "Builtin.h"
#define _BUILTIN_H_
#endif


//Funcao que exibe os jobs em execucao
void jobs(){
    Process * iterator;

    for(iterator = listProcesses.list; iterator; iterator = iterator->next){
        printf("[%d] %d\n",iterator->jid,iterator->process->pgid);
    }

}

//Funcao que abri um diretorio que foi passado como parametro
void cd(char **argv){
    if(chdir(argv[1]) < 0){
        switch(errno){
            case EACCES: printf("Acess denied!\n"); break;
            case ENAMETOOLONG: printf("Pathname was too long!\n"); break;
            case ENOENT: printf("Directory not found!\n"); break;
            case ENOTDIR: printf("Pathname does not correspond to a valid directory!\n"); break;
        }
    }
}

//Funcao que mostra o diretorio atual de trabalho
void pwd(int print){
	long size;
	char * buf;

	size = pathconf(".", _PC_PATH_MAX);

	if((buf=(char*)malloc((size_t)size)) != NULL){
                workingDirectory = getcwd(buf, (size_t)size);
                if(print){
                    fprintf(stdout,"%s\n", workingDirectory);
                }
        }
	else{
            printf("Erro desconhecido!\n");
        }

	//free(buf);

}

//Funcao que coloca em background um job que foi pausado por ctrlz
void bg() {

	Process *p = listProcesses.list;

	if (p) {

		for ( p; p; p = p->next ) {

			if (!p->process->lancado) {
				p->process->lancado = 1;
				kill(p->process->pgid,SIGCONT);
			}

		}

	}

}

//Funcao que coloca em foreground um job que foi pausado por ctrlz
void fg(int jid) {

	Process_Object *p = getProcess(jid);

	if (p) {
		if (!p->lancado) {
			fgProcess = p;
			kill(p->pgid,SIGCONT);
			p->lancado = 1;
			waitProcess(p);
		} else perror("Job n√£o esta rodando.\n");
	} else perror("Job nao encontrada.\n");

}

void showArgs (char **args)
{
    int i=0;
    while (args[i] != NULL) {
        printf("%s\n",args[i]);
        i++;
    }
}

//Checa se um comando passado È embutido ou nao
int isBuiltinCommand(char *cmd){
    int jobs = strcmp(cmd,"jobs") == 0;
    int pwd = strcmp(cmd,"pwd") == 0 ;
    int cd = strcmp(cmd,"cd") == 0;
    int echo = strcmp(cmd,"echo") == 0;
    int bg = strcmp(cmd,"bg") == 0;
    int fg = strcmp(cmd,"fg") == 0;

    if(jobs || pwd || cd || echo || bg || fg){
        return 1;
    }else{
        return 0;
    }
}
