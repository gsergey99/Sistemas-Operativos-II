/*********************************************
*   Project: Práctica 2 de Sistemas Operativos II 
*
*   Program name: LineaResultado.h
*
*   Author: Sergio Jiménez
*
*   Date created: 09-03-2020
*
*   Porpuse: Librería en la que se define los diferentes métodos de la clase LineResult
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <fstream>
#include <stdlib.h>
#include "colours.h"


#ifndef LINEARESULTADO_H 
#define LINEARESULTADO_H
class LineResult{

private:
    int num_thread;
    int initial_line;
    int final_line;
    int found_line;
    std::string actual_word;
    std::string before_word;
    std::string next_word;

public:

    LineResult(int thread,int initial_line, int final_line, int found_line,std::string actual_word,std::string before_word,std::string next_word); // Constructor de Clase
    int get_NumThread();
    int get_Initial_Line();
    int get_Final_Line();
    int get_Found_Line();
    std::string get_Actual_Word();
    std::string get_Before_Word();
    std::string get_Next_Word();
    void toString();
    void set_NumThread(int thread);
    void set_Initial_Line(int initial_line);
    void set_Final_Line(int final_line);
    void set_Found_Line(int found_line);
    void set_Actual_Word(std::string actual_word);
    void set_Before_Word(std::string before_word);
    void set_Next_Word(std::string next_word);

};
#endif