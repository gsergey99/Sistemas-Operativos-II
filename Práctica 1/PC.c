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

void write_file_mark(char *dst, int mark);
int calculate_mark(int first_mark);

int main(int argc, char *argv[]){

FILE* file_name;
char buffer[NUM_BUFFER], directory[NUM_BUFFER];
file_name = fopen(argv[1],"rb");
int first_mark, second_mark;

if(file_name == NULL){
    fprintf(stderr,"Error en la apertura del archivo");
    exit(EXIT_FAILURE);
}

while(fscanf(file_name,"%s",buffer)!=EOF){
    if(strlen(buffer)==8){
        strcpy(directory,buffer);

    }else if (strlen(buffer)==1 && isdigit(buffer[0])){
        first_mark = atoi(buffer);
        second_mark = calculate_mark(first_mark);
        write_file_mark(directory,second_mark);
    } 
}
fclose(file_name);
return EXIT_SUCCESS;
}

void write_file_mark(char *dst, int mark){
    
    FILE* dest;
    char *dest_directory;
    char *text = "La nota que debes obtener en este nuevo examen para superar la prueba es ";
    dest_directory = strcat(dst,"/aviso.txt");
    dest = fopen(dest_directory,"w");
    if(dest == NULL){
        fprintf(stderr,"Error en la apertura del archivo");
        exit(EXIT_FAILURE);
    }
    fprintf(dest,"%s",text);
    fprintf(dest,"%d",mark);
    fclose(dest);
    }


int calculate_mark (int first_mark){

    return 10-first_mark;

}