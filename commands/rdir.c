
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
int recursive_deletion_directory(const char * path);



int rdir(int argc , char * argv []) {


     if(argc < 2) {
       printf("\e[1;31mrdir : specifiez au moins 1 repertoire (man)\e[0m\n");
    } else {

        bool check_option = false;
        for(int i = 1 ; i < argc ; i ++) {
            if(strcmp(argv[i] , "-r") == 0) check_option = true;
        }

        if(check_option && argc == 2) {
            printf("\e[1;31merreur:\e[0m specifiez au moins 1 repertoire (man)\n");
            return 1;
        }



        for(int i = 1 ; i < argc ; i ++) {
            char * remove_dir = argv[i];

            if (strcmp(remove_dir, "-r") == 0) continue;

            struct stat dirstat;

            if(stat(remove_dir , &dirstat) != 0) {
                fprintf(stderr ,  "\e[1;31merreur:\e[0m le repertoire '%s' n'existe pas \n", remove_dir);
                continue;
            }

            if (!S_ISDIR(dirstat.st_mode)) {
                fprintf(stderr , "\e[1;31merreur:\e[0m '%s' n'est pas un repertoire\n", remove_dir);
                continue;
            }

            
            if (is_dir_empty(remove_dir) != 0) { 
                if (rmdir(remove_dir) != 0) {
                    if(check_option && strcmp(remove_dir , "-r") != 0) printf("\e[1;31mErreur:\e[0m le repertoire n'existe pas : '%s' \n", remove_dir);
                }
            } else {
                if(check_option) {
                    recursive_deletion_directory(remove_dir);
                    if (rmdir(remove_dir) != 0) {
                        printf("\e[1;31mErreur:\e[0m le repertoire n'existe pas : '%s' \n", remove_dir);
                    }
                } else printf("\e[1;31mErreur:\e[0m le repertoire n'est pas vide : '%s' \n", remove_dir);
               
            }
  
    
            
        

            
    
        }

    }

    return 0;
}




int recursive_deletion_directory(const char * path) {

    struct dirent * dir;
    DIR * d;

    d = opendir(path);

     if (d == NULL) {
        printf("\e[1;31mErreur:\e[0m impossible d'ouvrir le répertoire '%s' : %s\n", path, strerror(errno));
        return -1;
    }


    char current_data[512];
    while((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                snprintf(current_data , sizeof(current_data) , "%s/%s" , path , dir -> d_name);

                struct stat data_stat;
                if(stat(current_data , &data_stat) == 0) {
                    if(S_ISDIR(data_stat.st_mode)) {
                        if(is_dir_empty(current_data) != 0) {
                            if (rmdir(current_data) != 0)  printf("\e[1;31merreur:\e[0m le repertoire n'existe pas : '%s' \n", current_data);
                        } else if(recursive_deletion_directory(current_data) != 0) {
                                printf("\e[1;31merreur:\e[0m echec lors de la supression de '%s' \n", current_data);
                        }
                    } else {
                        if(unlink(current_data) != 0) {
                            fprintf(stderr, "\e[1;31merreur : impossible de supprimer le fichier existant %s : %s\e[0m\n", current_data, strerror(errno));
                            return 1;
                        }
                    }
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