/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: TicketMsg.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 18-04-2020
*
*   Porpuse: Definición de la clase TicketMsg con el fin de establecer cada petición de los clientes
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/TicketMsg.h"
#include "../include/colours.h"
#include <iostream>
#include <vector>
TicketMsg::TicketMsg(int id_clients){

    this->id_client = id_clients;
    
        
}
int TicketMsg::get_ID(){
    return this->id_client;
}
int TicketMsg::get_NumTickets(){
    return this->n_tickets;
}
bool TicketMsg::getPayd(){
    return this->payd;
}
void TicketMsg::set_ID(int id){
    this->id_client=id;
}
void TicketMsg::set_NumTickets(int tickets){
    this->n_tickets = tickets;
}
void TicketMsg::generate_ticket_random(){

    this->n_tickets =  (rand()%6)+1;
}
void TicketMsg::setPayd(bool payd){
    this->payd = payd;
}