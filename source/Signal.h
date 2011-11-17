
#ifndef _SIG_H_
#include <signal.h>
#define _SIG_H_
#endif

#ifndef _PROCESS_H_
#include "Process.h"
#define _PROCESS_H_
#endif

Process_Object * fgProcess = NULL;

void waitProcess( Process_Object * );
void ctrlc(int);
void ctrlz(int);
