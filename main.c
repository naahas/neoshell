#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include "commands/show.h"
#include "commands/pwd.h"
#include "commands/cdir.h"
#include "commands/rdir.h"


#define MAXIN 256
#define MAX_PATH 1024
#define MAX_ARGUMENTS 20



// PROTOTYPES
int checkCommands(char * input);
int exit_shell(int argc , char * argv []);




typedef int (*CommandFunc)(int argc , char *argv []);

typedef struct {
    char * current_arg;
    CommandFunc func;
} Command;


//DECLARATION OF COMMAND/FILE
Command commands[] = {
    {"show" , show},
    {"pwd" , pwd},
    {"exit" , exit_shell},
    {"cdir" , cdir},
    {"rdir" , rdir},
    {NULL , NULL}
};








int main(int argc, char *argv[]) {
    printf("---------------------------------------------------- \n");
    printf("--------------- INTERACTIVE SHELL ON --------------- \n");
    printf("---------------------------------------------------- \n");


    char user_input[MAXIN];
    char cwd_buffer[MAX_PATH];
    char *username;


    #ifdef _WIN32
        username = getenv("USERNAME");
    #else
        username = getenv("USER");
    #endif


    while(1) {
       
       // DISPLAY CWD AT THE BEGINNING
        if(getcwd(cwd_buffer , sizeof(cwd_buffer)) != NULL) {
          if(username) printf("\e[1;32m%s\e[0m \e[1;33m%s\e[0m\n", username , cwd_buffer);
          else printf("\e[1;33m%s\e[0m\n", cwd_buffer);
        } 

         printf("$ ");



          if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            break;  
        }


        checkCommands(user_input);

        
    }


    return 0;
}






int checkCommands(char * input) {

    char * final_input[MAX_ARGUMENTS];
    int arg_count = 0;

    const char * separator = " \n";
    char * token = strtok(input , separator);
   

    //EXTRACT INPUT USER ARGUMENTS
    while(token != NULL) {
        final_input[arg_count] = token;
        arg_count ++;
        token = strtok (NULL , separator);
    }



    if(arg_count > 0) {
         for (int i = 0; commands[i].current_arg != NULL; i++) {
           if(strcmp(final_input[0] , commands[i].current_arg) == 0) {
                commands[i].func(arg_count , final_input);

                printf("\n");
                return 1;
           }
        }

       
        printf("\e[1;37mCommande introuvable : %s\n\e[0m", final_input[0]);

    }

    
     printf("\n");
        

    return 0;
}






int exit_shell(int argc , char * argv []) {

    printf("\e[1;31m%s\e[0m  ", "Sortie du Shell..");
    exit(1);

    return 1;
}