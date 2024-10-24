
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <stdbool.h>

#include "rfile.h"



int rfile(int argc , char * argv []) {

    if(argc < 2) {
        fprintf(stderr, "\e[1;31mrfile : specifiez au moins 1 argument (man)\e[0m\n");
        return 1;
    }


    const char * path;
    for(int i = 1; i < argc ; i++) {
        path = argv[i];
        struct stat st;

        if(stat(path , &st) != 0) {
            fprintf(stderr, "\e[1;31mErreur : fichier %s introuvable (man)\e[0m\n" , path);
            continue;
        }

        if(S_ISREG(st.st_mode)) {

            char confirm;
            printf("voulez-vous vraiment supprimer le fichier \e[1;37m%s\e[0m ? (o/n) : ", path);
            scanf(" %c", &confirm);
            getchar();
            if (confirm != 'o')  continue;

            if(unlink(path) != 0) fprintf(stderr, "\e[1;31mErreur : impossible de supprimer le fichier %s (man)\e[0m\n" , path);
        } else {
            fprintf(stderr, "\e[1;31mErreur : %s n'est pas un fichier regulier (man)\e[0m\n" , path);
        }
    }
    

    return 0;
}
