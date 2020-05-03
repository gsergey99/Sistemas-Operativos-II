/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: PayMsg.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 30-04-2020
*
*   Porpuse: Definición de la clase PayMsg con el fin de establecer cada petición del sistema de pago
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/PayMsg.h"
#include "../include/colours.h"
#include <iostream>
#include <vector>
PayMsg::PayMsg(int id_clients,int site){

    this->id_client = id_clients;
    this->site = site;

        
}
int PayMsg::get_ID(){
    return this->id_client;
}
int PayMsg::get_Site(){
    return this->site;
}

void PayMsg::set_ID(int id){
    this->id_client=id;
}
void PayMsg::set_Site(int site){
    this->site = site;
}
