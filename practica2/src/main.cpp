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
void find_word (std::vector<int> intervalo_lineas,std::string fichero, std::string palabra,int num_hilo); 
std::vector <vector<int>> ajustar_linea(std::vector<vector<int>> intervalo_lineas, int num_lineas, int num_hilos);
void mostrar_resultado(); 

std::mutex semaphore;
std::map <int,std::vector<LineaResultado>> resultado;
std::vector<std::thread> vhilos;

int main(int argc, char *argv[])
{
    std::string file = argv[1];
    std::string word = argv[2];
    int num_threads = atoi(argv[3]);

    int num_lines;
    std::vector<vector<int>> intervalo_lineas;

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

    
    intervalo_lineas = ajustar_linea(intervalo_lineas,num_lines,num_threads);
    
    for(int i = 0;i<num_threads;i++){
        
        vhilos.push_back(std::thread(find_word,intervalo_lineas[i],file,word,i));
    }
    
    std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));

    mostrar_resultado();

    return EXIT_SUCCESS;
                                                                                  
}

int line_count(std::string file){
    
    ifstream src_file;
    int num_lines=0;
    std::string line;

    src_file.open(file); //src/test.txt
    if (src_file.fail()) {
        cerr << FRED("Error al abrir el fichero de entrada.")<< endl;
        src_file.close();
        exit(EXIT_FAILURE);
    }
    
    while (getline(src_file, line)){
        num_lines++;
    }
    src_file.close();

    return num_lines;
}

void find_word (std::vector<int> intervalo_lineas,std::string fichero, std::string palabra,int num_hilo){ 
    int ref_linea[2]; //Es un vector que continiene el 0 la linea inicial y el 1 la línea final
    std::vector<LineaResultado> linea_resultado;
    
    ifstream src_fichero;
    
    std::string expr_regular_general = "[¿¡—( ]" + palabra + "[ .—,:;)?!]";
    std::string expr_regular_prefijo = "[¿¡—( ]" + palabra;
    std::string expr_regular_sufijo = palabra + "[ .—,:;)?!]";

    std::regex palabra_expr_regular_g(expr_regular_general,std::regex_constants::ECMAScript | std::regex_constants::icase);  
    std::regex palabra_expr_regular_p(expr_regular_prefijo, std::regex_constants::ECMAScript | std::regex_constants::icase); 
    std::regex palabra_expr_regular_s(expr_regular_sufijo, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex palabra_sola3(palabra, std::regex_constants::ECMAScript | std::regex_constants::icase); 
 
    std::string linea;
    std::string tupla_palabras;
    std::string palabra_anterior;
    std::string palabra_posterior;
    std::string palabra_encontrada;
    
    auto ref_linea_inicial = intervalo_lineas.begin();
    auto ref_linea_final = intervalo_lineas.back();
    ref_linea[0] = *ref_linea_inicial;
    ref_linea[1] = ref_linea_final;
    int num_linea = 0;    
    
    src_fichero.open(fichero); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "[MANAGER] Error al abrir el fichero de entrada" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    
    if(src_fichero.is_open()){
        while(getline(src_fichero,linea)){
            if(ref_linea[0]<=num_linea && ref_linea[1]>=num_linea){

                if(std::regex_search(linea,palabra_expr_regular_g)|| std::regex_search(linea,palabra_sola3) ){  
                    tupla_palabras = std::regex_replace(linea,palabra_expr_regular_g,"\e[3m$&\e[0m");

                    regex expr_reg_espacio("\\s+");
                    sregex_token_iterator iter(tupla_palabras.begin(), tupla_palabras.end(), expr_reg_espacio,-1);
                    sregex_token_iterator end;
                    vector<string> vector_aux(iter, end);
                    
                    for(int i =0;i<vector_aux.size();i++){
                        
                        if(vector_aux.at(i) == palabra||std::regex_search(vector_aux.at(i),palabra_expr_regular_p) || std::regex_search(vector_aux.at(i),palabra_expr_regular_s)) { 

                            palabra_encontrada = vector_aux.at(i);
                            cout<<palabra_encontrada<< " "<<vector_aux.back()<<endl;
                            
                            if(vector_aux.at(i)==vector_aux.back()){

                                palabra_posterior = "";
                            }else{

                                palabra_posterior = vector_aux.at(i+1);
                            }
                            auto ref_linea_anterior = vector_aux.begin();
                            if(vector_aux.at(i)==*ref_linea_anterior){

                                palabra_anterior = "";
                            }else{

                                palabra_anterior = vector_aux.at(i-1);
                            }
                            
                            LineaResultado l_resultado(num_hilo+1,ref_linea[0],ref_linea[1],num_linea,palabra_encontrada,palabra_anterior,palabra_posterior);
                            linea_resultado.push_back(l_resultado);
                        }
                    }
                }
            }
            num_linea++;
        }
        
    }
    std::lock_guard<std::mutex> lk(semaphore);
    resultado.insert(std::pair<int, vector<LineaResultado>>(num_hilo,linea_resultado));

    src_fichero.close();
}

void mostrar_resultado(){ 
    
    for (std::vector<std::vector<LineaResultado>>::size_type i = 0; i < resultado.size(); i++ ){
        for (std::vector<LineaResultado>::size_type j = 0; j < resultado[i].size(); j++ ){
            resultado[i][j].toString();
        }
    }
} 

std::vector<vector<int>> ajustar_linea(std::vector<vector<int>> intervalo_lineas, int num_lineas, int num_hilos){
    
    std::vector<int> inicio_final;
    int linea_objeto[num_hilos];
    int cociente_filas, resto_filas;
    int rest_individual=0;
    int unidad = 1;
    int seek = 0;
    resto_filas = num_lineas % num_hilos;
    cociente_filas = num_lineas / num_hilos;
    
    for(int i=0;i<num_hilos;i++){

        if(rest_individual==resto_filas){
            linea_objeto[i] = cociente_filas;
        
        }else{
            
            linea_objeto[i] = cociente_filas+unidad;
            rest_individual++;
            
        }

        for (int j = 0;j< linea_objeto[i];j++){
            
            inicio_final.push_back(seek);
            seek++;
        }
        for(int z = 0;z<linea_objeto[i];z++){
            //cout << "Inicio de  "<< i <<" en " << inicio_final.at(z) << endl;
        }
        intervalo_lineas.push_back(inicio_final);
        inicio_final.clear();

    }
    return intervalo_lineas;
}