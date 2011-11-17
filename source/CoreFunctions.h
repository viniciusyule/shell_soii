/* 
 * File:   coreFunctions.h
 * Author: vinicius
 *
 * Created on 2 de Outubro de 2011, 11:37
 */
#ifndef _FCNTL_H_
#include <fcntl.h>
#define _FCNTL_H_
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
#define _UNISTD_H_
#endif

#ifndef _SYSWAIT_H_
#include <sys/wait.h>
#define _SYSWAIT_H_
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif

#ifndef _BUILTIN_H_
#include "Builtin.h"
#define _BUILTIN_H_
#endif

#ifndef _HISTORY_H_
#include "History.h"
#define _HISTORY_H_
#endif

#ifndef _STRING_H_
#include <string.h>
#define _STRING_H_
#endif

extern shell_terminal;

int **fd, chain, pipeEx;
pid_t *pid;

int background;
int status;
Process_Object * newProcess = NULL;
History_Node * newHistoryNode = NULL;

char * readLine();

void parser(char *,int);

int runJob(Process_Object *, Job_Object, pid_t, int, int, int);

int runProcess(Process_Object *);
