#include "quicksort.hpp"
#include "determinanteIterativo.hpp"
#include "determinanteRecursivo.hpp"

#include <iostream>

using namespace std; 

int main() {
    int opcion;
    
    cout << "\n   [1] Quick sort \n   [2] Determinante iterativo \n   [3] Determinante recursivo\n";
    
    cout << "\nIntroduce el número de la opción que deseas realizar: ";
    cin >> opcion;

    switch (opcion){
        case 1:
            cout << "\nSe ha seleccionado el metodo de ordenamiento burbuja\n" << endl;
            ordenacionQuickSort();
        break;
    //---------
        case 2:
            cout << "\nSe ha seleccionado el metodo del determinante iterativo\n" << endl;
            determinanteIterativo();

        break;
    //---------
        case 3:
            cout << "\nSe ha seleccionado el metodo del determinante recursivo\n" << endl;
            determinanteRecursivo();
        break;
    //---------
        default: 
            cout << "Error, has introducido un elemento desconocido" << endl;
        break;
    }

    return 0;
}