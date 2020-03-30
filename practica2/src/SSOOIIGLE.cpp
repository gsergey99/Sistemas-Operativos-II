/*********************************************
*   Project: Práctica 2 de Sistemas Operativos II 
*
*   Program name: SSOOIIGLE.cpp
*
*   Author: Sergio Jiménez
*
*   Date created: 09-03-2020
*
*   Porpuse: Gestión de procesos para realización paralela de hilos
*
*   Revision History: Reflejado en el repositorio de GitHub
|*********************************************/

#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

#include <stdlib.h>
#include <string.h>

#include "../include/LineaResultado.h"
#include "../include/colours.h"

int line_count(std::string file);
std::vector <std::vector<int>> line_manage(std::vector<std::vector<int>> interval_lines, int num_lines, int num_threads);
bool correct_word(std::string word_to_compare);
char to_lowercase(char c);

void find_word (std::vector<int> interval_lines,std::string file, std::string word,int num_thread); 
void show_result();

std::mutex semaphore;
std::map <int,std::vector<LineResult>> result;
std::vector<std::thread> g_vhilos;

int main(int argc, char *argv[])
{
    if(argc!=4){
        std::cerr << FRED("[MANAGER] El número de argumentos es incorrecto <nombre_fichero> <palabra> <numero_hilos>.") <<std::endl;
        exit(EXIT_FAILURE);
    }

    std::string file = argv[1];
    std::string word = argv[2];
    int num_threads = atoi(argv[3]);

    int num_lines;
    std::vector<std::vector<int>> interval_lines;

    num_lines = line_count(file);

    if(num_lines<num_threads){
        std::cerr << FRED("[MANAGER] El número de hilos es más grande que el número de líneas") <<std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << YELLOW << "WELCOME TO " << RESET << FBLU("SS") << FRED("O") << FYEL("O") << FBLU("II") << FGRN("GL")<<FRED("E")<<  YELLOW << " : " << RESET << std::endl;

    interval_lines = line_manage(interval_lines,num_lines,num_threads);
    std::cout << "[MANAGER] "<< BOLD(FBLU("Creando hilos de hilos")) << std::endl;

    for(int i = 0;i<num_threads;i++){
        
        g_vhilos.push_back(std::thread(find_word,interval_lines[i],file,word,i)); /*Referenciamos los hilos*/
    }

    std::cout << "[MANAGER] "<< BOLD(FBLU("Esperando terminación de hilos")) << std::endl;
    
    std::for_each(g_vhilos.begin(),g_vhilos.end(),std::mem_fn(&std::thread::join)); 

    show_result();

    std::cout << "[MANAGER] "<< BOLD(FBLU("Hilos terminados")) << std::endl;

    return EXIT_SUCCESS;
                                                                                  
}

int line_count(std::string file){ 
    /*Función que cuenta las líneas del fichero seleccionado*/    
    
    std::ifstream src_file;
    int num_lines=0;
    std::string line;

    src_file.open(file);
    if (src_file.fail()) {
        std::cerr << FRED("[MANAGER] Error al abrir el fichero de entrada.")<< std::endl;
        src_file.close();
        exit(EXIT_FAILURE);
    }
    
    while (getline(src_file, line)){
        num_lines++;
    }
    src_file.close();

    return num_lines;
}

void find_word (std::vector<int> interval_lines,std::string file, std::string word,int num_thread){ 
    /*Función de búsqueda de la palabra indicada en la línea de comandos*/

    int ref_line[2]; /*Es un vector que continiene el 0 la linea inicial y el 1 la línea final*/
    std::vector<LineResult> line_result;
    
    std::ifstream src_file;

    std::string expr_regular_general = "\\b" + word + "\\b"; /*Definimos la expresión regular que incluye cualquier signo de puntuación*/
    std::string line;
    std::string tuple_words;
    std::string before_word;
    std::string word_next; 
    std::string found_word;
    std::string aux_word;
    
    std::regex word_expr_regular_g(expr_regular_general,std::regex_constants::ECMAScript | std::regex_constants::icase| std::regex_constants::nosubs);/*Definimos cada una de las expresiones regulares*/  
    std::regex word_alone(word, std::regex_constants::ECMAScript | std::regex_constants::icase); /*Las expresiones tendrán en cuenta las palabras mayúsculas, minúsuculas y que no pertenezca a una palabra derivada*/
        
    auto ref_line_initial = interval_lines.begin();
    auto ref_line_final = interval_lines.back();
    ref_line[0] = *ref_line_initial;
    ref_line[1] = ref_line_final;
    int num_line = 0;
    bool continue_find;
    
    
    src_file.open(file); 
    if (src_file.fail()) {
        std::cerr << FRED("[MANAGER] Error al abrir el fichero de entrada") << std::endl;
        src_file.close();
        exit(EXIT_FAILURE);
    }
    
    if(src_file.is_open()){
        while(getline(src_file,line)){
            if(ref_line[0]<=num_line && ref_line[1]>=num_line){ /*Comparamos que el el hilo está dentro del rango de líneas*/

                if(std::regex_search(line,word_expr_regular_g)) {  /*Buscamos las ocurrrencias en el cada línea del ficheros*/
                    tuple_words = std::regex_replace(line,word_expr_regular_g," ...$1\e[3m$&\e[0m"); 
                    
                    std::regex expr_reg_espacio("\\s+"); /*Separamos las líneas que continen las ocurrencias en palabras*/
                    std::sregex_token_iterator iter(tuple_words.begin(), tuple_words.end(), expr_reg_espacio,-1);
                    std::sregex_token_iterator end;
                    std::vector<std::string> vector_aux(iter, end);

                    for(int i =0;i<vector_aux.size();i++){
                                               
                        aux_word = word;
                        found_word = vector_aux.at(i);
                        std::string aux_found = vector_aux.at(i);

                        for (char &c: aux_found) { // Covertimos la palabra a minúscula
		                    c = to_lowercase(c);
	                    }      
                                                    
                        if(correct_word(aux_found)&&(std::regex_search(vector_aux[i],word_alone)|| (std::regex_search(vector_aux[i],word_expr_regular_g)))){ /*Segundo filtrado para cada una de las palabras*/
                            
                                if(vector_aux.at(i)==vector_aux.back()){ 
                                    
                                    word_next = "";
                                }else{

                                    word_next = vector_aux.at(i+1);
                                }

                                auto ref_before_line = vector_aux.begin();
                                if(vector_aux.at(i)==*ref_before_line){

                                    before_word = "";
                                }else{

                                    before_word = vector_aux.at(i-1);
                                }
                                word_next = " " + word_next + " ..."; /*Insertamos la palabra anterior y posterior a la palabra encontrada*/
                                before_word = " " + before_word + " ";
                                found_word.insert(3,before_word);
                                found_word.insert(found_word.size(), word_next);
                                    
                                LineResult l_resultado(num_thread+1,ref_line[0],ref_line[1],num_line+1,found_word);
                                line_result.push_back(l_resultado);
                        }
                        
                    }
                }
            }
            num_line++;
        }
    }
    std::lock_guard<std::mutex> lk(semaphore);
    result.insert(std::pair<int, std::vector<LineResult>>(num_thread,line_result));

    src_file.close();
}

char to_lowercase(char c){
    /*Función que convierte la palabra a minúscula*/

	if (c >= 'A' && c <= 'Z')
		return c + 32;

	return c;
}

void show_result(){
    /*Función de mostrar el resultado de cada uno de los hilos*/

    std::cout<< "[MANAGER] " << BOLD(FYEL("RESULTADO: ")) << RESET<< std::endl;
    for (std::vector<std::vector<LineResult>>::size_type i = 0; i < result.size(); i++ ){
        for (std::vector<LineResult>::size_type j = 0; j < result[i].size(); j++ ){
            result[i][j].toString();
        }
    }
} 

std::vector<std::vector<int>> line_manage(std::vector<std::vector<int>> interval_lines, int num_lines, int num_threads){
    /*Función para asignar las diferentes líneas a cada uno de los hilos*/
    
    std::vector<int> init_final;
    int line_object[num_threads];
    int quotient_lines, rest_files;
    int rest_individual=0;
    int unit = 1;
    int seek = 0;
    rest_files = num_lines % num_threads;
    quotient_lines = num_lines / num_threads;
    
    for(int i=0;i<num_threads;i++){

        if(rest_individual==rest_files){
            line_object[i] = quotient_lines;
        
        }else{
            
            line_object[i] = quotient_lines+unit;
            rest_individual++;
            
        }

        for (int j = 0;j< line_object[i];j++){
            
            init_final.push_back(seek);
            seek++;
        }
        
        interval_lines.push_back(init_final);
        init_final.clear();

    }
    return interval_lines;
}

bool correct_word(std::string word_to_compare){
    /*Función que comprueba si una palabra está dentro de la expresión regular definida y añadirla a nuestra clase LineResult*/

    bool punctuation = false;
    auto first_character = word_to_compare.begin();
    auto second_character = word_to_compare.begin()+1;    
    
    if(ispunct(*first_character)|| ispunct(*second_character)){
        
        punctuation = true; 
    }

    return punctuation;     
}


    
