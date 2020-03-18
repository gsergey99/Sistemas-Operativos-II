#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "LineaResultado.h"
#include <string.h>
#include <regex>

using namespace std;

int contar_filas(std::string fichero);
void encontrar_palabra (std::string fichero, std::string palabra);
void leer_line();
    
    
int main(int argc, char *argv[])
{
    
    if(argc!=4){
        std::cerr << "El número de argumentos es incorrecto <nombre_fichero> <palabra> <numero_hilos>" <<std::endl;
        exit(EXIT_FAILURE);
    }

    std::string fichero = argv[1];
    std::string palabra = argv[2];
    int num_hilos = atoi(argv[3]);
    int num_filas = contar_filas(fichero);
    encontrar_palabra ("test.txt", "fidelidad");

    
    
    //LineaResultado l(1,2, 3, 4,"hola","adios","std::string palabra_posterior");
    std::cout << num_filas <<std::endl;
    
}

int contar_filas(std::string fichero){
    
    ifstream src_fichero;
    int num_filas=0;
    std::string line;

    src_fichero.open(fichero); //src/test.txt
    if (src_fichero.fail()) {
        cerr << "Error opeing a file" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    
    while (getline(src_fichero, line))
    {
        //std::cout << line << std::endl;
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
                cout << "Palabra "<< caracter << endl;

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