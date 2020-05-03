/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: PayMsg.h
*
*   Author: Sergio Jiménez
*
*   Date created: 30-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase PayMsg
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"
#include <vector>
#include <string>


#ifndef PAYMSG_H 
#define PAYMSG_H
class PayMsg{

private:
    int id_client;
    int site;


public:

    PayMsg(int id_client,int site); // Constructor de Clase
    int get_ID();
    int get_Site();
    void set_ID(int id);
    void set_Site(int site);
    
};
#endif