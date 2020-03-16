#include <fstream>
#include <stdlib.h>
#include "LineaResultado.h"
#include <iostream>

LineaResultado::LineaResultado(int hilo,int linea_inicial, int line_final, int linea_encontrada,std::string palabra_actual,std::string palabra_anterior,std::string palabra_posterior){

    this->num_hilo = hilo;
    this->linea_inicial=linea_inicial;
    this->linea_final=linea_final;
    this->linea_encontrada=linea_encontrada;
    this->palabra_actual=palabra_actual;
    this->palabra_anterior=palabra_anterior;
    this->palabra_posterior=palabra_posterior;

}

int LineaResultado::get_NumHilo(){
    return this->num_hilo;
}
int LineaResultado::get_LineaI(){
    return this->linea_inicial;
}
int LineaResultado::get_LineaF(){
    this->linea_final;
}
int LineaResultado::get_LineaE(){
    return this->linea_encontrada;
}
std::string LineaResultado::get_PalabraAc(){
    return this->palabra_actual;
}
std::string LineaResultado::get_PalabraAn(){
    return this->palabra_anterior;
}
std::string LineaResultado::get_PalabraPo(){
    return this->palabra_posterior;
}
void LineaResultado::toString(){
    std::cout <<"[Hilo: " << std::to_string(this->num_hilo) << "inicio " << std::to_string(this->linea_final) << "-final " << std::to_string(this->linea_final) << "]:: línea " << std::to_string(this->linea_encontrada) << "..." << this->palabra_anterior << this->palabra_actual << this->palabra_posterior<<std::endl;
}
void LineaResultado::set_NumHilo(int hilo){
    this->num_hilo=hilo;
}
void LineaResultado::set_LineaI(int linea_inicial){
    this->linea_inicial = linea_inicial;
}
void LineaResultado::set_LineaF(int linea_final){
    this->linea_final=linea_final;
}
void LineaResultado::set_LineaE(int linea_encontrada){
    this->linea_encontrada = linea_encontrada;
}
void LineaResultado::set_PalabraAc(std::string palabra_actual){
    this->palabra_actual=palabra_actual;
}
void LineaResultado::set_PalabraAn(std::string palabra_anterior){
    this->palabra_anterior=palabra_anterior;
}
void LineaResultado::set_PalabraPos(std::string palabra_posterior){
    this->palabra_posterior=palabra_posterior;
}