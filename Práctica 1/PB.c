//Librerías necesarias para PB
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

void copy_file(char *src, char *dest);


int main(int argc, char *argv[]){

    FILE* file_name;
    char buffer[NUM_BUFFER];
    char directory[NUM_BUFFER];
    char *dest_directory;

    file_name = fopen(argv[1],"rb");
    if (file_name ==NULL){

        fprintf(stderr,"Error en la apertura del archivo %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
            if(strlen(buffer)==8){
                strcpy(directory,buffer);

            }else{

            if(strcmp(buffer,"A")==0){
                dest_directory= strcat(directory,PATH_A);
                copy_file("modelos/A.pdf",dest_directory);
            }else if (strcmp(buffer,"B")==0)
            {
                dest_directory= strcat(directory,PATH_B);
                copy_file("modelos/B.pdf",dest_directory);

            }else if (strcmp(buffer,"C")==0){    
                
                dest_directory= strcat(directory,PATH_C);
                copy_file("modelos/C.pdf",dest_directory);               

            }

        }
    }
    fclose(file_name);
    return EXIT_SUCCESS;

}

void copy_file(char *src, char *dest){
    int source_file, dest_file, num_write, num_read;
    unsigned char buffer[NUM_BUFFER];


    source_file = open(src, O_RDONLY);
    dest_file = open(dest, O_CREAT | O_WRONLY,PERMISOS);

    while (1) {
        num_read = read(source_file, buffer, NUM_BUFFER);
        if (num_read == -1) {
            fprintf(stderr,"Error en la copia del fichero de fuente.\n");
            exit(EXIT_FAILURE);
        }
        num_write = num_read;
        if (num_write == 0) break;

        num_read = write(dest_file, buffer, num_write);
        if (num_read == -1) {
            fprintf(stderr,"Error en la escritura del fichero de salida\n");
            exit(EXIT_FAILURE);
        }
    }

    close(source_file);
    close(dest_file);
}




