#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;
int main(int argc, char *argv[])
{
    ifstream src_fichero;

    src_fichero.open("src/test.txt");

    if (src_fichero.fail()) {
        cerr << "Error opeing a file" << endl;
        src_fichero.close();
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(src_fichero, line))
    {
        cout << line << endl;
    }

    src_fichero.close();
}