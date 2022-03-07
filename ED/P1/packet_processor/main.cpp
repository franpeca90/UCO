/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "queue_imp.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{
    Queue<int> cola;

    cout<<"Tamaño de la cola: " << cola.size() << endl;

    if(cola.is_empty()){
        cout<<"Estoy vacia" << endl;
    }

    cola.enque(10);
    
    if(cola.is_empty()){
        cout<<"Estoy vacia" << endl;
    } else {
        cout<<"Me han introducido valores" << endl;
        cout<<"Nuevo tamaño de la cola: " << cola.size() << endl;
    }

    cout<<"Ultimo elemento (Input) " << cola.back() << endl;
    cola.enque(20);
    cout<<"Ultimo elemento (Input) " << cola.back() << endl;
    cola.deque();
    cout<<"Ultimo elemento (Output) " << cola.front() << endl;


    

}
