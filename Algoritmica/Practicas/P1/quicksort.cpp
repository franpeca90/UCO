/*
    Funciones de ordenacion quicksort
*/
#include "quicksort.hpp"
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


#include <stdlib.h>
#include <time.h>
#include <math.h>

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

    vector<double> tiemposReales; // Tiempo medio que ha tardado en ordenar un vector de tamaño N. La posicion 0 corresponde con el vector de tamaño minimo
    vector<double> tiemposEstimados; // Tiempo dado por la curva a crear, nos dice de forma estimada el tiempo que se tarda en ordenar un vector de tamaño N

    vector<double> numeroElementos; // Indica el numero de elementos que posee cada vector. La posicion i corresponde con el tiempo i del vector de tiemposReales
    
    vector<double> a; // Vector con los coeficientes de la curva a ajustar

    fstream file; // Fichero donde almacenaremos los datos

    // Obtenemos los valores que quiera el usuario
    cout << "Introduce el tamaño minimo del vector" << endl;
    cin >> nMin;

    cout << "Introduce el tamaño máximo del vector" << endl;
    cin >> nMax;

    cout << "Introduce el incremento del valor de los vectores" << endl;
    cin >> incremento;

    cout << "Introduce el numero de veces que se repetira la ordenacion" << endl;
    cin >> repeticiones;

    // Calculamos los tiempos reales en ordenar vectors de diferentes tamaños
    tiemposOrdenacionQuickSort(nMin, nMax, repeticiones, incremento, tiemposReales, numeroElementos);

    // Almacenamos los valores en un fichero
    file.open("tiempoReales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposReales.size() ; i++){
        file << numeroElementos[i] << " " << tiemposReales[i] << endl;  
    }
    file.close();

    // Ajustamos una curva logaritmica, esto es, obtener los coeficientes de la ecuacion logistica
    ajusteNlogN(numeroElementos, tiemposReales, a);
    cout << "Los coeficientes de la regresion logisitca son: " << a[0] << " y " << a[1] << endl;

    // Calculamos los tiempos estimados usando la curva
    calcularTiemposEstimadosNlogN(numeroElementos, a, tiemposEstimados);

    // Calculamos el coeficiente de determinacion para saber cuan bien se ajusta nuestro modelo a la realidad
    coeficienteDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    // Almacenamos los resultados finales en un fichero
    file.open("tiempoFinales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposEstimados.size() ; i++){
        file << tiemposEstimados[i] << endl;  
    }
    file.close();

    // Representamos graficamente con gnuplot

    // Permitimos al usuario aproximar tiempos para un tamaño introducido por el mismo
}


/*!		
	\brief Rellena un vector con valores aleatorios entre 0 y 9999999
	\param v: Vector a rellenar con valores aleatorios
*/
void rellenarVector(vector<int> &v){
    srand(time(NULL)); // Inicio de la semilla de generacion de numeros aleatorios

    for(int i=0 ; i<v.size() ; i++){ // Generamos tantos numeros como elementos del vector
        v[i] = rand()%9999999; // Genera numeros entre 0 y 9999999
    }
}


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
	\brief Calcula el tiempo medio real que se tarda en ordenar un vector por quicksort, para diferentes tamaños de vector 
	\param nMin: Tamaño minimo que tendra el vector
	\param nMax: Tamaño maximo que tenndra el vector
    \param repeticiones: Numero de veces que realizaremos pruebas para un mismo tamaño de vector
    \param incremento: Aumento de tamaño de vector tras realizar pruebas
    \param tiemposReales: Tiempos medios reales para cada tamaño de vector
    \param numeroElementos: Diferentes tamaños obtenidos
