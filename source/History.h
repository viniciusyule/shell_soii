#ifndef _STDLIB_H_
#include <stdlib.h>
#define _STDLIB_H_
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#define _STDIO_H_
#endif

#ifndef _STRING_H_
#include <string.h>
#define _STRING_H_
#endif

typedef struct historyArgs{
	int i;
	char *args; //primeiro testando com um vetor normal, dps com a matriz
	struct historyArgs *next;
} History_Node;

typedef struct History_List{
	History_Node *history;
	History_Node *lastNode;
	int i;
} History_List;

History_List savedCmd;

void initHistory();

void addToHistory(History_Node *);

void showHistory();

char *  getHistCommandAt(int);

