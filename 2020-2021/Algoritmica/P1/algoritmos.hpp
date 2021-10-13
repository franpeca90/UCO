#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <vector>

using namespace std;
// Funcion invocada desde el main
void ordenacionHeapSort();

// Se invoca a las funciones de ordenacion y se van almacenando los tiempos obtenidos
void tiemposOrdenacionHeapSort(double nMin, double nMax, int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos);

/* Funcion que realizara la media de los tiempos dados por la ordenacion HeapSort
Toma el tamaño del vector y el numero de veces que se realizara la ordenacion para ese tamaño */
double tiempoMedioHeapShort(const int &tam,const double &repeticiones);

// Funcion que rellena el vector del cual queremos calcular sus tiemposMedios
// --------> Usada en tiemposOrdenacionHeapSort
void rellenarVector(vector<int> &v);

bool heapSort(vector <int> &v);

// Funcion que ordena el vector
// --------> Usada en tiemposOrdenacionHeapSort
bool estaOrdenado(const vector <int> &v);

// Se comienza con el modelo de regresion, se ajusta la curva logaritmica
void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);

// Funcion para calcular los sumatorios
double sumatorio(const vector <double> &n,const  vector <double> &t, double expN, double expT);

// Funcion que usa el modelo creado para calcular tiempos estimados para un imput dado por el usuario
void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &a, vector <double> &tiemposEstimados);

//Funcion que calcula el coeficiente de determinacion de nuestro modelo
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

//Funcion que vuelva los datos en un fichero
void guardarEnFichero(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

//Funcion que muestra los datos por consola
void mostrarResultados(const vector <double> a, const double coefDeterminacion);

//Mostramos el tiempo que tardaria en ordenarse el vector para un tamaño dado por el usuario
double calcularTiempoEstimadoNlogN(const double &n, vector <double> &a);

//Funcion principal donde se ejecutara las funciones para realizar el detemrinante iterativo
void determinanteIterativo();

//Funcion que realiza el calculo del determinante
double calculoDeterminanteIterativo(int tam, int opcion);

//Funcion que crea el modelo para el determinante iterativo
void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);

//Funcion que calcula los tiempos estimados
void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);

//Funcion que prueba el modelo del determinante iterativo
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);


#endif