*/
void tiemposOrdenacionQuickSort(int nMin, int nMax, int repeticiones, int incremento, vector<double> &tiemposReales, vector<double> &numeroElementos){
    double sum_tiempos; // Se usara para le media de tiempos
    
    vector<int> v; // Vector que asignaremos diferentes tamaños y ordenaremos varias veces 
    Clock time; // Creacion del objeto que medira el tiempo

    for (double tam = nMin ; tam<nMax ; tam = tam+incremento){ // Obtenemos los diferentes tamaños del vector     
        sum_tiempos = 0.0;

        // Ahora realizamos la creacion y ordenacion tantas veces como ha indicado el usuario
        for(double it = 0 ; it<repeticiones ; it++){
            v.clear(); // Limpiamos el vector
            v.resize(tam); // Establecemos el tamaño del vector

            rellenarVector(v); // Rellenamos el vector de forma aleatoria

            time.start(); // Inicio de la medicion de tiempo
           
            sort(v.begin(), v.end()); // Ordenamos el vector
            
            time.stop(); // Parada de la medicion de tiempo

            sum_tiempos = sum_tiempos + time.elapsed();
                  
            if(estaOrdenado(v)){ // Comprobamos si los vectores estan ordenados
                //cout << "Vector ordenado" << endl;
            } else {
                //cout << "Vector no ordenado " << endl;
            }
        }

        numeroElementos.push_back(tam); // Guardamos el numero de elementos del vector creado
        tiemposReales.push_back(sum_tiempos/repeticiones); // Guardamos la media de los tiempos reales obtenidos para ese tamaño

    }
    
}


/*!		
	\brief Obtencion de los coeficientes de la curva logaritmica que calculara los tiempos estimados 
	\param numeroElementos: Tamaños de los vectores usados para calcular sus tiempos reales
	\param tiemposReales: Tiempos medios reales que se tardaron en ordenar los vectores
    \param a: Coeficientes de la curva, es lo que devuelve la funcion
*/
void ajusteNlogN(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector<double> &a){
    vector<double> z; // Aqui se guarda el resultado de realizar n * log(n), para cada n, lo metemos en esta funcion y tenemos hecho el cambio de variable
    
    // Los tamaños de las matrices son acorde a la ecuacion dada en el documento de practicas
    // Si utilizaramos una ecuacion logaritmica con mas terminos habria que modificarlo
    vector<vector<double>> A{ { 0, 0}, 
                              { 0, 0} }; // Vector que tiene los coeficientes del sistema de ecuaciones
    vector<vector<double>> B{ {0},
                              {0} }; // Vector que tiene los terminos independientes del sistema de ecuaciones
    vector<vector<double>> X{ {0},
                              {0} }; // Vector que contendras los coeficientes de la ecuacion logistica

    int n = 2; // Dimensiones n x n de la matriz A

    // En el ajuste, necesitamos N, sumatorio de X, sumatorio de X^2, sumatorio de y, sumatorio de x*y
    // Donde N es el numero de vectores que han sido ordenados, X son los tamaños de los vectores e Y los tiempos reales obtenidos
    
    // Realizamos el cambio de variable
    for(int i=0 ; i<numeroElementos.size() ; i++){
        z.push_back(numeroElementos[i]*log(numeroElementos[i]));
    }

    // Ahora generamos los distintos sumatorios para resolver el sistema por minimos cuadrados
    A[0][0] = numeroElementos.size(); // N

    A[0][1] = sumatorio(z, tiemposReales, 1, 0); // Sumatorio de X
    A[1][0] = A[0][1];

    A[1][1] = sumatorio(z, tiemposReales, 2, 0); // Sumatorio de X^2

    B[0][0] = sumatorio(z, tiemposReales, 0, 1); // Sumatorio de Y

    B[1][0] = sumatorio(z, tiemposReales, 1, 1); // Sumatorio de X*Y

    // Resolvemos el sistema de ecuaciones
    resolverSistemaEcuaciones(A, B, n, X);
 
    // Guardamos los resultados en el vector de coeficientes
    a.push_back(X[0][0]);
    a.push_back(X[1][0]);

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