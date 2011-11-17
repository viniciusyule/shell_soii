/* 
 * File:   Process.h, Simula uma classe estática
 * Author: vinicius
 *
 * Created on 19 de Setembro de 2011, 20:01
 */

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
#define _UNISTD_H_
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#define _STDLIB_H_
#endif

struct List_of_Process;

#define MAXARGS 10

typedef struct{
	char *args[MAXARGS*10];
	int ir, or, ar; //Input Redirection, Output Redirection, Append Redirection
	char *file;
	pid_t pid;    
	int status;  
} Job_Object;

typedef struct List_of_Jobs{
    struct List_of_Jobs *next;
    Job_Object * task;
} Jobs;

typedef struct Job_list {
    Jobs *lastJob;
    Jobs *list;
    Jobs *jobIterator;
    pid_t pgid;
    int lancado;
    int size;
    int stdin, stdout;
    struct List_of_Process *parent;
} Process_Object;

typedef struct List_of_Process{
    struct List_of_Process *next;
    Process_Object * process;
    int jid;
} Process;

typedef struct{
    Process *lastProcess;
    Process *list;
    int jid;
    int size;
} Processes;

Jobs listJobs, *listJobsNode;
Processes listProcesses;
Process *listProcessesNode;

//Process_Object process;
int MAXJOBS = 10;

//----------------METHODS DEFINITION---------------//

int addJob(Process_Object *, Job_Object *);

void initProcessObject(Process_Object *);

int addProcess(Process_Object *);

void initProcessList();

Process_Object * getProcess(int);

void rmJobs(Process_Object *);

void rmProcess(int);
