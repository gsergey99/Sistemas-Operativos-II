//Librerías necesarias para PD
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

#define MAX_PATH 4096



int main(int argc, char *argv[]){

    DIR *direct;
    struct dirent *node;
    struct stat st;
    char name[MAX_PATH];
    const char *dir = argv[1];
    char directory[MAX_PATH];
    if((direct = opendir(dir))==NULL){
        fprintf(stderr,"Error en el directorio %s\n", dir);
        exit(EXIT_FAILURE);
    }

    while ((node = readdir(direct))!= NULL)
    {
        if((strlen(dir)+strlen(node->d_name)+2)>sizeof(name)){
            fprintf(stderr,"Nombre %s/%s demasiado largo\n",dir,node->d_name);
            exit(EXIT_FAILURE);
        }
        sprintf(name, "%s/%s",dir,node->d_name);
        if(strcmp(node->d_name,".") && strcmp(node->d_name,"..")){
            if(stat(name,&st)==-1){
                fprintf(stderr,"Error en %s\n",node->d_name);
                exit(EXIT_FAILURE);
            }
            if(S_ISDIR(st.st_mode )&& strcmp(node->d_name,"modelos")){
                printf("%s\n",node->d_name);
                rmdir(name);
            } 
        }
    }
    
        
    
    
    
    return EXIT_SUCCESS;       
}


    
