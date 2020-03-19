#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LineaResultado.h"
#include <string.h>
#include <regex>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

int contar_filas(std::string fichero);
void encontrar_palabra (std::string fichero, std::string palabra);
void leer_line();
void ajustar_linea(LineaResultado lista_objetos[], int num_lineas, int num_hilos);
    
    
int main(int argc, char *argv[])
{
    std::string fichero = argv[1];
    std::string palabra = argv[2];
    int num_hilos = atoi(argv[3]);
   
    int reference = 0;
    int num_lineas;
    LineaResultado lista_objetos [num_hilos];

    if(argc!=4){
        std::cerr << "El número de argumentos es incorrecto <nombre_fichero> <palabra> <numero_hilos>" <<std::endl;
        exit(EXIT_FAILURE);
    }

    num_lineas = contar_filas(fichero);

    if(num_lineas<=num_hilos){
        std::cerr << "El número de hilos es más grande que el número de líneas" <<std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0;i<num_hilos;i++){
        reference++;
        LineaResultado linea_resultado(reference,0,0,0,palabra,"","");
        lista_objetos[i]=linea_resultado;
    }
    
    ajustar_linea(lista_objetos,num_lineas,num_hilos);  
    encontrar_palabra (fichero, palabra);

    
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

void encontrar_palabra (std::string fichero, std::string palabra){
    
    ifstream src_fichero;
    std::string expr_regular = palabra+ "[.,:?!]";
    std::regex palabra_comp(expr_regular, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::string linea;
    std::string caracter;
    std::string palabra_anterior;
    std::string palabra_posterior;

    src_fichero.open(fichero); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "Error al abrir el fichero de entrada" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    if(src_fichero.is_open()){
        while(getline(src_fichero,linea)){
            if(std::regex_search(linea,palabra_comp)){
                caracter = std::regex_replace(linea,palabra_comp,"\e[3m$&\e[O");
                cout << "Palabra "<< caracter << "\n"<< endl;

            }
        }
    }
    
    src_fichero.close();
    
}
    
void leer_linea(){
    /*ifstream src_fichero;
    char buffer[4096];
    std::string palabra_anterior;
    std::string palabra_posterior;
    int linea =0;

    src_fichero.open("test.txt"); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "Error opeing a file" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    
    while (!src_fichero.eof()) {
        src_fichero.seekg(buffer);
        src_fichero >> caracter;
        cout << caracter << endl;
    
    
  }
    src_fichero.close();*/
}
void ajustar_linea(LineaResultado lista_obeto[], int num_lineas, int num_hilos){

    int cociente_filas, resto_filas;
    int rest_individual=0;
    int unidad = 1;
    resto_filas = num_lineas % num_hilos;
    cociente_filas = num_lineas / num_hilos;
    
    for(int i=0;i<num_hilos;i++){

        if(rest_individual==resto_filas){
            lista_obeto[i].set_LineaE(cociente_filas);
        
        }else{
            
            lista_obeto[i].set_LineaE(cociente_filas+unidad);
            rest_individual++;
            
        }
    }
}