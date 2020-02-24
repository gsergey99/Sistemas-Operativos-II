#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid_pa;
    pid_pa = fork();
    int status;
    switch (pid_pa)
        {
        case -1:
            printf("No se ha podido crear el proceso hijo \n");
            break;
        case 0:
            printf("Proceso hijo creado\n");
            execl("./PA",argv[1],NULL);
            exit(EXIT_SUCCESS);
        }

    waitpid(pid_pa,&status,0);
    if (status == EXIT_FAILURE){
        fprintf(stderr,"Error en la la espera de PA, eliminación de archivos");
        
    }



    
}

