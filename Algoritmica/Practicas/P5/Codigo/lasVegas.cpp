#include "lasVegas.hpp"
#include "funcionesComunes.hpp"
#include "ClaseTiempo.cpp"

//#include <iostream> No necesarios, ya incluidos
//#include <vector>


using namespace std;

void lasVegas(){

	cout << "Metodo principal de Las Vegas" << endl;

	double tiempo;
	
	int n; // Numero de reinas
	int intentos = 0;
	
	vector<int> vectorSolucion; // ED que contendra la solucion
	
	bool exito = false;
	
	cout << "Introduce el numero de reinas: ";
	cin >> n;
	
	while(!exito){
		// Llamada al algoritmo
		lasVegasNreinas(n, vectorSolucion, exito, tiempo);
		intentos++;
	}

		// Mostrar datos
	cout << "\nMostrando resultados:" << endl;
	mostrarSolucion(vectorSolucion);
	cout << "\n\nEl numero de intentos ha sido: " << intentos << endl;
	cout << "\nSe ha tardado en encontrar la solucion un total de: " << tiempo/1000 << endl;
}


void lasVegasNreinas(int n, vector<int> &vectorSolucion, bool &exito, double &tiempo){
	
	Clock temporizador;
	int contador, col;
	vector<int> ok(n);
	vector<int> x(n);

	temporizador.start(); // Comenzamos a contar el tiempo

	for(int i = 0 ; i<n ; i++){ // Inicializamos la solucion a 0
		x[i] = 0;
	}

	for(int k = 0 ; k<n ; k++){
		contador = 0;

		for(int j = 0 ; j<n ; j++){
			x[k] = j;
			
			if(Lugar(k,x) == true){
				contador++;
				ok[contador] = j;
			}
		}

		if(contador == 0){
			break;
		}
		int random = rand()%contador+1;
		col = ok[random];
		x[k] = col;
	}	

	if(contador == 0){
		exito = false;
	} else {
		exito = true;
		vectorSolucion = x;
	}

	temporizador.stop(); // Comenzamos a contar el tiempo
	tiempo = temporizador.elapsed(); // Tomamos el tiempo empleado

}