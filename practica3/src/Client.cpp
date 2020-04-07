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

Client::Client(int id){

    this->id = id;    
}
int Client::get_ID(){
    return this->id;
}
int Client::get_Tickets(){
    return this->tickets;
}
void Client::set_ID(int id){
    this->id=id;
}
void Client::set_Tickets(int tickets){
    this->tickets = tickets;
}
