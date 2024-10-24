

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>  

#include "cls.h"


int cls(int argc , char * argv []) {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    

    return 0;

}
