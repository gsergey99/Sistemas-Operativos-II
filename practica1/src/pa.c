
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#define NUM_BUFFER 4096
#define PERMISOS 0777
#define PATH "../practica1/Estudiantes"

void manejador(int signo);



int main(int argc, char *argv[]){
    FILE* file_name;
    char buffer[NUM_BUFFER],directory[NUM_BUFFER];
    int p_dir =mkdir(PATH,PERMISOS);
    file_name = fopen(argv[0],"rb");
    signal(SIGINT,manejador);
    if (file_name ==NULL){

        fprintf(stderr,"Error en la apertura del archivo %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
        
        if (strlen(buffer)==8){
            sprintf(directory,"%s/%s",PATH,buffer);
            int res_dir = mkdir(directory,PERMISOS);
            printf("%s \n",directory);
        }

    }
    fclose(file_name);
    return EXIT_SUCCESS;

}
void manejador(int signo){

    printf("[PA %d] Todos los procesos están muertos .\n",getpid());
    
}
