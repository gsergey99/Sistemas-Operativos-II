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


int main(int argc, char *argv[]){

FILE* file_name;
char buffer[255];
int count = 3;

file_name = fopen(argv[1],"rb");
if (file_name ==NULL){

    fprintf(stderr,"El archvo no existe \n");
    exit(EXIT_FAILURE);
}

while(fscanf(file_name,"%s",buffer)!=EOF){
     
    if (count%3==0){
        int res_dir = mkdir((const char*)buffer,0777);
    }
    count++;
    printf("%s\n", buffer);

}
fclose(file_name);
printf("Creación de directorios finalizada.\n");
return EXIT_SUCCESS;

}