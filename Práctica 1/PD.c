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

void remove_files(const char *dir, char *mode, char *files);

int main(int argc, char *argv[]){

    const char *dir = argv[1];
    remove_files(dir,"files","A.pdf");
    remove_files(dir,"files","B.pdf");
    remove_files(dir,"files","C.pdf");
    remove_files(dir,"files","aviso.txt");
    remove_files(dir,"directory","directory");



    
    
    return EXIT_SUCCESS;       
}


void remove_files(const char *dir, char *mode, char *files){
    DIR *direct;
        struct dirent *node;
        struct stat st;
        char name[MAX_PATH];
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
            //printf("%s\n",node->d_name);

            sprintf(name, "%s/%s",dir,node->d_name);
            if(strcmp(node->d_name,".") && strcmp(node->d_name,"..")){
                if(stat(name,&st)==-1){
                    fprintf(stderr,"Error en %s\n",node->d_name);
                    exit(EXIT_FAILURE);
                }
                if(strcmp(mode,"files")==0 && strcmp(node->d_name,files)==0){
                    if(remove(name)==0){
                        printf("%s has sido borrado correctamente\n",node->d_name);
                    }

                }
                if(S_ISDIR(st.st_mode) && strcmp(node->d_name,"modelos")){

                    if(strcmp(mode,"files")==0){
                    remove_files(name,mode,files);
                    }else{
                        if(rmdir(name)==0){
                        printf("%s ha sido borrado correctamente\n",node->d_name);
                        }
                    }
                }
                
            }
        }
}
