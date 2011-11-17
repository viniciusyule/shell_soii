#ifndef _PROCESS_H_
#include "Process.h"
#define _PROCESS_H_
#endif

//Adiciona processo ao job pai
int addJob(Process_Object * processOwner, Job_Object * job){
    
    if(processOwner->size < MAXJOBS){
        
        Jobs * iterator = processOwner->list;    

        listJobsNode = (Jobs *)malloc(sizeof(Jobs));
        listJobsNode->task = job;
        listJobsNode->next = NULL;
       
        if(iterator == NULL){//Inseri na cabeça da lista
            processOwner->list = listJobsNode;
            processOwner->lastJob = listJobsNode;
            //printf("%s\n",(listNode->task)->args[0]);
        }else{
             (processOwner->lastJob)->next = listJobsNode;
             processOwner->lastJob =  (processOwner->lastJob)->next;
            //printf("%s\n",(listNode->task)->args[0]);
        }
                
         processOwner->size++;
         //printf("%d\n",processOwner->size);
    }else{
        printf("Maximum number of jobs per process achieved!\n");
        exit(0);
    }

}


void initProcessObject(Process_Object * process){
    process->list = NULL;
    process->lastJob = NULL;
    process->stdin = STDIN_FILENO;
    process->stdout = STDOUT_FILENO;
    process->lancado = 0;
}

//Adiciona jobs a lista de jobs
int addProcess(Process_Object * newProcess){
    initProcessObject(newProcess);

    listProcessesNode = (Process *)malloc(sizeof(Process));

    listProcessesNode->next = NULL;
    listProcessesNode->process = newProcess;
    listProcessesNode->jid = ++listProcesses.jid;
    newProcess->parent = listProcessesNode;

    if(listProcesses.list == NULL){
        listProcesses.list = listProcessesNode;
        listProcesses.lastProcess = listProcessesNode;
    }else{
        listProcesses.lastProcess->next = listProcessesNode;
        listProcesses.lastProcess = listProcesses.lastProcess->next;
    }

    listProcesses.size++;
}

void initProcessList(){
    listProcesses.lastProcess = NULL;
    listProcesses.list = NULL;
    listProcesses.jid = 0;
    listProcesses.size = 0;
}

//Retorna o job na posicao jid
Process_Object * getProcess( int jid ) {

	Process *p = listProcesses.list;
	
	if ( jid < listProcesses.jid ) {
		while ( p && p->jid != jid ) p = p->next;
		return p->process;
	} else {
		perror("Job inexistente.\n");
		return NULL;
	}

}

void rmProcess(int jid) {

	Process *p = listProcesses.list;
	Process *aux = p;
	if ( jid <= listProcesses.jid ) {
		if ( listProcesses.size == 1 ) {
			listProcesses.list = NULL;
			listProcesses.lastProcess = NULL;
			p->process->list = NULL;
			p->process->lastJob = NULL;
			p->process->jobIterator = NULL;		
			free(p);
			listProcesses.size = 0;
		}
		else if (listProcesses.size >1 ) {
			if ( p->jid != jid ) {
				while ( p->next && p->next->jid != jid ) p = p->next;
				aux = p;
				p = p->next;
			}
			if (p) {
				if ( p == listProcesses.lastProcess ) listProcesses.lastProcess = aux;
				aux->next = p->next;
				p->process->list = NULL;
				p->process->lastJob = NULL;
				p->process->jobIterator = NULL;				
				free(p);
				listProcesses.size--;
			}
		}
	}

}
