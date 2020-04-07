/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Client.h
*
*   Author: Sergio Jiménez
*
*   Date created: 07-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase Client
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"


#ifndef CLIENT_H 
#define CLIENT_H
class Client{

private:
    int id;
    int tickets;

public:

    Client(int id); // Constructor de Clase
    int get_ID();
    int get_Tickets();
    void set_ID(int id);
    void set_Tickets(int tickets);
};
#endif