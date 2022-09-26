/*
    Funciones de ordenacion quicksort
*/

#include <iostream>
#include <vector>

#include "quicksort.hpp"

using namespace std;

/*!		
	\brief Funcion princiapl que calcula tiempos reales, genera un modelo y calcula tiempos aproximados. Tambien pasa los datos a ficheros y permite al usuario
    calcular tiempos aproximados de ordenacion para un tamaño concreto de vector 
*/
void ordenacionQuickSort(){

    int nMin, nMax; // Numero minimo y maximo de elementos que tendra el vector
    int repeticiones; // Cuantas veces se realizaran las pruebas para un mismo tamaño de vector
    int incremento; // Incremento del tamaño del vector, tras X repeticiones, se incrementara

    double coeficienteDeterminacion; // Coeficiente que nos dice que tan bien aproxima nuestro modelo

    vector<double> tiemposReales // Tiempo medio que ha tardado en ordenar un vector de tamaño N. La posicion 0 corresponde con el vector de tamaño minimo
    vector<double> tiemposEstimados // Tiempo dado por la curva a crear, nos dice de forma estimada el tiempo que se tarda en ordenar un vector de tamaño N

    vector<double> numeroElementos // Indica el numero de elementos que posee cada vector. La posicion i corresponde con el tiempo i del vector de tiemposReales
    
    vector<double> a // Vector con los coeficientes de la curva a ajustar

    // Calculamos los tiempos reales en ordenar vectors de diferentes tamaños
    tiemposOrdenacionQuickSort(nMin, nMax, repeticiones, incremento, *tiemposReales, *numeroElementos);

    // Almacenamos los valores en un fichero

    // Ajustamos una curva logaritmica
    ajusteNlogN(*numeroElementos, *tiemposReales, *a);

    // Calculamos los tiempos estimados usando la curva
    calcularTiemposEstimadosNlogN(*numeroElementos, *a, *tiemposEstimados);

    // Calculamos el coeficiente de determinacion para saber cuan bien se ajusta nuestro modelo a la realidad
    coeficienteDeterminacion = calcularCoeficienteDeterminacion(*tiemposReales, *tiemposEstimados);

    // Almacenamos los resultados finales en un fichero

    // Representamos graficamente con gnuplot

    // Permitimos al usuario aproximar tiempos para un tamaño introducido por el mismo
}


/*!		
	\brief Rellena un vector con valores aleatorios entre 0 y 9999999
	\param v: Vector a rellenar con valores aleatorios
*/
void rellenarVector(vector<int> &v){


}

/*!		
	\brief Comprueba si el vector pasado como parametro esta ordenado o no 
	\param v: Vector a comprobar
*/
bool estaOrdenado(const vector<int> &v){

    return 0;
}


/*!		
	\brief Calcula el tiempo medio real que se tarda en ordenar un vector por quicksort, para diferentes tamaños de vector 
	\param nMin: Tamaño minimo que tendra el vector
	\param nMax: Tamaño maximo que tenndra el vector
    \param repeticiones: Numero de veces que realizaremos pruebas para un mismo tamaño de vector
    \param incremento: Aumento de tamaño de vector tras realizar pruebas
    \param tiemposReales: Tiempos medios reales para cada tamaño de vector
    \param numeroElementos: Diferentes tamaños obtenidos
*/
void tiemposOrdenacionQuickSort(int nMin, int nMax, int repeticiones, int incremento, vector<double> &tiemposReales, vector<double> &numeroElementos){

}


/*!		
	\brief Obtencion de los coeficientes de la curva logaritmica que calculara los tiempos estimados 
	\param numeroElementos: Tamaños de los vectores usados para calcular sus tiempos reales
	\param tiemposReales: Tiempos medios reales que se tardaron en ordenar los vectores
    \param a: Coeficientes de la curva, es lo que devuelve la funcion
*/
void ajusteNlogN(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector<double> &a){

}



double sumatorio(vector<double> &n, vector <double> &t, int expN, int expT){

    return 0.0;
}


/*!		
	\brief Se calculan los tiempos estimados usando una curva logaritmica para diferentes tamaños de vector 
	\param numeroElementos: Tamaños de los vectores usados para calcular sus tiempos reales
    \param a: Coeficientes de la curva
    \param tiemposEstimados: Tiempos estimados, resultado de aplicar la curva a diferentes tamaños de vector
*/
void calcularTiemposEstimadosNlogN(const vector<double> &numeroElementos, const vector<double> &a, vector<double> &tiemposEstimados){

}


/*!		
	\brief Coeficiente que indica cuan bien aproxima nuestro modelo a los resultados
	\param tiemposReales: Tiempos medios reales que se tardaron en ordenar los vectores
    \param tiemposEstimados: Tiempos estimados, resultado de aplicar la curva a diferentes tamaños de vector
*/
double calcularCoeficienteDeterminacion(const vector<double> &tiemposReales, const vector<double> &tiemposEstimados){

    return 0.0;
}


/*!		
	\brief Calcula el tiempo de ordenacion de un vector con tamaño introducido por el usuario
	\param n: Tamaño del vector introducido por el usuario, sera del que se calcule el tiempo aproximado
    \param a: Coeficientes de la curva
*/
double calcularTiempoEstimadoNlogN(const double &n, vector<double> &a){
    
    return 0.0;
}