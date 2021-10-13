#include <iostream>
#include "algoritmos.hpp"

using namespace std;

int main(){

  int option;

  while(1){

    cout << endl;
    cout << "========= Menu ============" << endl;
    cout << "1 - Algoritmo Heapsort" << endl;
    cout << "2 - Determinante Iterativo" << endl;
    cout << "3 - Determinate Recursivo" << endl;
    cout << "4 - Salir del programa" << endl;
    cout << "===========================" << endl;
    cout << endl << "Introduce que quieres hacer: ";
    cin >> option;
    cout << endl;

    switch (option) {
      case 1: //Se realiza el algoritmo Heapsort
        ordenacionHeapSort();
      case 2: //Se realiza el determinante rterativo
        determinanteIterativo();
      case 3: //Se realiza el determinate recursivo

      case 4: //Se sale del programa
        return 0;
      default:
        cout << "Esa opcion no es valida" << endl;
    }
  }
}
