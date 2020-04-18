/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: SemCounter.h
*
*   Author: Sergio Jiménez
*
*   Date created: 13-04-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase SemCounter
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/
#include <fstream>
#include <stdlib.h>
#include "colours.h"
#include <vector>
#include <mutex>


#ifndef SEMCOUNTER_H 
#define SEMCOUNTER_H

class SemCounter{
private:
    int value;
    std::mutex mutex_;
    std::mutex mutex_block;

    void block();
    void unblock();

public:
    SemCounter(int value);
    void wait();
    void signal();
    int getValue();
    void setValue(int num);

};
#endif