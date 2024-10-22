
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <sys/stat.h>  
#include <errno.h>  
#include <stdbool.h>

#include "show.h"


//PROTOTYPES
int remove_array_duplicate(int argc , char * argv []);


int show(int argc , char *argv []) {

    argc = remove_array_duplicate(argc , argv);


    struct dirent * dir;
    struct stat st;
    
    DIR * d;


    //SHOW WITHOUT ARGUMENTS
    if(argc == 1) {
        d = opendir(".");

        if(d) {
            while((dir = readdir(d)) != NULL) {
                char * cdata = dir -> d_name;

                if(stat(cdata , &st) == 0 && strcmp(cdata , ".") != 0 && strcmp(cdata , "..") != 0) {

                    if(S_ISDIR(st.st_mode))  printf("\e[1;34m%s/\e[0m  ", cdata);
                    else  printf("\e[1;31m%s\e[0m  ", cdata);

                }

            }

            printf("\n");
            closedir(d);
        } else fprintf(stderr , "Erreur dans la récupération du répertoire\n");


    //SHOW WITH ARGUMENTS
    } else {
        for(int i = 1 ; i < argc ; i ++) {
            d = opendir(argv[i]);

            if(d) {
                 if(argc > 2) printf("\e[1;37m%s%s\e[0m  ", argv[i], " ->  \n");

                while((dir = readdir(d)) != NULL) {
                    char * cdata = dir -> d_name;
                    char true_path[1024];

                    snprintf(true_path , sizeof(true_path) , "%s/%s" , argv[i] , cdata);

                    if(stat(true_path , &st) == 0 && strcmp(cdata , ".") != 0 && strcmp(cdata , "..") != 0) {

                        if(S_ISDIR(st.st_mode))  printf("\e[1;34m%s/\e[0m  ", cdata);
                        else  printf("\e[1;31m%s\e[0m  ", cdata);

                    }


                    

                }

                printf("\n");
                closedir(d);
                



            } else printf("Impossible d'acceder au fichier ou dossier : %s\n" , argv[i]);


            if(argc > 2) printf("\n");


        }
    }

    


    return 0;
}





int remove_array_duplicate(int argc , char * argv []) {
    int new_argc = 0;
    char *unique_args[argc]; 

    for (int i = 0; i < argc; i++) {
        bool is_duplicate = false;

        for (int j = 0; j < new_argc; j++) {
            if (strcmp(argv[i], unique_args[j]) == 0) {
                is_duplicate = true;
                break;
            }
        }


        if (!is_duplicate) {
            unique_args[new_argc++] = argv[i];
        }
    }



    for (int i = 0; i < new_argc; i++) {
        argv[i] = unique_args[i];
    }

    return new_argc; 
}