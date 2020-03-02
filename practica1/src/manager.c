/*********************************************
*   Project: Práctica 1 de Sistemas Operativos II 
*
*   Program name: manager.c
*
*   Author: Sergio Jiménez
*
*   Date created: 27-02-2020
*
*   Porpuse: Gestión de procesos para realización paralela de tareas
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#define FICHERO "src/estudiantes_p1.text"
#define LOG "src/log.txt"
#define NUM_HIJOS 3
 
FILE *file_log;
pid_t g_pids[NUM_HIJOS];

void manejador(int);
void instalar_signal();
void crear_pa();
void crear_pb_pc(int tuberia[]);
void esperar_pb_pc();


int main(int argc, char *argv[]){
    char media[5]={0};
    int status,tuberia[2];
    file_log = fopen(LOG,"wb");
    
    if(file_log == NULL){
        fprintf(stderr,"[MANAGER] Error en la apertura del archivo %s \n",LOG);
        exit(EXIT_FAILURE);
    }
    
    fprintf(file_log,"%s","******** LOG DEL SISTEMA ********\n");
    instalar_signal();

    crear_pa();
    waitpid(g_pids[0],&status,0);

    if (status == EXIT_FAILURE){
        fprintf(stderr,"[MANAGER] Error en la la espera de PA, eliminación de archivos");
        return EXIT_FAILURE;
    }

    fprintf(file_log,"%s","Creación de directorios finalizada.\n");
    sleep(2);
    
    crear_pb_pc(tuberia);
    esperar_pb_pc();
    
    read(tuberia[0],media,sizeof(media));
    fprintf(file_log,"La nota media de la clase es: %s******** FIN DEL PROGRAMA ********\n", media);
    fclose(file_log);
    printf("[MANAGER] Todos los procesos han terminado.\n");
    return EXIT_SUCCESS; 
    
}

void manejador(int signal){
    int i,status;
    pid_t pid_pd;
    for (i = 0; i < NUM_HIJOS; i++)
    {
        if(g_pids[i]!=0){
            kill(g_pids[i],SIGKILL);
                
            
        }
    
    }    
    printf("[MANAGER] Todos los procesos han terminado forzosamente.\n");
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
    fprintf(file_log,"El usuario ha utilizado CTRL+C.\n******** FIN DEL PROGRAMA ********");
    fclose(file_log);
    exit(EXIT_SUCCESS);
}

void instalar_signal(){

    if(signal(SIGINT,manejador)==SIG_ERR){
        fprintf(stderr,"[MANAGER] Error en el paso de la señal");
        exit(EXIT_FAILURE);
    }
}

void crear_pa(){

    g_pids[0] = fork();

    switch (g_pids[0])
        {
        case -1:
            printf("[MANAGER] No se ha podido crear el proceso A \n");
            exit(EXIT_FAILURE);
        case 0:
            printf("[MANAGER] Proceso A creado\n");
            if(execl("./exec/pa",FICHERO,NULL)==-1){
                fprintf(stderr,"[MANAGER] Error en el execl()\n");
                exit(EXIT_FAILURE);
            }
            
        }
}

void crear_pb_pc(int tuberia[]){
    int i;
    pipe(tuberia);

    for (i = 1; i < NUM_HIJOS; i++)
    {
        g_pids[i] = fork();
        switch (g_pids[i])
        {
        case -1:
            printf("[MANAGER] No se ha podido crear el proceso hijo\n");
            exit(EXIT_FAILURE);
        
        case 0:
            if(i == 1){
                printf("[MANAGER] Proceso B creado\n");
                if(execl("./exec/pb",FICHERO,NULL)==-1){
                    fprintf(stderr,"[MANAGER] Error en el execl()\n");
                    exit(EXIT_FAILURE);
                }  
            }else if(i==2){
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
}

void esperar_pb_pc(){
    int i,status;
    pid_t wait_pid;

    for (i = 0; i < 2; i++)
    {
        wait_pid = wait(&status);
        if(wait_pid == g_pids[1]){
            printf("[MANAGER] Proceso B ha terminado\n");
            fprintf(file_log,"%s","Copia de modelos de examen, finalizada.\n");

        }else if (wait_pid == g_pids[2]){
            printf("[MANAGER] Proceso C ha terminado\n");
            fprintf(file_log,"%s","Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada. \n");
        }
    }

}

