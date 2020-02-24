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
#define PATH "../practica1/Estudiantes"

void write_file_mark(char *dst, int mark);
int calculate_mark(int first_mark);
void calculate_media(int media[],int count);

int main(int argc, char *argv[]){

    FILE* file_name;
    char buffer[NUM_BUFFER], directory[NUM_BUFFER],src_directory[NUM_BUFFER];
    file_name = fopen(argv[0],"rb");
    int first_mark, second_mark, count;
    int media[25];
    count =0;
    int *out;
    out=(int *) malloc(sizeof(int) * 25);


    if(file_name == NULL){
        fprintf(stderr,"Error en la apertura del archivo %s",argv[1]);
        exit(EXIT_FAILURE);
    }

    while(fscanf(file_name,"%s",buffer)!=EOF){
        if(strlen(buffer)==8){
            strcpy(directory,buffer);

        }else if (strlen(buffer)<=2 && (isdigit(buffer[0]) || isdigit(buffer[1]))){
            first_mark = atoi(buffer);
            second_mark = calculate_mark(first_mark);
            sprintf(src_directory,"%s/%s",PATH,directory);
            write_file_mark(src_directory,second_mark);
            out[count] = first_mark;
            count++;

        } 
    }
    fclose(file_name);
    calculate_media(out,count);
    return EXIT_SUCCESS;
}

void write_file_mark(char *dst, int mark){
    
    FILE* dest;
    char *dest_directory;
    char *text = "La nota que debes obtener en este nuevo examen para superar la prueba es ";
    dest_directory = strcat(dst,"/aviso.txt");
    dest = fopen(dest_directory,"wb");
    if(dest == NULL){
        fprintf(stderr,"Error en la apertura del archivo");
        exit(EXIT_FAILURE);
    }
    fprintf(dest,"%s",text);
    fprintf(dest,"%d",mark);
    fclose(dest);
    }


int calculate_mark (int first_mark){
    return 10 - first_mark;
}

void calculate_media(int value[], int count){
    int media =0;
    int i;
    for (i = 0; i < 25; i++)
    {
        media+=value[i];
    }

    printf("%d\n",media/count);
    free(value);

}