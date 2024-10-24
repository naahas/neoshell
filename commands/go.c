

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <stdbool.h>
#include <unistd.h>

#include "go.h"


#define MAXP 200

int go(int argc , char * argv []) {

    if(argc > 2) {
         printf("\e[1;31mErreur:\e[0m trop d'arguments (man)\n");
         return 1;
    }

   
    static char former_path[MAXP];
    char current_path[MAXP];
    if(getcwd(current_path , sizeof(current_path)) == NULL) {
          printf("\e[1;31mErreur:\e[0m répertoire courant introuvable\n");
    }




     const char * path;

    if(argc < 2) {
        path = getenv("HOME");

        if (path == NULL) {
            printf("\e[1;31mErreur:\e[0m variable HOME non définie\n");
            return 1;
        }

        if(chdir(path) != 0) {
            printf("\e[1;31mErreur:\e[0m impossible d'acceder a \e[1;37m%s\e[0m (man)\n", path);
        }
    } else {
        path = argv[1];

        if(strcmp(path , "-") == 0) {
            if(chdir(former_path) != 0) {
                printf("\e[1;31mErreur:\e[0m impossible d'acceder a \e[1;37m%s\e[0m (man)\n", path);

            }
        } else {
            if(chdir(path) != 0) {
                printf("\e[1;31mErreur:\e[0m impossible d'acceder a \e[1;37m%s\e[0m (man)\n", path);
            }
        }

    }


    strcpy(former_path , current_path);
    former_path[MAXP - 1] = '\0';

    return 0;

}
