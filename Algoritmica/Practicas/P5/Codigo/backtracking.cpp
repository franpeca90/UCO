#include "backtracking.hpp"
#include "funcionesComunes.hpp"
#include "ClaseTiempo.cpp"

#include <iostream>
#include <vector>

using namespace std;

void backtracking(bool opcion){

	int n; // Numero de reinas
	cout << "Introduce el numero de reinas: ";
	cin >> n;

	double tiempo;

	// Declaracion de las EDs para mostrar los datos
	vector<vector<int>> matrizSoluciones;

	// Funciones backtracking
	if(opcion == false) { // Si estamos en el caso de backtracking con varia soluciones
		backtrackingNreinas(n, matrizSoluciones);
	} else { // Si estamos en el caso de backtracking con una solucion
		backtrackingNreinas_once(n, matrizSoluciones, tiempo);
	}

	// Mostrar datos
	cout << "\nMostrando resultados:" << endl;
	mostrarSoluciones(matrizSoluciones);

	// Mostramos el tiempo para el caos de que solo busquemos una solucion
	if(opcion == true) {
		cout << "\nSe ha tardado en encontrar la solucion un total de: " << tiempo/1000 << endl;
	}
}


void backtrackingNreinas(int n, vector<vector<int>> &matrizSoluciones){ // Realiza el algoritmo de backtracking encontrando todas las soluciones
	
	// Parte inicial del algoritmo, inicializacion de las variables
	vector<int> x(n); // Vector con la solucion que se va creando, tendra n reinas

	x[0] = 0;
	int k = 0; // Variable que nos permite ir recorriendo el espacio de soluciones

	// Algoritmo de backtracking, tal y como se ha visto en clase
	while( k>=0 ){

		x[k] = x[k] + 1;

		while( (x[k] <= n) && (Lugar(k,x) == false )){ // Comprobamos que la reina puesta sea en una posicion valida
			x[k] = x[k] + 1; // Si es una posicion valida, continuamos
		}

		if( x[k] <= n ){
			
			if( k==n-1 ){ // Si ya hemos puesto todas las fichas...
				matrizSoluciones.push_back(x); // ... añadimos la solucion al conjuto total de soluciones	
			} else { 

				k++;
				x[k] = 0;
			}

		} else { // Si ese camino no conduce a nada correcto, volvemos hacia atras
			k--;
		}
	}
}


void backtrackingNreinas_once(int n, vector<vector<int>> &matrizSoluciones, double &tiempo){ // Realiza el algoritmo de backtracking encontrando una unica soucion y mide el tiempo medio
	Clock temporizador;
	bool encontrado = false;
	// Parte inicial del algoritmo, inicializacion de las variables
	vector<int> x(n); // Vector con la solucion que se va creando, tendra n reinas

	temporizador.start(); // Comenzamos a contar el tiempo
	x[0] = 0;
	int k = 0; // Variable que nos permite ir recorriendo el espacio de soluciones

	// Algoritmo de backtracking, tal y como se ha visto en clase
	while( k>=0 && !encontrado){

		x[k] = x[k] + 1;

		while( (x[k] <= n) && (Lugar(k,x) == false )){ // Comprobamos que la reina puesta sea en una posicion valida
			x[k] = x[k] + 1; // Si es una posicion valida, continuamos
		}

		if( x[k] <= n ){
			
			if( k==n-1 ){ // Si ya hemos puesto todas las fichas...
				matrizSoluciones.push_back(x); // ... añadimos la solucion al conjuto total de soluciones
				encontrado = true; // Si hemos encontrado una solucion, nos salimos de la busqueda de mas soluciones
			} else { 

				k++;
				x[k] = 0;
			}

		} else { // Si ese camino no conduce a nada correcto, volvemos hacia atras
			k--;
		}
	}

	temporizador.stop(); // Paramos el tiempo

	tiempo = temporizador.elapsed(); // Tomamos el tiempo empleado
}
