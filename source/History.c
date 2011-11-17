
#ifndef _HISTORY_H_
#include "History.h"
#define _HISTORY_H_
#endif

//Inicia a estrutura do historico
void initHistory(){
    savedCmd.history = savedCmd.lastNode = NULL;
    savedCmd.i = 0;
}

//Adiciona os comandos ao historico
void addToHistory(History_Node * node){

	//node->args = calloc(strlen(command),sizeof(char));
	//strcpy(node->args,command);
	node->i = ++savedCmd.i;	
	node->next = NULL;

	if(savedCmd.history == NULL){
		savedCmd.history = node;
		savedCmd.lastNode = node;		
	}else{
		savedCmd.lastNode->next = node;
		savedCmd.lastNode = savedCmd.lastNode->next;
	}
}

//Exibe o historico
void showHistory(){
	History_Node * iterator;
	for(iterator = savedCmd.history; iterator; iterator = iterator->next){
		printf("[%d] %s\n",iterator->i, iterator->args);
	}
}

//Retorna o comando do historico na posicao index
char *  getHistCommandAt(int index){
	if(index > 0 && index <= savedCmd.i){
		History_Node * iterator;

		for(iterator = savedCmd.history; iterator && (iterator->i != index); iterator = iterator->next){
		}			

		return iterator->args;
	}else{
            return NULL;
	}
}

