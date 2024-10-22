
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <direct.h>
#include <stdbool.h>
#include <dirent.h> 

#include "rdir.h"


int is_dir_empty(const char * path);



int rdir(int argc , char * argv []) {


     if(argc < 2) {
       printf("\e[1;31mrdir : specifiez au moins 1 argument (man)\e[0m\n");
    } else {

        for(int i = 1 ; i < argc ; i ++) {
            char * remove_dir = argv[i];

            if (is_dir_empty(remove_dir) != 0) { 
                if (rmdir(remove_dir) != 0) {
                    printf("\e[1;31mErreur:\e[0m le repertoire n'existe pas : '%s' \n", remove_dir);
                }
            } else {
                 printf("\e[1;31mErreur:\e[0m le repertoire n'est pas vide : '%s' \n", remove_dir);
            }
        

            
    
        }

    }

    return 0;
}




int is_dir_empty(const char * path) {
    struct dirent *entry;
    DIR * d = opendir(path);

    if (d == NULL) { 
        return -1; 
    }


    int ct = 0;
    while((entry = readdir(d)) != NULL) {
         if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            ct++;
            if (ct > 0) {
                closedir(d);
                return 0;
            }
        }
    }

    return 1;
}