/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: ventas_online.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 06-04-2020
*
*   Porpuse: Gestión de procesos para realización paralela de hilos
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/colours.h"
#include "../include/Client.h"

void initialize_environment(int num_clients);
void tickets_request(const int thread_id);
int generate_ticket_random();

std::mutex s_clients;
std::mutex s_wait_queue;
std::mutex s_requst_tickets;
std::condition_variable cv_shift;
int shift = -1;
int cinema[6][12];
int num_seats = 72; /*Indicamos el numero de butacas*/
std::vector <Client> queue_client;

int main(int argc, char *argv[]){

    if(argc!=2){
        
        std::cerr << FRED("[MANAGER] El número de argumentos es incorrecto <número_clientes>.") <<std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::thread> g_clients;/*Cola de espera de entrada al cine de cada uno de los clientes*/
    int num_clients = atoi(argv[1]);

    initialize_environment(num_clients); /*Inicializamos las butacas en la sala de cine y creación de los clientes*/


    /*Creación de solicitudes de clientes*/
    s_wait_queue.lock();
    for (int i =0; i< num_clients;i++){
        g_clients.push_back(std::thread(tickets_request,i));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::unique_lock<std::mutex> lk(s_clients);
    for(int i=0;i<num_clients;i++){
        if(i > 0){
            
            lk.lock();
        }
        shift = queue_client[i].get_ID();
        cv_shift.notify_all();
        lk.unlock();
        s_wait_queue.lock();
    }
    

    /*Esperamos a que finalice cada uno de los clientes*/
    for_each(g_clients.begin(), g_clients.end(),std::mem_fn(&std::thread::join));
    queue_client.clear();
    
    

    return EXIT_SUCCESS;
}
void initialize_environment(int num_clients){

    for (int i = 0;i < 6; i++ ){
        for(int j = 0;j < 12; j++){
            cinema[i][j] = 0;
        }
    }
    for (int i = 0;i < num_clients; i++){
        Client client(i);
        queue_client.push_back(client);
    }
        
}
void tickets_request(const int thread_id){
    int num_tickets = generate_ticket_random();


    std::unique_lock<std::mutex> lk(s_clients);
    std::cout << FYEL("Soy el hilo ") << thread_id << FYEL(" estoy en la cola") << std::endl;

    cv_shift.wait(lk,[thread_id]{return (shift==thread_id);});
    std::cout << FGRN("Soy en hilo ") << thread_id << FGRN(" ,es mi turno, a por la entradas")<<std::endl;
    s_requst_tickets.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    queue_client[thread_id].set_Tickets(num_tickets);
    s_requst_tickets.unlock();
    s_wait_queue.unlock();
}

int generate_ticket_random(){

    return  (rand()%6)+1;

}

