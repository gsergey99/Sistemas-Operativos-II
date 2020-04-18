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
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/colours.h"
#include "../include/Client.h"
#include "../include/SemCounter.h"
#include "../include/FoodMsg.h"

void client_request(int id_client);
void initialize_environment(int num_clients);
void assign_seats(int num_tickets, int num_thread);
void request_information(int seat, int num_thread);
void pay_service();
int generate_ticket_random();
void ticket_sale();

/*Semáforo para el hilo reponedor*/
std::mutex stock_manager; 

/*Semáforos para el sistema de pago */
std::mutex pay_lock;
std::mutex pay_wait_lock;
std::mutex cr_secc_payment;


std::mutex s_ticket_sale;
std::mutex s_ticket_request;
std::mutex s_espera_tickets;
std::mutex s_manager;
std::mutex s_request_tickets;

/*Variables de condición*/
std::condition_variable cv_shift;

std::vector<std::thread> g_clients;/*Cola de espera de entrada al cine de cada uno de los clientes*/

std::queue<FoodMsg> queue_tickets;

int shift = -1; 
int cinema[6][12];
int num_seats = 72; 

int main(int argc, char *argv[]){

    if(argc!=2){
        
        std::cerr << FRED("[MANAGER] El número de argumentos es incorrecto <número_clientes>.") <<std::endl;
        exit(EXIT_FAILURE);
    }
    int num_clients = atoi(argv[1]);

    initialize_environment(num_clients); /*Inicializamos las butacas en la sala de cine y creación de los clientes*/

    //std::thread stock_manager(); Hilo para el reponedor

    s_manager.lock();
    s_ticket_request.lock();
    s_espera_tickets.lock();
    //std::thread payment_service (pay_service);
    std::cerr << FRED("[MANAGER] TAQUILLA ABIERTA") <<std::endl;
    std::thread h_taquilla(ticket_sale);

    for (int i =1; i<= num_clients;i++){
        
        g_clients.push_back(std::thread(client_request,i));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    std::unique_lock<std::mutex> lk(s_ticket_sale);
    
    for(int i=1;i<=num_clients;i++){
        
        if(i > 1){
            
            lk.lock();
        }

        shift = i;
        cv_shift.notify_all();
        lk.unlock();
        s_manager.lock();
        
    }
    

    /*Esperamos a que finalice cada uno de los clientes*/
    for_each(g_clients.begin(), g_clients.end(),std::mem_fn(&std::thread::join));
    h_taquilla.join();
    //payment_service.join();

    return EXIT_SUCCESS;
}

void initialize_environment(int num_clients){
    /*Inicializamos el entorno de la solicitud*/
    for (int i = 0;i < 6; i++ ){
        for(int j = 0;j < 12; j++){
            cinema[i][j] = 0;
        }
    }     
}


void client_request(int id_client){
    
    std::cout << FYEL("[CLIENTE ") << id_client << FYEL("] estoy en la cola...") << std::endl;
    std::unique_lock<std::mutex> lk(s_ticket_sale);
    

    cv_shift.wait(lk,[id_client]{return (shift==id_client);});
    std::cout << FGRN("[CLIENTE ") << id_client << FGRN("] es mi turno, voy a por las entradas")<<std::endl;
    lk.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    FoodMsg food_request(id_client);
    food_request.generate_ticket_random();
    queue_tickets.push(food_request);

    s_ticket_request.unlock();
    s_espera_tickets.lock();

    std::cout << FBLU("[CLIENTE ")<<shift<< FBLU("] tengo las entradas y he pagado")<<num_seats<<std::endl;
    s_manager.unlock();


}

void pay_service(){

    while (true){
        //pay_lock.lock();
        
        std::cout << FBLU("[SISTEMA DE PAGO] Cliente ")<<shift<< FBLU(" ha pagado las entradas ")<<num_seats<<std::endl;
        //m2.unlock();
    
        //s_wait_queue.unlock();
        
    }
}
void ticket_sale(){
    int remain_tickets;
    bool with_tickets;
    while (true)
    {
        s_ticket_request.lock();
        FoodMsg msg_food = queue_tickets.front();
        queue_tickets.pop();
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "[TAQUILLA]: Venta de " << msg_food.get_NumTickets() << " tickets a cliente "<< msg_food.get_ID() << "...\n";
        s_request_tickets.lock();

        remain_tickets = num_seats - msg_food.get_NumTickets();
    if(remain_tickets<=0){
        
        with_tickets = false;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }else{
        
        assign_seats(msg_food.get_NumTickets(),msg_food.get_ID());
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        with_tickets = true;
    }

    s_request_tickets.unlock();
    pay_lock.unlock();
        
    s_espera_tickets.unlock();
    }
    
}

void request_information(int seat, int num_thread){
    std::string inf_row;
    std::string inf_column;

    int row = (num_seats-1) /12;
    int column = (num_seats-1) %12;
    
    if(row == 0 || row == 1){ /*Información de las filas*/

        inf_row = " cerca ";
    }else if (row == 2||row == 3){
        
        inf_row = " medio ";
    }else if(row == 4 || row == 5){
        
        inf_row = " lejos ";
    }

    if(column == 0 || column == 1 || column == 2 || column == 3){

        inf_column = " izquierda ";
    }else if(column == 4 || column == 5 || column == 6 || column == 7){

        inf_column = " medio ";
    }else if (column == 8 || column == 9 || column == 10 || column == 11){

        inf_column = " derecha ";
    }

    std::cout << FBLU("SOLICITUD ENTRADAS <")<<num_thread+1<< FBLU(" > < ")<<seat<< FBLU(" > <")<<inf_row<<FBLU("> <") << inf_column<< FBLU(">")<<std::endl;

}
void assign_seats(int num_tickets, int num_thread){
    
    for (int i = 0; i < num_tickets; i++)
    {   
        request_information(num_tickets,num_thread);
        num_seats--;

    }
    
}

