

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  
#include <libgen.h>

#include "mv.h"



int mv(int argc , char * argv []) {

     if(argc < 2) {
       fprintf(stderr, "\e[1;31mmv : specifiez au moins 2 arguments (man)\e[0m\n");
       return 1;
    } 

    if(argc == 2) {
        fprintf(stderr, "\e[1;31mmv : argument(s) manquant(s) (man)\e[0m\n");
        return 1;
    }         

    
    const char * dest_path = argv[argc - 1];
    struct stat dest_stat;

    if(stat(dest_path , &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
       for (int i = 1; i < argc - 1; i++) {
            struct stat data_path;

            if(stat(argv[i] , &data_path) == 0) {
                if (S_ISREG(data_path.st_mode) || S_ISDIR(data_path.st_mode)) {
                    char NEODATA[200];
                    snprintf(NEODATA , sizeof(NEODATA) , "%s/%s" ,  dest_path , basename(argv[i]));

                    if(rename(argv[i] , NEODATA) != 0) {
                        fprintf(stderr, "\e[1;31merreur : echec du deplacement de %s vers %s\e[0m\n", argv[i], dest_path);                    
                    }

                } else {
                     fprintf(stderr, "\e[1;31merreur : %s n'est pas un fichier valide\e[0m\n", argv[i]);           
                }
            } else {
                 fprintf(stderr, "\e[1;31merreur : le fichier %s n'existe pas \e[0m\n" , argv[i]);
                 continue;
            }

            
        }

    } else {
        if(argc > 3)  {
            fprintf(stderr, "\e[1;31merreur : %s n'est pas un repertoire (man)\e[0m\n" , dest_path);
            return 1;
        }

        struct stat data_path; 

         if(stat(argv[1] , &data_path) == 0) {
                if (S_ISREG(data_path.st_mode)) {

                     if (stat(dest_path, &dest_stat) == 0) {
                        char confirm;
                        printf("\e[1;37mle fichier %s existe deja et sera ecrase ,poursuivre? \e[0m (o/n) : ", dest_path);
                        scanf(" %c", &confirm);
                        getchar();
                        if (confirm != 'o')  return 1;
                        if(unlink(dest_path) != 0) {
                            fprintf(stderr, "\e[1;31merreur : impossible de supprimer le fichier existant %s : %s\e[0m\n", dest_path, strerror(errno));
                            return 1;
                        }
                    }

                    if(rename(argv[1] , dest_path) != 0) {
                        fprintf(stderr, "\e[1;31merreur : impossible de renommer %s en %s\e[0m\n", argv[1], dest_path);  
                        return 1;                  
                    }
                } else {
                     if(S_ISDIR(data_path.st_mode)) fprintf(stderr, "\e[1;31merreur : impossible de renommer le repertoire %s en %s \e[0m\n", argv[1] , dest_path);  
                     else fprintf(stderr, "\e[1;31merreur : %s n'est pas un nom de fichier existant valide\e[0m\n", argv[1]);             
                }
        } else {
           fprintf(stderr, "\e[1;31merreur : le fichier %s n'existe pas \e[0m\n" , argv[1]);  
        }

    }

    



    

    return 0;
}
