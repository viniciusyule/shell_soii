/* 
 * File:   Builtin.h
 * Author: vinicius
 *
 * Created on 8 de Novembro de 2011, 15:35
 */

#ifndef _SYSTYPES_H_
#include <sys/types.h>
#define _SYSTYPES_H_
#endif

#ifndef _SYSSTAT_H_
#include <sys/stat.h>
#define _SYSSTAT_H_
#endif

#ifndef _ERRNO_H_
#include <errno.h>
#define _ERRNO_H_
#endif

#ifndef _FCNTL_H_
#include <fcntl.h>
#define _FCNTL_H_
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
#define _UNISTD_H_
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif

#ifndef _SIGNAL_H_
#include <signal.h>
#define _SIGNAL_H_
#endif

#ifndef _PROCESS_H_
#include "Process.h"
#define _PROCESS_H_
#endif

#ifndef _SIG_H_
#include "Signal.h"
#define _SIG_H_
#endif

char *workingDirectory = NULL;
int workingDirectoryfd;
extern Process_Object * fgProcess;

void jobs();

void cd(char **);

void pwd(int);

void bg();

void fg(int);

void showArgs (char **);

int isBuiltinCommand(char *);
