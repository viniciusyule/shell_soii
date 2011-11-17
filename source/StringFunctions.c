#ifndef _STRINGFUNCTIONS_H_
#include "StringFunctions.h"
#define _STRINGFUNCTIONS_H_
#endif

//Funcao que remove espacos em branco do inicio e do final da string
char * trim(char command[]){
    char *p;
    int i = 0;

    p = command;
    while(p && (*p == ' ' || *p == '\n')){
        i++;
        p++;
    }

    p = command + strlen(command) - 1;
    while(p && (*p == ' ' || *p == '\n')){
        p--;
    }

    p++;
    *p = '\0';

    return (command + i);
}
