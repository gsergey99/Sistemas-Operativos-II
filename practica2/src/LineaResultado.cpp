#include <fstream>
#include <stdlib.h>
#include "../include/LineaResultado.h"
#include "../include/colours.h"
#include <iostream>

LineResult::LineResult(int hilo,int linea_inicial, int linea_final, int linea_encontrada,std::string palabra_actual,std::string palabra_anterior,std::string palabra_posterior){

    this->num_thread = hilo;
    this->initial_line=linea_inicial;
    this->final_line=linea_final;
    this->found_line=linea_encontrada;
    this->actual_word=palabra_actual;
    this->before_word=palabra_anterior;
    this->next_word=palabra_posterior;

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
std::string LineResult::get_Before_Word(){
    return this->before_word;
}
std::string LineResult::get_Next_Word(){
    return this->next_word;
}
void LineResult::toString(){
    std::cout <<"[Hilo: " << std::to_string(this->num_thread) << " inicio " << std::to_string(this->initial_line) << " - final " << std::to_string(this->final_line) << " ]:: línea " << std::to_string(this->found_line) << " ... " << this->before_word << " "<< this->actual_word << " " << this->next_word<<std::endl;
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
void LineResult::set_Before_Word(std::string before_word){
    this->before_word=before_word;
}
void LineResult::set_Next_Word(std::string next_word){
    this->next_word=next_word;
}