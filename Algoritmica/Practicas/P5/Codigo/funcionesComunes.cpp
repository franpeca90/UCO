#include <iostream>
#include <vector>

using namespace std;

bool Lugar(int k, vector<int> &x){
	// Algoritmo que muestra si la posicion de las reinas es valida para la solucion, se añade al algoritmo de clase el control de los movimientos del caballo
	for(int i=0 ; i<k ; i++){
		if( x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k) ){ // Si no se cumplen las reglas de las posiciones, no es valido
			// Comprobamos los movimientos de caballo
				return false;
		}
	}

	return true; // En caso de que se cumplan, devolvemos true
}


void mostrarSoluciones(vector<vector<int>> matrizSoluciones){

	for(int i=0 ; i<matrizSoluciones.size() ; i++){
		cout << "Solucion: " << i+1 << " --> ";
		for(int j=0 ; j<matrizSoluciones[i].size() ; j++){
			cout << matrizSoluciones[i][j] << " ";
		}
		cout << "\n";
	}
}