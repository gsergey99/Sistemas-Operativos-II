/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Client.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 07-04-2020
*
*   Porpuse: Definición de la clase Client con el fin de establecer cada una de sus solicitudes
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/Client.h"
#include "../include/colours.h"
#include <iostream>
#include <vector>
Client::Client(int id){

    this->id = id;
        
}
int Client::get_ID(){
    return this->id;
}
int Client::get_NumTickets(){
    return this->num_tickets;
}
bool Client::getPayTicket(){
    return this->pay_tickets;
}
bool Client::getPayDrinkFood(){
    this->pay_drink_food;
}
void Client::set_ID(int id){
    this->id=id;
}
void Client::set_NumTickets(int tickets){
    this->num_tickets = tickets;
}
void Client::add_SeatNum(int ticket){
    this->seats.push_back(ticket);
}
void Client::setPayTicket(bool pay){
    this->pay_tickets = pay;
}
void Client::setPayDrinkFood(bool pay){
    this->pay_drink_food = pay;
}
