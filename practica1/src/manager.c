#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FICHERO "src/estudiantes_p1.text"
#define LOG "src/log.txt"
#define LOG_TEXT1 "******** Log del sistema ********\n"
#define LOG_TEXT2 "Creación de directorios finalizada.\n"
#define LOG_TEXT3 "Copia de modelos de examen, finalizada.\n"
#define LOG_TEXT4 "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada. \n"

pid_t general_pids[3];
FILE *fd_log;

void manejador(int);


int main(int argc, char *argv[]){
    char media[5]={0};
    fd_log = fopen(LOG,"wb");
    if(fd_log == NULL){
        fprintf(stderr,"[MANAGER] Error en la apertura del archivo %s \n",LOG);
        exit(EXIT_FAILURE);
    }
    fprintf(fd_log,"%s",LOG_TEXT1);
    pid_t pid_pa;
    
    pid_pa = fork();
    if(signal(SIGINT,manejador)==SIG_ERR){
        fprintf(stderr,"Error en el paso de la señal");
        return EXIT_FAILURE;
    }
    int status,i, tuberia[2];
    pipe(tuberia);
    
    
    switch (pid_pa)
        {
        case -1:
            printf("[MANAGER] No se ha podido crear el proceso A \n");
            exit(EXIT_FAILURE);
        case 0:
            general_pids[0] = pid_pa;
            printf("[MANAGER] Proceso A creado\n");
            if(execl("./exec/pa",FICHERO,NULL)==-1){
                fprintf(stderr,"[MANAGER] Error en el execl()\n");
                exit(EXIT_FAILURE);
            }
            
        }
    
    waitpid(pid_pa,&status,0);
    if (status == EXIT_FAILURE){
        fprintf(stderr,"Error en la la espera de PA, eliminación de archivos");
        return EXIT_FAILURE;
    }
    fprintf(fd_log,"%s",LOG_TEXT2);
    sleep(2);
    pid_t pids[2];

    for ( i = 0; i < 2; i++)
    {
        pids[i] = fork();
        switch (pids[i])
        {
        case -1:
            printf("[MANAGER] No se ha podido crear el proceso hijo\n");
            exit(EXIT_FAILURE);
        
        case 0:
            if(i == 0){
                general_pids[1] = pids[i];
                printf("[MANAGER] Proceso B creado\n");
                if(execl("./exec/pb",FICHERO,NULL)==-1){
                    fprintf(stderr,"[MANAGER] Error en el execl()\n");
                    exit(EXIT_FAILURE);
                }  
            }else if(i==1){
                general_pids[2] = pids[i];
                printf("[MANAGER] Proceso C creado\n");
                dup2(tuberia[1],STDOUT_FILENO);
                if(execl("./exec/pc",FICHERO,NULL)==-1){
                    fprintf(stderr,"[MANAGER] Error en el execl()\n");
                    exit(EXIT_FAILURE);
                }
            }

        break;
        }
    }
    
    for (i = 0; i < 2; i++)
    {
        pid_t wait_pid = wait(&status);
        if(wait_pid == pids[0]){
            printf("[MANAGER] Esperando al proceso B\n");
            fprintf(fd_log,"%s",LOG_TEXT3);

        }else{
            printf("[MANAGER] Esperando al proceso C \n");
            fprintf(fd_log,"%s",LOG_TEXT4);


        }
    }
    read(tuberia[0],media,sizeof(media));
    fprintf(fd_log,"La nota media de la clase es: %s.\nFIN DEL PROGRAMA. \n", media);
    fclose(fd_log);
    return EXIT_SUCCESS; 
    
}
void manejador(int signal){
    int i,status;
    pid_t pid_pd;
    for (i = 0; i < 3; i++)
    {
        if(general_pids[i]!=0){
        kill(general_pids[i],SIGKILL);
        }
    
    }    
    printf("[MANAGER] Todos los procesos están muertos .\n");
    pid_pd = fork();

    switch (pid_pd)
        {
        case -1:
            printf("[MANAGER] No se ha podido crear el proceso D \n");
            exit(EXIT_FAILURE);
        case 0:
            printf("[MANAGER] Proceso D creado\n");
            if(execl("./exec/pd",FICHERO,NULL)==-1){
                fprintf(stderr,"[MANAGER] Error en el execl()\n");
                exit(EXIT_FAILURE);
            }
            
        }
    
    waitpid(pid_pd,&status,0);
    fprintf(fd_log,"El usuario ha utilizado CTRL+C.\n ******** Finalizacíon del Programa ********");
    fclose(fd_log);
    exit(EXIT_SUCCESS);
}

