/*
    Este fichero contiene funciones que se usa para los tres algoritmos usados en la practica
    Hay funciones, como la de rellenar vector, que se implementan de forma distinta
    dependiendo del tipo de algoritmo, por eso no estan incluidas aqui.
*/

#include <vector>
#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

/*!		
	\brief Comprueba si el vector pasado como parametro esta ordenado o no 
	\param v: Vector a comprobar
*/
bool estaOrdenado(const vector<int> &v){
    if (is_sorted(v.begin(), v.end())){ // Comprobamos si esta ordenado
        return true;
    } else {
        return false;
    }
}


/*!		
	\brief Permite realizar el sumatorio de dos vectores de entrada con su correspondiente exponente 
	\param n: Vector que contiene los elementos de la sumatoria, multiplican a los elementos del vector t
	\param t: Vector que contiene los otros elementos de la sumatoria, multiplican a los elementos del vector n
    \param expN: Coeficiente de los elementos de n. 0 en caso de que no se quiera usar estos elementos
    \param expT: Coeficiente de los elementos de t. 0 en caso de que no se quiera usar estos elementos 
*/
double sumatorio(const vector<double> &n,const vector <double> &t, int expN, int expT){
    double sumatoria = 0.0;

    for(int i=0 ; i<n.size() ; i++){ // Los vectores n y t tienen el mismo numero de elementos, por eso comparten indice
        sumatoria = sumatoria + (pow(n[i], expN) * pow(t[i], expT));
    }

    return sumatoria;
}


/*!		
	\brief Coeficiente que indica cuan bien aproxima nuestro modelo a los resultados
	\param tiemposReales: Tiempos medios reales que se tardaron en ordenar los vectores
    \param tiemposEstimados: Tiempos estimados, resultado de aplicar la curva a diferentes tamaños de vector
*/
double calcularCoeficienteDeterminacion(const vector<double> &tiemposReales, const vector<double> &tiemposEstimados){
    // El coeficiente es X / Y, siendo X la varianza de los tiempos estimados e Y la de los tiempos reales
    float sum_X = 0.0, sum_Y = 0.0; // Variable auxiliar que sirve tanto para calcular la media como para el sumatorio que hay en la varianza
    float media_X = 0.0, media_Y = 0.0;
    float var_X = 0.0, var_Y = 0.0; // Varianzas de ambos vectores

    // Calculamos los sumatorios de los valores de los vectores y sus respectivas medias
    for(int i = 0 ; i<tiemposReales.size() ; i++){
        sum_X = sum_X + tiemposEstimados[i];
        sum_Y = sum_Y + tiemposReales[i];
    }
    
    media_X = sum_X / tiemposEstimados.size(); // Realmente, tienen el mismo tamaño
    media_Y = sum_Y / tiemposReales.size();
    
    // Calculamos la varianza, primero realizamos la parte del sumatorio y despues dividimos entre N
    for(int j = 0 ; j<tiemposReales.size() ; j++){
        sum_X = sum_X + pow(tiemposEstimados[j] - media_X, 2);
        sum_Y = sum_Y + pow(tiemposReales[j] - media_Y, 2);
    }

    var_X = sum_X / tiemposEstimados.size();
    var_Y = sum_Y / tiemposReales.size();

    return var_X / var_Y; // Devolvemos el coeficiente
}


void rellenarMatriz(vector<vector<double>> &m, int opcion){
    srand(time(NULL)); // Inicio de la semilla de generacion de numeros aleatorios
    double valor; // Variable auxiliar para almacenar los valores de la matrices en la misma

    if(opcion == 1){ // Rellenamos de forma aleatoria con valores entre 0.95 y 1.05

        // Generamos numeros entre el intervalo pero multiplicado por 100 y al resultado lo dividimos entre 100
        for(int i = 0 ; i<m.size() ; i++){
            for(int j = 0 ; j<m.size() ; j++){
                valor = 95+rand()%(105+1-95);
                m[i][j] = valor/100;
            }
        } 

    } else if (opcion == 2){ // Los valores los rellena el usuario de forma manual
        cout << "\n"; // Para que sea mas legible la consola
        // Generamos numeros entre el intervalo pero multiplicado por 100 y al resultado lo dividimos entre 100
        for(int i = 0 ; i<m.size() ; i++){
            for(int j = 0 ; j<m.size() ; j++){
                cout << "Introduce el valor de la posicion [" << i << "][" << j << "] de la matriz: ";
                cin >> valor;
                m[i][j] = valor;
            }
        }
        cout << "\n Ya has terminado de rellenar esta matriz!\n";

    } else { // En caso de que el usuario introduzca algo no valido
        cout << "Error, no has introducido una opcion valida" << endl;
    } 
}