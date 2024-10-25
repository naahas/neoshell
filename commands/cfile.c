


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <utime.h>

#include "cfile.h"
#include "show.h"



int cfile(int argc , char * argv []) {

    argc = remove_array_duplicate(argc , argv);
    
    if(argc < 2) {
        fprintf(stderr, "\e[1;31mcfile : specifiez au moins 1 nom de fichier (man)\e[0m\n");
        return 1;
    }

    

    for(int i = 1; i < argc ; i ++) {
        struct stat fstat;

        if(stat(argv[i] , &fstat) == -1) {
            FILE * file = fopen(argv[i] , "w");
            if(file == NULL) {
                fprintf(stderr, "\e[1;31merreur : creation de %s impossible\e[0m\n" , argv[i]);
                return 1;
            }
            fclose(file);
        } else {
            if(utime(argv[i] , NULL) != 0) {
                fprintf(stderr, "\e[1;31merreur : mis à jour de %s impossible\e[0m\n" , argv[i]);
                return 1;
            }
            fprintf(stderr, "\e[1;36m%s : horodatage mis a jour\e[0m\n" , argv[i]);
        }
        
    }



   

    return 0;
}
