#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../include/LineaResultado.h"
#include "../include/colours.h"
#include <string.h>
#include <regex>
#include <map>
#include <vector>
#include <thread>
#include <sstream>
#include <mutex>

using namespace std;


int line_count(std::string file);
void find_word (std::vector<int> interval_lines,std::string file, std::string word,int num_thread); 
std::vector <vector<int>> line_manage(std::vector<vector<int>> interval_lines, int num_lines, int num_threads);
void show_result(); 

std::mutex semaphore;
std::map <int,std::vector<LineResult>> result;
std::vector<std::thread> vhilos;

int main(int argc, char *argv[])
{
    std::string file = argv[1];
    std::string word = argv[2];
    int num_threads = atoi(argv[3]);

    int num_lines;
    std::vector<vector<int>> interval_lines;

    if(argc!=4){
        std::cerr << FRED("[MANAGER] El número de argumentos es incorrecto <nombre_fichero> <palabra> <numero_hilos>.") <<std::endl;
        exit(EXIT_FAILURE);
    }

    num_lines = line_count(file);

    if(num_lines<num_threads){
        std::cerr << FRED("[MANAGER] El número de hilos es más grande que el número de líneas") <<std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "WELCOME TO " << FBLU("SS")<<FRED("O")<<FYEL("O")<<FBLU("II")<< FGRN("GL")<<FRED("E")<<std::endl;

    
    interval_lines = line_manage(interval_lines,num_lines,num_threads);
    
    for(int i = 0;i<num_threads;i++){
        
        vhilos.push_back(std::thread(find_word,interval_lines[i],file,word,i));
    }
    
    std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));

    show_result();

    return EXIT_SUCCESS;
                                                                                  
}

int line_count(std::string file){
    
    ifstream src_file;
    int num_lines=0;
    std::string line;

    src_file.open(file); //src/test.txt
    if (src_file.fail()) {
        cerr << FRED("[MANAGER] Error al abrir el fichero de entrada.")<< endl;
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
    int ref_line[2]; //Es un vector que continiene el 0 la linea inicial y el 1 la línea final
    std::vector<LineResult> line_result;
    
    ifstream src_file;
    
    std::string expr_regular_general = "[¿¡—( ]" + word + "[ .—,:;)?!]";
    std::string expr_regular_prefix = "[¿¡—( ]" + word;
    std::string expr_regular_sufix = word + "[ .—,:;)?!]";

    std::regex palabra_expr_regular_g(expr_regular_general,std::regex_constants::ECMAScript | std::regex_constants::icase);  
    std::regex palabra_expr_regular_p(expr_regular_prefix, std::regex_constants::ECMAScript | std::regex_constants::icase); 
    std::regex palabra_expr_regular_s(expr_regular_sufix, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex palabra_alone(word, std::regex_constants::ECMAScript | std::regex_constants::icase); 
 
    std::string line;
    std::string tuple_words;
    std::string before_word;
    std::string word_next;
    std::string found_word;
    
    auto ref_line_initial = interval_lines.begin();
    auto ref_line_final = interval_lines.back();
    ref_line[0] = *ref_line_initial;
    ref_line[1] = ref_line_final;
    int num_line = 0;    
    
    src_file.open(file); //src/test.txt
    if (src_file.fail()) {
        cerr << FRED("[MANAGER] Error al abrir el fichero de entrada") << endl;
        src_file.close();
        exit(EXIT_FAILURE);
    }
    
    if(src_file.is_open()){
        while(getline(src_file,line)){
            if(ref_line[0]<=num_line && ref_line[1]>=num_line){

                if(std::regex_search(line,palabra_expr_regular_g)|| std::regex_search(line,palabra_alone) ){  
                    tuple_words = std::regex_replace(line,palabra_expr_regular_g,"\e[3m$&\e[0m");

                    regex expr_reg_espacio("\\s+");
                    sregex_token_iterator iter(tuple_words.begin(), tuple_words.end(), expr_reg_espacio,-1);
                    sregex_token_iterator end;
                    vector<string> vector_aux(iter, end);
                    
                    for(int i =0;i<vector_aux.size();i++){
                        
                        if(vector_aux.at(i) == word||std::regex_search(vector_aux.at(i),palabra_expr_regular_p) || std::regex_search(vector_aux.at(i),palabra_expr_regular_s)) { 

                            found_word = vector_aux.at(i);
                            //cout<<palabra_encontrada<< " "<<vector_aux.back()<<endl;
                            
                            if(vector_aux.at(i)==vector_aux.back()){

                                word_next = "";
                            }else{

                                word_next = vector_aux.at(i+1);
                            }
                            auto ref_linea_anterior = vector_aux.begin();
                            if(vector_aux.at(i)==*ref_linea_anterior){

                                before_word = "";
                            }else{

                                before_word = vector_aux.at(i-1);
                            }
                            
                            LineResult l_resultado(num_thread+1,ref_line[0],ref_line[1],num_line+1,found_word,before_word,word_next);
                            line_result.push_back(l_resultado);
                        }
                    }
                }
            }
            num_line++;
        }
        
    }
    std::lock_guard<std::mutex> lk(semaphore);
    result.insert(std::pair<int, vector<LineResult>>(num_thread,line_result));

    src_file.close();
}

void show_result(){ 
    
    for (std::vector<std::vector<LineResult>>::size_type i = 0; i < result.size(); i++ ){
        for (std::vector<LineResult>::size_type j = 0; j < result[i].size(); j++ ){
            result[i][j].toString();
        }
    }
} 

std::vector<vector<int>> line_manage(std::vector<vector<int>> interval_lines, int num_lines, int num_threads){
    
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
        for(int z = 0;z<line_object[i];z++){
            //cout << "Inicio de  "<< i <<" en " << inicio_final.at(z) << endl;
        }
        interval_lines.push_back(init_final);
        init_final.clear();

    }
    return interval_lines;
}