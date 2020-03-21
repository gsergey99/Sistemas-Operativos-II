#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LineaResultado.h"
#include <string.h>
#include <regex>
#include <vector>
#include <thread>
#include <sstream>
#include <mutex>

using namespace std;

int contar_filas(std::string fichero);
void encontrar_palabra (std::vector<int> intervalo_lineas,std::string fichero, std::string palabra, int num_hilo);
std::vector <vector<int>> ajustar_linea(std::vector<vector<int>> intervalo_lineas, int num_lineas, int num_hilos);
std::mutex semaforo;


int main(int argc, char *argv[])
{
    std::string fichero = argv[1];
    std::string palabra = argv[2];
    int num_hilos = atoi(argv[3]);
    int num_lineas;
    std::vector<vector<int>> intervalo_lineas;
    std::vector<std::thread> vhilos;

    if(argc!=4){
        std::cerr << "El número de argumentos es incorrecto <nombre_fichero> <palabra> <numero_hilos>" <<std::endl;
        exit(EXIT_FAILURE);
    }

    num_lineas = contar_filas(fichero);

    if(num_lineas<=num_hilos){
        std::cerr << "El número de hilos es más grande que el número de líneas" <<std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<vector<int>> aux;
    intervalo_lineas = ajustar_linea(intervalo_lineas,num_lineas,num_hilos);
    /*for ( std::vector<std::vector<int>>::size_type i = 0; i < intervalo_lineas.size(); i++ ){
   for ( std::vector<int>::size_type j = 0; j < intervalo_lineas[i].size(); j++ )
   {
      std::cout << intervalo_lineas[i][j] << ' ';
   }
   std::cout << std::endl;
   }*/
   
    for(int i =0;i<num_hilos;i++){
        vhilos.push_back(std::thread(encontrar_palabra,intervalo_lineas[i],fichero,palabra,i));
    }

    std::for_each(vhilos.begin(),vhilos.end(),std::mem_fn(&std::thread::join));
    /*for(int i =0;i<num_hilos;i++){
        encontrar_palabra(intervalo_lineas[i],fichero,palabra,i);
    } */                                                                                  
}

int contar_filas(std::string fichero){
    
    ifstream src_fichero;
    int num_filas=0;
    std::string line;

    src_fichero.open(fichero); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "Error al abrir el fichero de entrada" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    
    while (getline(src_fichero, line))
    {
        num_filas++;
    }
    src_fichero.close();
    return num_filas;
}

void encontrar_palabra (std::vector<int> intervalo_lineas,std::string fichero, std::string palabra,int num_hilo){
    int ref_linea[2]; //Es un vector que continiene el 0 la linea inicial y el 1 la línea final
    std::vector<LineaResultado> linea_resultado;
    ifstream src_fichero;
    std::string expr_regular = "[¡¿]"+palabra + "[.,:?!]";
    std::regex palabra_comp(expr_regular, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex palabra_sola(palabra, std::regex_constants::ECMAScript | std::regex_constants::icase);
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
    semaforo.lock();
    src_fichero.open(fichero); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "[MANAGER] Error al abrir el fichero de entrada" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    
    if(src_fichero.is_open()){
        while(getline(src_fichero,linea)){
            if(ref_linea[0]<=num_linea && ref_linea[1]>=num_linea){
                if(std::regex_search(linea,palabra_comp) || std::regex_search(linea,palabra_sola)){
                    tupla_palabras = std::regex_replace(linea,palabra_comp,"\e[3m$&\e[O");
                    cout << "LINEA " << tupla_palabras << endl;
                    regex expr_reg_espacio("\\s+");

                    sregex_token_iterator iter(tupla_palabras.begin(), tupla_palabras.end(), expr_reg_espacio,-1);
                    sregex_token_iterator end;
                    vector<string> vector_aux(iter, end);

                    for(int i =0;i<vector_aux.size();i++){
                        
                        if(std::regex_search(vector_aux.at(i),palabra_comp)|| std::regex_search(vector_aux.at(i),palabra_sola)){ // 

                            
                            cout << "Palabra encontrada " << vector_aux.at(i) << endl;
                            palabra_encontrada = vector_aux.at(i);
                            if(vector_aux.at(i)==vector_aux.back()){
                                cout << "Palabra posterior " << "nada" << endl;
                                palabra_posterior = "";
                            }else{
                                cout << "Palabra posterior " << vector_aux.at(i+1) << endl;
                                palabra_posterior = vector_aux.at(i+1);
                            }
                            auto ref_linea_anterior = vector_aux.begin();
                            //cout << "Palabra anterior l" << *ref_linea_anterior << endl;
                            if(vector_aux.at(i)==*ref_linea_anterior){
                                palabra_anterior = "";
                                cout << "Palabra anterior " << palabra_anterior << endl;
                            }else{
                                palabra_anterior = vector_aux.at(i-1);
                                cout << "Palabra anterior " << palabra_anterior << endl;
                            }
                            LineaResultado l_resultado(num_hilo,ref_linea[0],ref_linea[1],num_linea,palabra_encontrada,palabra_anterior,palabra_posterior);
                            
                            linea_resultado.push_back(l_resultado);
                        }
                    }
                }
            }
            num_linea++;
        }
        for (std::vector<LineaResultado>::size_type j = 0; j < linea_resultado.size(); j++ ){
            linea_resultado[j].toString();
        }
   std::cout << std::endl;   
    }
    semaforo.unlock();
    src_fichero.close();
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
            cout << "Inicio de  "<< i <<" en " << inicio_final.at(z) << endl;
        }
        intervalo_lineas.push_back(inicio_final);
        inicio_final.clear();

    }
    return intervalo_lineas;
}