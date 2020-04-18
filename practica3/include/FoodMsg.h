/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Client.h
*
*   Author: Sergio Jiménez
*
*   Date created: 18-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase FoodMsg
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"
#include <vector>


#ifndef FOODMSG_H 
#define FOODMSG_H
class FoodMsg{

private:
    int id_client;
    int n_tickets;


public:

    FoodMsg(int id_client); // Constructor de Clase
    int get_ID();
    int get_NumTickets();
    void set_ID(int id);
    void set_NumTickets(int tickets);
    void generate_ticket_random();
};
#endif