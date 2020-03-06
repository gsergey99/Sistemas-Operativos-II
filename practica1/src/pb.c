/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II 
*
*   Program name: pb.c
*
*   Author: Sergio Jiménez
*
*   Date created: 25-02-2020
*
*   Porpuse: Copia el fichero .pdf a cada uno de los estudiantes asignados
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


#define NUM_BUFFER 4096
#define PERMISOS 0644
#define PATH_A "/A.pdf"
#define PATH_B "/B.pdf"
#define PATH_C "/C.pdf"
#define PATH "../practica1/Estudiantes"

void copiar_fichero(char *src, char *dest);

int main(int argc, char *argv[]){

    FILE* file_name;
    char buffer[NUM_BUFFER];
    char directorio[NUM_BUFFER],src_directorio[NUM_BUFFER];
    char *dest_directorio;
    
    file_name = fopen(argv[0],"rb");
    if (file_name ==NULL){

        fprintf(stderr,"[PB] Error en la apertura del archivo %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
            if(strlen(buffer)==8){ /*Comprobamos que el valor buffer es el DNI del estudiante*/
                strcpy(directorio,buffer);

            }
            else{
                
                if(strcmp(buffer,"A")==0){
                    
                    dest_directorio= strcat(directorio,PATH_A);
                    sprintf(src_directorio,"%s/%s",PATH,dest_directorio);
                    
                    copiar_fichero("modelos/A.pdf",src_directorio);
                
                }else if (strcmp(buffer,"B")==0)
                {
                    dest_directorio= strcat(directorio,PATH_B);
                    sprintf(src_directorio,"%s/%s",PATH,dest_directorio);

                    copiar_fichero("modelos/B.pdf",src_directorio);

                }else if (strcmp(buffer,"C")==0){    

                    dest_directorio= strcat(directorio,PATH_C);
                    sprintf(src_directorio,"%s/%s",PATH,dest_directorio);

                    copiar_fichero("modelos/C.pdf",src_directorio);
                }

        }
        printf("[PB] Se ha copiado correctamente %s\n",src_directorio);

    }
    fclose(file_name);
    return EXIT_SUCCESS;

}

void copiar_fichero(char *src, char *dest){
    int source_file, dest_file, num_escrito, num_leido;
    unsigned char buffer[NUM_BUFFER];

    source_file = open(src, O_RDONLY);
    dest_file = open(dest, O_CREAT | O_WRONLY,PERMISOS);

    while (1) {
        num_leido = read(source_file, buffer, NUM_BUFFER);
        if (num_leido == -1) {
            fprintf(stderr,"[PB] Error en la copia del fichero de fuente.\n");
            exit(EXIT_FAILURE);
        }
        num_escrito = num_leido;
        if (num_escrito == 0) break;

        num_leido = write(dest_file, buffer, num_escrito);
        if (num_leido == -1) {
            fprintf(stderr,"[PB] Error en la escritura del fichero de salida\n");
            exit(EXIT_FAILURE);
        }
    }

    close(source_file);
    close(dest_file);
}


