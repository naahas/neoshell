
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <stdbool.h>

#include "cdir.h"



int cdir(int argc , char * argv []) {


    if(argc < 2) {
       fprintf(stderr, "\e[1;31mcdir : specifiez au moins 1 argument (man)\e[0m\n");
    } else {
        int status;

        for(int i = 1 ; i < argc ; i ++) {
            char * new_dir = argv[i];
            status = mkdir(new_dir);

            if(status != 0) {
                if(errno  == EEXIST) {
                    printf("\e[1;31mErreur:\e[0m Le repertoire '%s' existe deja\n", new_dir);
                } else printf("\e[1;31mErreur:\e[0m Impossible de créer le repertoire '%s': %s\n", new_dir, strerror(errno));
            }

    
        }

    }

    

    return 0;
}
