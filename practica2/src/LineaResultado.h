#include <fstream>
#include <stdlib.h>


#ifndef LINEARESULTADO_H 
#define LINEARESULTADO_H
class LineaResultado{

private:
    int num_hilo;
    int linea_inicial;
    int linea_final;
    int linea_encontrada;
    std::string palabra_actual;
    std::string palabra_anterior;
    std::string palabra_posterior;

public:

    LineaResultado(int hilo,int linea_inicial, int line_final, int linea_encontrada,std::string palabra_actual,std::string palabra_anterior,std::string palabra_posterior); // Constructor de Clase
    int get_NumHilo();
    int get_LineaI();
    int get_LineaF();
    int get_LineaE();
    std::string get_PalabraAc();
    std::string get_PalabraAn();
    std::string get_PalabraPo();
    void toString();
    void set_NumHilo(int hilo);
    void set_LineaI(int linea_inicial);
    void set_LineaF(int line_final);
    void set_LineaE(int linea_encontrada);
    void set_PalabraAc(std::string palabra_actual);
    void set_PalabraAn(std::string palabra_anterior);
    void set_PalabraPos(std::string palabra_posterior);

};
#endif