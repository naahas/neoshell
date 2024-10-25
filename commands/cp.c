

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <sys/stat.h>  
#include <errno.h>  
#include <stdbool.h>

#include "cp.h"


int recursive_directory_copy(char * source , const char * destpath);
void copy_file(const char * source , const char * destpath);



int cp(int argc , char *argv []) {

     if(argc < 2) {
       fprintf(stderr, "\e[1;31mcp : specifiez au moins 2 arguments (man)\e[0m\n");
       return 1;
     } 

     if(argc == 2) {
        fprintf(stderr, "\e[1;31mcp : argument(s) manquant(s) (man)\e[0m\n");
        return 1;
    }   


    bool check_option = false;
    for(int i = 1 ; i < argc ; i ++) {
        if(strcmp(argv[i] , "-r") == 0) check_option = true;
    }

    if(check_option && argc == 2) {
         printf("\e[1;31merreur:\e[0m specifiez au moins 1 repertoire (man)\n");
        return 1;
    }


    const char * dest_path = argv[argc - 1];
    struct stat dest_stat;

    if(stat(dest_path , &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
         for (int i = 1; i < argc - 1; i++) {

            if (strcmp(argv[i], "-r") == 0) continue;
            struct stat sourcestat;

            if(stat(argv[i] , &sourcestat) != 0) {
                fprintf(stderr, "\e[1;31merreur:\e[0m le fichier ou repetoire '%s' n'existe pas\n", argv[i]);
                continue;
            }


            
            if(S_ISDIR(sourcestat.st_mode)) {
                if(check_option) {
                    char dest_file_path[512];
                    snprintf(dest_file_path , sizeof(dest_file_path) , "%s/%s" , dest_path , argv[i]);
                    if(mkdir(dest_file_path) != 0) {
                        fprintf(stderr , "\e[1;31merreur:\e[0m Impossible de créer le repertoire '%s'\n", argv[i]);
                    }
                    recursive_directory_copy(argv[i] , dest_file_path);
                } else {
                    fprintf(stderr, "\e[1;31merreur:\e[0m '%s' est un repertoire , utilisez -r (man)\n", argv[i]);
                    continue;
                }
            } else {
            
                char dest_file_path[512];
                snprintf(dest_file_path, sizeof(dest_file_path), "%s/%s", dest_path, argv[i]);
                copy_file(argv[i], dest_file_path);

            }
        }
        
    } else {
        fprintf(stderr, "\e[1;31merreur : %s n'est pas un repertoire (man)\e[0m\n" , dest_path);
        return 1;
    }

    

    return 1;
}





void copy_file(const char *source, const char * destpath) {
    FILE *sourcefile = fopen(source, "rb");
    if (sourcefile == NULL) {
        fprintf(stderr, "\e[1;31merreur:\e[0m impossible d'ouvrir le fichier '%s'\n", source);
        return;
    }

    FILE *destfile = fopen(destpath, "wb");
    if (destfile == NULL) {
        fprintf(stderr, "\e[1;31merreur:\e[0m impossible de créer le fichier destination '%s'\n", destpath);
        fclose(sourcefile);
        return;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), sourcefile)) > 0) {
        if (fwrite(buffer, 1, bytes, destfile) != bytes) {
            fprintf(stderr, "\e[1;31merreur:\e[0m problème lors de l'écriture dans '%s'\n", destpath);
            break;
        }
    }

    fclose(sourcefile);
    fclose(destfile);
}





int recursive_directory_copy(char * source , const char * destpath) {

    DIR * dir = opendir(source);

    if(dir == NULL) {
        fprintf(stderr, "\e[1;31merreur:\e[0m impossible d'ouvrir le repertoire '%s'\n", destpath);
        return 1;
    }

    struct dirent * entry;
    while((entry = readdir(dir)) != NULL) {
         if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char source_path[512];
            snprintf(source_path , sizeof(source_path) , "%s/%s" , source , entry -> d_name);

            char dest_path[512];
            snprintf(dest_path , sizeof(dest_path) , "%s/%s" , destpath , entry -> d_name);

            struct stat sourcestat;
            if(stat(source_path , &sourcestat) == 0) {
                if(S_ISDIR((sourcestat.st_mode))) {
                    if (mkdir(dest_path) != 0) {
                        fprintf(stderr , "\e[1;31merreur:\e[0m impossible de creer le répertoire '%s'\n", dest_path);
                    }
                    recursive_directory_copy(source_path , dest_path);
                } else {
                    copy_file(source_path , dest_path);
                }
            } else {
                fprintf(stderr, "\e[1;31merreur:\e[0m obtention des données de '%s' impossible\n", source);
            }





         }
    }


    closedir(dir);
    return 0;
}