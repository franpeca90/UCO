#include "funcionesPrimero.hpp"
#include "funcionesSegundo.hpp"

#include "punto.cpp"
#include "recta.cpp"
#include "serietemporal.cpp"

#include <iostream>

using namespace std; 

int main() {
    int opcion;
    
    cout << "\n   [1] Primer metodo \n   [2] Segundo metodo\n";
    
    cout << "\nIntroduce el número de la opción que deseas realizar: ";
    cin >> opcion;

    switch (opcion){
        case 1:
            cout << "\nSe ha seleccionado el metodo 1\n" << endl;
            metodoPrimero();
        break;
    //---------
        case 2:
            cout << "\nSe ha seleccionado el metodo 2\n" << endl;
            metodoSegundo();

        break;
    //---------
        default: 
            cout << "Error, has introducido un elemento desconocido" << endl;
        break;
    }

    return 0;
}