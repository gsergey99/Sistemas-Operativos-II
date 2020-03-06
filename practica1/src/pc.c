/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II 
*
*   Program name: pc.c
*
*   Author: Sergio Jiménez
*
*   Date created: 25-02-2020
*
*   Porpuse: Calcula nota media de los estudiantes y envía un archivo .txt con la 
*            segunda nota que tienen que sacar para aprobar la asignatura
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
#include <signal.h>

#define NUM_BUFFER 4096
#define PERMISOS 0644
#define PATH "../practica1/Estudiantes"

void escribir_txt(char *dst, int nota);
int calcular_nota(int nota1);
void calcular_media(int notas[],int n_estudiantes);


int main(int argc, char *argv[]){

    FILE* file_name;
    char buffer[NUM_BUFFER], directorio[NUM_BUFFER],src_directorio[NUM_BUFFER];
    int nota1,nota2,n_estudiantes,*notas;
    n_estudiantes=0;
    notas=(int *) malloc(sizeof(int) * 25);
    file_name = fopen(argv[0],"rb");

    if(file_name == NULL){
        fprintf(stderr,"[PC] Error en la apertura del archivo %s",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
        if(strlen(buffer)==8){ /*Comprobamos que el valor buffer es el DNI del estudiante*/
            strcpy(directorio,buffer);

        }else if (strlen(buffer)<=2 && (isdigit(buffer[0]) || isdigit(buffer[1]))){ /*Comprobamos si el buffer es la nota del primer examen*/
            nota1 = atoi(buffer);
            nota2 = calcular_nota(nota1);
            sprintf(src_directorio,"%s/%s",PATH,directorio);
            escribir_txt(src_directorio,nota2);
            notas[n_estudiantes] = nota1;
            n_estudiantes++;

        } 
    }
    fclose(file_name);
    calcular_media(notas,n_estudiantes);
    return EXIT_SUCCESS;
}

void escribir_txt(char *dst, int nota){
    
    FILE* dest_file;
    char *dest_directorio;
    char *text = "La nota que debes obtener en este nuevo examen para superar la prueba es ";
    dest_directorio = strcat(dst,"/aviso.txt");
    dest_file = fopen(dest_directorio,"w");
    if(dest_file == NULL){
        fprintf(stderr,"[PC] Error en la apertura del archivo");
        exit(EXIT_FAILURE);
    }
    fprintf(dest_file,"%s",text);
    fprintf(dest_file,"%d",nota);
    fclose(dest_file);
    }


int calcular_nota(int nota1){
    return 10 - nota1;
}

void calcular_media(int notas[], int n_estudiantes){
    int media=0;
    int i;
    for (i = 0; i < 25; i++)
    {
        media+=notas[i];
    }

    printf("%d\n",media/n_estudiantes);
    free(notas);

}