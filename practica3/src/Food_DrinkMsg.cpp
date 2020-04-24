/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: Food_DrinkMsg.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 23-04-2020
*
*   Porpuse: Definición de la clase Food_DrinkMsg con el fin de establecer cada petición de los clientes
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/Food_DrinkMsg.h"
#include "../include/colours.h"
#include <iostream>
#include <vector>
Food_DrinkMsg::Food_DrinkMsg(int id_clients){

    this->id_client = id_clients;
    
        
}
int Food_DrinkMsg::get_ID(){
    return this->id_client;
}
int Food_DrinkMsg::get_NumDrinks(){
    return this->n_drinks;
}
int Food_DrinkMsg::get_NumPopcorn(){
    return this->n_popcorn;
}
void Food_DrinkMsg::set_ID(int id){
    this->id_client=id;
}
void Food_DrinkMsg::set_NumDrinks(int n_drinks){
    this->n_drinks = n_drinks;
}
void Food_DrinkMsg::set_NumPopcorn(int n_popcorn){
    this->n_popcorn = n_popcorn;
}
void Food_DrinkMsg::drink_food_random(){

    this->n_drinks =  (rand()%6)+1;
    this->n_popcorn =  (rand()%6)+1;

}