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

struct Student{

char DNI[8];
int exam_model;
int mark; 
};


int main(int argc, char *argv[]){

FILE* file_name;
char buffer[255];
int count = 3;
struct Students *data = malloc(sizeof(struct Student));


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
return EXIT_SUCCESS;

}