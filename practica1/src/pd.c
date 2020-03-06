/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II
*
*   Program name: pd.c
*
*   Author: Sergio Jiménez
*
*   Date created: 28-02-2020
*
*   Porpuse: Elimina el repositorio de Estudiantes
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>



int main(int argc, char *argv[]){

    system("rm -rf Estudiantes/");
    printf("[PD] El directorio Estudiantes ha sido borrado.\n");
    
    return EXIT_SUCCESS;       
}

