//Librerías necesarias 
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


void copy_file(char *src, char *dest);


int main(int argc, char *argv[]){

FILE* file_name;
char buffer[NUM_BUFFER];
char directory[NUM_BUFFER];
char *dest_directory;

file_name = fopen(argv[1],"rb");
if (file_name ==NULL){

    fprintf(stderr,"El archvo no existe \n");
    exit(EXIT_FAILURE);
}

while(fscanf(file_name,"%s",buffer)!=EOF){
        if(strlen(buffer)==8){
            strcpy(directory,buffer);

        }else{

        if(strcmp(buffer,"A")==0){
            dest_directory= strcat(directory,"/A.pdf");
            copy_file("modelos/A.pdf",dest_directory);
        }else if (strcmp(buffer,"B")==0)
        {
            dest_directory= strcat(directory,"/B.pdf");
            copy_file("modelos/B.pdf",dest_directory);

        }else if (strcmp(buffer,"C")==0){    
            
            dest_directory= strcat(directory,"/C.pdf");
            copy_file("modelos/C.pdf",dest_directory);               

        }

    }
}
fclose(file_name);
return EXIT_SUCCESS;

}

void copy_file(char *src, char *dest){
    int src_fd, dst_fd, n, err;
    unsigned char buffer[NUM_BUFFER];


    src_fd = open(src, O_RDONLY);
    dst_fd = open(dest, O_CREAT | O_WRONLY,PERMISOS);

    while (1) {
        err = read(src_fd, buffer, NUM_BUFFER);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }

    close(src_fd);
    close(dst_fd);
}




