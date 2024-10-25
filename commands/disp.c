

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <utime.h>

#include "disp.h"



int disp(int argc , char * argv []) {

    if(argc < 2) {
       fprintf(stderr, "\e[1;31mdisp : specifiez au moins 1 fichier (man)\e[0m\n");
       return 1;
     } 

    for(int i = 1; i < argc ; i++ ) {
        struct stat sourcestat;

        if(stat(argv[i] , &sourcestat) == 0 && S_ISDIR(sourcestat.st_mode)) {
            fprintf(stderr, "\e[1;31merreur : '%s' est un repertoire (man)\e[0m\n", argv[i]);
            continue;
        }

        FILE * file = fopen(argv[i] , "r");
        if(!file) {
            fprintf(stderr, "\e[1;31merreur : fichier '%s' introuvable\e[0m\n", argv[i]);
            continue; 
        }

         char buffer[4096];
        size_t bytesread;

        while((bytesread = fread(buffer , 1 , sizeof(buffer) , file)) > 0) {
            fwrite(buffer , 1 , bytesread , stdout);
        }


        fclose(file);
    }


    return 0;
}