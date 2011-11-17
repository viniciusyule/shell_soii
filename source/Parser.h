/* 
 * File:   Parser.h
 * Author: vinicius
 *
 * Created on 4 de Novembro de 2011, 13:44
 */
char * command;
char commandLine[100];
char commandList[10][100];
int line;

Job_Object * newJob;
Job * JobClass = InitJobClass((Job *)malloc(sizeof(Job)));

void parser(){
//Separa os comandos
    command = strtok(commandLine,"|");
    for(line = 0; (command != NULL) && (line < MAXARGS); line++){
            strcpy(commandList[line],trim(command));

            command = strtok(NULL,"|");
    }

    //Pega os argumentos e verifica se ha redirecionamento de i/o
    int i;
    for(i = 0; i < line; i++){
        char *file = NULL, *ptr = NULL;

        newJob = (*(JobClass->create))((Job_Object *)malloc(sizeof(Job_Object)));


        if((file = strstr(commandList[i],">>")) != NULL){
            ptr = file;
            file = trim(file + 1);

            *ptr = '\0';

            (*newJob).ar = 1;
        }else if((file = strstr(commandList[i],">")) != NULL){
            ptr = file;
            file = trim(file + 1);

            *ptr = '\0';

            (*newJob).or = 1;
        }else if((file = strstr(commandList[i],"<")) != NULL){
            ptr = file;
            file = trim(file + 1);

            *ptr = '\0';

            (*newJob).ir = 1;
        }

        (*newJob).file = file;

        if(ptr && file){
            ptr = NULL;
            file = NULL;
        }

        int k, j = 0;
        char *p;
        char arg[100];

        // para cada argumento
        for (k = 0, p = commandList[i]; *p && j < MAXARGS; p += k, j++) {
                        sscanf(p, " %s%n", arg, &k);
                        (*newJob).args[j] = arg;
        }

        (*(process.addJob))(newJob);
    }
}
