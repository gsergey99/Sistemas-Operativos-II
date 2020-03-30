/*********************************************
*   Project: Práctica 2 de Sistemas Operativos II 
*
*   Program name: LineaResultado.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 09-03-2020
*
*   Porpuse: Definición de la clase LineResult con el fin de guardar la información de la palabra encontrada
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "../include/LineaResultado.h"
#include "../include/colours.h"
#include <iostream>

LineResult::LineResult(int thread,int initial_line, int final_line, int found_line,std::string actual_word){

    this->num_thread = thread;
    this->initial_line=initial_line;
    this->final_line=final_line;
    this->found_line=found_line;
    this->actual_word=actual_word;
    
}
int LineResult::get_NumThread(){
    return this->num_thread;
}
int LineResult::get_Initial_Line(){
    return this->initial_line;
}
int LineResult::get_Final_Line(){
    this->final_line;
}
int LineResult::get_Found_Line(){
    return this->found_line;
}
std::string LineResult::get_Actual_Word(){
    return this->actual_word;
}
void LineResult::toString(){
    std::cout <<FYEL("[Hilo: ") << CIAN <<std::to_string(this->num_thread) << RESET << FYEL(" inicio ") << GREEN << std::to_string(this->initial_line) << RESET << FYEL(" - final ") << GREEN << std::to_string(this->final_line) << RESET << FYEL(" ]:: línea ") << VIOLET << std::to_string(this->found_line) << RESET << " "<< this->actual_word << std::endl;
}
void LineResult::set_NumThread(int thread){
    this->num_thread=thread;
}
void LineResult::set_Initial_Line(int initial_line){
    this->initial_line = initial_line;
}
void LineResult::set_Final_Line(int final_line){
    this->final_line=final_line;
}
void LineResult::set_Found_Line(int found_line){
    this->found_line = found_line;
}
void LineResult::set_Actual_Word(std::string acutal_word){
    this->actual_word=actual_word;
}