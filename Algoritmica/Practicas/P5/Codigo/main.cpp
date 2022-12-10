#include <iostream>

#include "backtracking.hpp"
#include "lasVegas.hpp"
#include "poda.hpp"
#include "montecarlo.hpp"

using namespace std; 

int main() {
    int opcion = 1;
    
    while (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4 || opcion == 5){
        
        cout << "\n\n\n|> Inicio del programa\n";
        cout << "\n   [1] Algoritmo de Backtracking \n   [2] Algoritmo de Backtracking 1 solucion \n   [3] Algoritmo de Las Vegas \n   [4] Algoritmo de poda \n   [5] Algoritmo de Montecarlo \n\n   [Otro cualquiera] Salir del programa \n";
        
        cout << "\nIntroduce el número de la opción que deseas realizar: ";
        cin >> opcion;

        switch (opcion){
            case 1:
                cout << "\nSe ha seleccionado el algoritmo Backtracking\n" << endl;
                backtracking(false);
            break;
        //---------
            case 2:
                cout << "\nSe ha seleccionado el algoritmo Backtracking 1 solucion\n" << endl;
                backtracking(true);

            break;
        //---------
            case 3:
                cout << "\nSe ha seleccionado el algoritmo Las Vegas\n" << endl;
                lasVegas();

            break;
        //---------
            case 4:
                cout << "\nSe ha seleccionado el algoritmo de Poda\n" << endl;
                poda();

            break;
        //---------
            case 5:
                cout << "\nSe ha seleccionado el algoritmo de Montecarlo\n" << endl;
                montecarlo();
            break;
        //---------
            default: 
                cout << "Finalizando el programa..." << endl;
            break;
        }
    }

    return 0;
}