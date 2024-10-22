


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pwd.h"


#define MAX_PATH 1024



int pwd(int argc , char * argv []) {

    char cwd_buffer[MAX_PATH];

    if(getcwd(cwd_buffer , sizeof(cwd_buffer)) != NULL) {
       printf("\e[1;37m%s\e[0m\n", cwd_buffer);
    } 

    return 0;
}


