#include "quicksort.hpp"
#include "determinanteIterativo.hpp"
#include "determinanteRecursivo.hpp"

#include <iostream>

using namespace std; 

int main() {

    cout << "\nIntroduce el número de la opción que deseas realizar" << endl;
    cout << "   [1] Quick sort \n   [2] Determinante iterativo \n   [3] Determinante recursivo\n\n";
    
    int opcion;
    cin >> opcion;

    switch (opcion){
        case 1:
            ordenacionQuickSort();
            cout << "Quicksort" << endl;
        break;
    //---------
        case 2:
            determinanteIterativo();
            cout << "Determinante iterativo" << endl;
        break;
    //---------
        case 3:
            determinanteRecursivo();
            cout << "Determinante recursivo" << endl;
        break;
    //---------
        default: 
            cout << "Error, has introducido un elemento desconocido" << endl;
        break;
    }

    return 0;
}