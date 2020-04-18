/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Client.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 18-04-2020
*
*   Porpuse: Definición de la clase FoodMsg con el fin de establecer cada petición de los clientes
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/FoodMsg.h"
#include "../include/colours.h"
#include <iostream>
#include <vector>
FoodMsg::FoodMsg(int id_clients){

    this->id_client = id_clients;
    
        
}
int FoodMsg::get_ID(){
    return this->id_client;
}
int FoodMsg::get_NumTickets(){
    return this->n_tickets;
}

void FoodMsg::set_ID(int id){
    this->id_client=id;
}
void FoodMsg::set_NumTickets(int tickets){
    this->n_tickets = tickets;
}
void FoodMsg::generate_ticket_random(){

    this->n_tickets =  (rand()%6)+1;

}