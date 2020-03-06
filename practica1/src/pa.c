/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II 
*
*   Program name: pa.c
*
*   Author: Sergio Jiménez
*
*   Date created: 26-02-2020
*
*   Porpuse: Crear los directorios de los DNIs correspondientes
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


#define NUM_BUFFER 4096
#define PERMISOS 0777
#define PATH "../practica1/Estudiantes"


int main(int argc, char *argv[]){
    FILE* file_name;
    char buffer[NUM_BUFFER],directorio[NUM_BUFFER];
    int p_dir = mkdir(PATH,PERMISOS); /*Creamos el directorio Estudiantes*/
    
    if (p_dir ==-1){
        fprintf(stderr,"[PA] Error en la creación del directorio <<Estudiantes>>.\n");
        exit(EXIT_FAILURE);
    }

    file_name = fopen(argv[0],"rb");
    if (file_name ==NULL){

        fprintf(stderr,"[PA] Error en la apertura del archivo %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
        
        if (strlen(buffer)==8){ /*Comprobamos que el valor buffer es el DNI del estudiante*/
            sprintf(directorio,"%s/%s",PATH,buffer);
            int res_dir = mkdir(directorio,PERMISOS); /*Creamos el directorio con el nombre de los DNIs*/
            if (res_dir == -1){
                fprintf(stderr,"[PA] Error en la creación de los directorios de los DNIs");
                exit(EXIT_FAILURE);
            }
            printf("[PA] Directorio %s creado correctamente\n",directorio);
        }
    }
    fclose(file_name);
    return EXIT_SUCCESS;
}

