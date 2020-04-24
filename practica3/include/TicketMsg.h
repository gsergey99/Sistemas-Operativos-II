/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: TicketMsg.h
*
*   Author: Sergio Jiménez
*
*   Date created: 18-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase TicketMsg
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"
#include <vector>


#ifndef TICKETMSG_H 
#define TICKETMSG_H
class TicketMsg{

private:
    int id_client;
    int n_tickets;
    bool payd;


public:

    TicketMsg(int id_client); // Constructor de Clase
    int get_ID();
    int get_NumTickets();
    bool getPayd();
    void set_ID(int id);
    void set_NumTickets(int tickets);
    void generate_ticket_random();
    void setPayd(bool payd);
    
};
#endif