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




void copy_file(char *source, char *destiny);


int main(int argc, char *argv[]){

FILE* file_name;
char buffer[255];
int count = 3;
char model;
char *DNI;

file_name = fopen(argv[1],"rb");
if (file_name ==NULL){

    fprintf(stderr,"El archvo no existe \n");
    exit(EXIT_FAILURE);
}

while(fscanf(file_name,"%s",buffer)!=EOF){
    
        if(strcmp(buffer,"A")==0){
            copy_file("MODELOSEXAMEN/MODELOA.pdf","HOLA/MODELOA.pdf");
        }else if (strcmp(buffer,"B")==0)
        {
            printf("Soy B");

            //copy_file("/MODELOSEXAMEN/MODELOB.pdf","HOLA");

        }else if (strcmp(buffer,"C")==0){    
                
            printf("Soy C");

            //copy_file("/MODELOSEXAMEN/MODELOC.pdf","HOLA")
   
        }
            printf("%s\n", buffer);
}
fclose(file_name);
return EXIT_SUCCESS;


}

void copy_file(char *src, char *dest){
    int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];
    char * src_path, dst_path;

    src_fd = open(src, O_RDONLY);
    dst_fd = open(dest, O_CREAT | O_WRONLY);

    while (1) {
        err = read(src_fd, buffer, 4096);
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



