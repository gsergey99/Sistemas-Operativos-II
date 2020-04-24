/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Food_DrinkMsg.h
*
*   Author: Sergio Jiménez
*
*   Date created: 23-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase Food_DrinkMsg
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"
#include <vector>


#ifndef FOOD_DRINKMSG_H 
#define FOOD_DRINKMSG_H
class Food_DrinkMsg{

private:
    int id_client;
    int n_drinks;
    int n_popcorn;


public:

    Food_DrinkMsg(int id_client); // Constructor de Clase
    int get_ID();
    int get_NumDrinks();
    int get_NumPopcorn();
    void set_ID(int id);
    void set_NumDrinks(int n_drinks);
    void set_NumPopcorn(int n_popcorn);
    void drink_food_random();
};
#endif