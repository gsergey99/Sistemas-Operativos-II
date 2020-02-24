
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
#define PATH ".."

int main(int argc, char *argv[]){

    FILE* file_name;
    char buffer[NUM_BUFFER];
    char *directory;

    file_name = fopen(argv[1],"rb");
    if (file_name ==NULL){

        fprintf(stderr,"Error en la apertura del archivo %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
        
        if (strlen(buffer)==8){
            sprintf(directory,"%s/%s",PATH,buffer);
            printf("%s\n",directory);
            int res_dir = mkdir(directory,PERMISOS);
        }

    }
    fclose(file_name);
    printf("Creación de directorios finalizada.\n");
    return EXIT_SUCCESS;

}