


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  
#include <errno.h>  

#include "man.h"



int man(int argc , char * argv []) {

    if(argc < 2) {
        fprintf(stderr, "\e[1;37mman use : man [command]\e[0m\n \n");
        fprintf(stderr, "\e[1;37mcommands: \n-> pwd \n-> show \n-> go \n-> cp \n-> mv \n-> cdir \n-> rdir \n-> cfile \n-> rfile \n-> disp \n-> cls \n-> exit \e[0m \n ");
        return 1;
    }

    if(argc > 2)  {
        fprintf(stderr, "\e[1;31merreur : trop d'arguments (man command)\e[0m\n");
        return 1;
    }

    char * command = argv[1];

    if (strcmp(command, "pwd") == 0) {
        printf("\n\e[1;37minfo:\e[0m affiche le chemin du repertoire courant\n");
    } else if (strcmp(command, "show") == 0) {
        printf("\n\e[1;37minfo:\e[0m affiche le contenu d'un ou plusieurs repertoires\n\e[1;37muse :\e[0m show [path1 path2 ...]\n");
     } else if (strcmp(command, "cp") == 0) {
        printf("\n\e[1;37minfo:\e[0m copie le contenu d'un ou plusieurs repertoires ou fichiers \n\e[1;37moptions :\e[0m r \n\e[1;37muse :\e[0m cp [file1 file2 ...  destination] , cp -r [file1 dir1 dir2 file2 ... destination]\n");
     } else if (strcmp(command, "disp") == 0) {
        printf("\n\e[1;37minfo:\e[0m affiche le contenu d'un ou plusieurs fichiers\n\e[1;37muse :\e[0m disp [file1 file2 ...]\n");
    } else if (strcmp(command, "go") == 0) {
        printf("\n\e[1;37minfo:\e[0m se deplace au repertoire specifie\n\e[1;37muse :\e[0m go [path1]\n");
    } else if (strcmp(command, "cdir") == 0) {
        printf("\n\e[1;37minfo:\e[0m cree un ou plusieurs repertoire vide\n\e[1;37muse :\e[0m cdir [dir1 dir2 ...]\n");
    } else if (strcmp(command, "rdir") == 0) {
        printf("\n\e[1;37minfo:\e[0m supprime un ou plusieurs repertoires vide ou recursivement\n\e[1;37moptions :\e[0m r \n\e[1;37muse :\e[0m rdir [dir1 dir2 ...] , rdir -r [dir1 dir2 ...]\n");
    } else if (strcmp(command, "cfile") == 0) {
        printf("\n\e[1;37minfo:\e[0m cree un ou plusieurs fichiers reguliers\n\e[1;37muse :\e[0m cfile [file1 fil2 ...]\n");
    } else if (strcmp(command, "rfile") == 0) {
        printf("\n\e[1;37minfo:\e[0m supprime un ou plusieurs fichiers reguliers\n\e[1;37muse :\e[0m rfile [file1 file2 ...]\n");
    } else if (strcmp(command, "mv") == 0) {
        printf("\n\e[1;37minfo:\e[0m deplace des fichiers/repertoires ou renomme un fichier regulier\n\e[1;37muse :\e[0m mv [namefile1 namefile2] , mv [path1 path2 ... destination]\n");
    } else if (strcmp(command, "cls") == 0) {
        printf("\n\e[1;37minfo:\e[0m efface l'ecran du shell\n");
    } else if (strcmp(command, "exit") == 0) {
        printf("\n\e[1;37minfo:\e[0m ferme le shell\n");
    } else {
        printf("\e[1;31mErreur:\e[0m commande '%s' inconnue\n", command);
    }
    

    return 0;
}
