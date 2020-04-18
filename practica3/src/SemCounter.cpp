/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: SemCounter.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 13-04-2020
*
*   Porpuse: Definición de la clase SemCount con el fin de establecer un semáforo contador
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include "../include/SemCounter.h"


SemCounter::SemCounter(int v): value(v){};

void SemCounter::block(){this->mutex_block.lock();}
void SemCounter::unblock(){this->mutex_block.unlock();}

void SemCounter::wait(){

    mutex_.lock();
    if(--this->value<=0){
        this->mutex_.unlock();
        block();
        this->mutex_.lock();
    }
    mutex_.unlock();
}

void SemCounter::signal(){

    mutex_.lock();
    if(++value<=0){
        unblock();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    mutex_.unlock();
}

int SemCounter::getValue(){
    return this->value;
}
void SemCounter::setValue(int num){
    this->value = num;
}