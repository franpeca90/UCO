/*
    Funciones del determinante iterativo 
*/

#include "determinanteIterativo.hpp"
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"
#include "codigoComun.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

/*!		
	\brief Realiza el calculo del determinante iterativo obteniendo un modelo para predecir tiempos para diferentes valores
*/
void determinanteIterativo() {
    int nMin, nMax; // Numero minimo y maximo de dimension que tendra la matriz
    int incremento; // Incremento del tamaño del vector, tras una repeticion, se incrementara
    
    bool flag = true; // Nos permitira salir del bucle que realiza predicciones de tiempos de tamaño introducido por el usuario
    int tam; // Tamaño de la matriz a predecir su tiempo de ordenacion
    double tiempo_aproximado; // Tiempo predecido para un tamaño matriz dado por el usuario usando nuestro modelo
    double years, days, minutes, seconds, aux;

    double coeficienteDeterminacion; // Coeficiente que nos dice que tan bien aproxima nuestro modelo

    vector<double> tiemposReales; // Tiempo medio que ha tardado en realizar el determinante de una matriz de tamaño N.
    vector<double> tiemposEstimados; // Tiempo dado por la curva a crear, nos dice de forma estimada el tiempo que se tarda realizar un determinante de tamaño N

    vector<double> numeroElementos; // Indica la dimension que posee cada matrix. La posicion i corresponde con el tiempo i del vector de tiemposReales

    vector<double> n; // Indica el orden de las matrices a realizar el determinante
    
    vector<double> a; // Vector con los coeficientes de la curva a ajustar

    fstream file; // Fichero donde almacenaremos los datos

    // Obtenemos los valores que quiera el usuario
    cout << "Introduce la dimension minima de la matriz: ";
    cin >> nMin;

    cout << "Introduce la dimension maxima de la matriz: ";
    cin >> nMax;

    cout << "Introduce el incremento de valor de las dimensiones: ";
    cin >> incremento;

    // Calculamos los tiempos reales en ordenar vectores de diferentes tamaños
    tiemposOrdenacionDeterminanteIterativo(nMin, nMax, incremento, tiemposReales, numeroElementos);

    // Almacenamos los valores en un fichero
    file.open("tiempoReales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposReales.size() ; i++){
        file << numeroElementos[i] << " " << tiemposReales[i] << endl;  
    }
    file.close();

    // Ajustamos una curva polinomica, esto es, obtener los coeficientes de la ecuacion logistica
    ajustePolinomico(numeroElementos, tiemposReales, a);

    // Calculamos los tiempos estimados usando la curva
    calcularTiemposEstimadosPolinomico(numeroElementos, tiemposReales, a, tiemposEstimados);

    // Calculamos el coeficiente de determinacion para saber cuan bien se ajusta nuestro modelo a la realidad
    coeficienteDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    // Almacenamos los resultados finales en un fichero
    file.open("tiempoFinales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposEstimados.size() ; i++){
        file << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << endl;  
    }
    file.close();

    // Mostramos los resultados
    cout << "\nLa curva de ajuste es:   " << a[0] << " + (" << a[1] << " * n) + (" << a[2] << " * n^2) + (" << a[3] << " * n^3)" << endl;
    cout << "El coeficiente de determinacion es:    " << coeficienteDeterminacion << endl;
    
    // Representamos graficamente con gnuplot

    // Permitimos al usuario aproximar tiempos para un tamaño introducido por el mismo
    while(flag){
        cout << "\nIntroduce un tamaño de ejemplar para predecir su tiempo. Si no quieres predecir, introduce 0: ";
        cin >> tam;

        if(tam!=0){
            // Calculamos el tiempo aproximado para el tamaño dado por el usuario
            tiempo_aproximado = calcularTiempoEstimadoPolinomico(tam, a); // NOTA: segun el guion, los resultados estan en microsegundos

            years = tiempo_aproximado * 3.168808781402895 * pow (10, -14); // Paso de milisegundos a años

            // Esta funcion introduce en el segundo parametro la parte entera y devuelve la parte decimal, correspondiente al primer argumento pasado
            days = modf(years, &years); // La parte entera seran los años, la decimal los dias
            minutes = modf(days*360, &days); // Le paso los dias correspondientes a la parte decimal de los años
            seconds = modf(minutes*1440, &minutes); // Paso de dias a minutos
            seconds = seconds * 60; // Finalmente paso de minutos a segundos

            // Mostramos los resultados
            cout << "\n--> Para ordenar un vector de " << tam << " elementos se tardaria aproximadamente: "
                 << years << " años " 
                 << days << " dias "
                 << minutes << " minutos "
                 << seconds << " segundos " << endl;
        } else {
            flag = false;
        }
    }
}


/*!		
	\brief Calcula el tiempo medio real que se tarda en ordenar un vector por quicksort, para diferentes tamaños de vector 
	\param nMin: Tamaño minimo que tendra el vector
	\param nMax: Tamaño maximo que tenndra el vector

    \param incremento: Aumento de tamaño de vector tras realizar pruebas
    \param tiemposReales: Tiempos medios reales para cada tamaño de vector
    \param numeroElementos: Diferentes tamaños obtenidos
*/
void tiemposOrdenacionDeterminanteIterativo(int nMin, int nMax, int incremento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos){

    vector<vector<double>> m; // Creamos la variable matriz 
    Clock time; // Creacion del objeto que medira el tiempo

    int opcion; // Variable para saber que opcion quiere realizar el usuario
    
    cout << "\n   [1] Introducir valores aleatorios \n   [2] Introducir valores manualmente \n";
    cout << "\nIntroduce el número de la forma de rellenado que deseas realizar: ";
    cin >> opcion;

    for (double tam = nMin ; tam<=nMax ; tam = tam+incremento){ // Obtenemos las diferentes dimensiones de la matriz     

        m = vector<vector<double>>(tam, vector<double>(tam)); // Volvemos a crear la matriz con diferente tamaño

        rellenarMatriz(m, opcion); // Rellenamos la matriz

        time.start(); // Inicio de la medicion de tiempo
           
        calculoDeterminanteIterativo(m, tam); // Calculamos el determinante mediante el metodo iterativo
            
        time.stop(); // Parada de la medicion de tiempo
        
        numeroElementos.push_back(tam); // Guardamos el numero de elementos del vector creado
        tiemposReales.push_back(time.elapsed()); // Guardamos la media de los tiempos reales obtenidos para ese tamaño
    }
}


/*!		
	\brief Realiza el calculo del determinante de una matriz 
	\param matrix: Matriz a calcular el determinante
	\param tam: Dimensiones de la matriz
*/
void calculoDeterminanteIterativo(vector<vector<double>> matrix, int tam){

    // Creamos la variable de la matriz inversa
    vector<vector<double>> inversa;
    inversa = vector<vector<double>>(tam, vector<double>(tam));

	//Inicializamos la matriz inversa
	inicializarInversa(inversa);

	//Se triangulariza la matriz por debajo de la diagonal
	trianguloInferior(matrix, inversa);
	
    //Mostramos determinante
	double determinante = productoDiagonal(matrix);

}


/*!		
	\brief Obtenemos los coeficientes del polinomio que predecira los tiempos para un tamaño de matriz dado
	\param n: Matriz a calcular el determinante
	\param tiemposReales: Dimensiones de la matriz
    \param a: Coeficientes del polinomio
*/
void ajustePolinomico(const std::vector <double> &n, const std::vector <double> &tiemposReales, std::vector <double> &a){
    // Los tamaños de las matrices son acorde a la ecuacion dada en el documento de practicas
    // Si utilizaramos una ecuacion polinomica con mas terminos habria que modificarlo
    vector<vector<double>> A{ { 0, 0, 0, 0}, 
                              { 0, 0, 0, 0},
                              { 0, 0, 0, 0},
                              { 0, 0, 0, 0} }; // Vector que tiene los coeficientes del sistema de ecuaciones
    
    vector<vector<double>> B{ {0},
                              {0},
                              {0},
                              {0} }; // Vector que tiene los terminos independientes del sistema de ecuaciones
    
    vector<vector<double>> X{ {0},
                              {0},
                              {0},
                              {0} }; // Vector que contendras los coeficientes de la ecuacion logistica

    int tam = 4; // Dimensiones n x n de la matriz A

    // En el ajuste necesitaremos varios de los sumatorios
    // Donde N es el numero de matrices que han sido operadas, X son los tamaños de los vectores e Y los tiempos reales obtenidos
    // Ahora generamos los distintos sumatorios para resolver el sistema por minimos cuadrados
    A[0][0] = n.size(); // N
    A[0][1] = sumatorio(n, tiemposReales, 1, 0); // Sumatorio de X
    A[0][2] = sumatorio(n, tiemposReales, 2, 0); // Sumatorio de X^2
    A[0][3] = sumatorio(n, tiemposReales, 3, 0); // Sumatorio de X^3

    A[1][0] = A[0][1];  // Sumatorio de X
    A[1][1] = A[0][2];  // Sumatorio de X^2
    A[1][2] = A[0][3];  // Sumatorio de X^3
    A[1][3] = sumatorio(n, tiemposReales, 4, 0);  // Sumatorio de X^4

    A[2][0] = A[0][2];  // Sumatorio de X^2
    A[2][1] = A[0][3];  // Sumatorio de X^3
    A[2][2] = A[1][3];  // Sumatorio de X^4
    A[2][3] = sumatorio(n, tiemposReales, 5, 0);  // Sumatorio de X^5

    A[3][0] = A[0][3];  // Sumatorio de X^3
    A[3][1] = A[1][3];  // Sumatorio de X^4
    A[3][2] = A[2][3];  // Sumatorio de X^5
    A[3][3] = sumatorio(n, tiemposReales, 6, 0);  // Sumatorio de X^6

    B[0][0] = sumatorio(n, tiemposReales, 0, 1); // Sumatorio de Y
    B[1][0] = sumatorio(n, tiemposReales, 1, 1); // Sumatorio de X * Y
    B[2][0] = sumatorio(n, tiemposReales, 2, 1); // Sumatorio de X^2 * Y
    B[3][0] = sumatorio(n, tiemposReales, 3, 1); // Sumatorio de X^3 * Y
    
    // Resolvemos el sistema de ecuaciones
    resolverSistemaEcuaciones(A, B, tam, X);
 
    // Guardamos los resultados en el vector de coeficientes
    a.push_back(X[0][0]);
    a.push_back(X[1][0]);
    a.push_back(X[2][0]);
    a.push_back(X[3][0]);
}


/*!		
	\brief Obtenemos los tiempos estimados para los mismos tamaños de matriz que antes
	\param n: Vector con los diferentes tamaños de matrices
	\param tiemposReales: Vector con los tiempos reales (No se usa)
	\param tiemposEstimados: Vector que contendra los tiempos estimados
*/
void calcularTiemposEstimadosPolinomico(const std::vector <double> &n, const std::vector <double> &tiemposReales, const std::vector <double> &a, std::vector <double> &tiemposEstimados){
    // La ecuacion a aplicar es: a + b*n + c*n^2 + d*n^3
    for(int i = 0 ; i<n.size() ; i++){
        tiemposEstimados.push_back(a[0] + a[1]*n[i] + a[2]*pow(n[i], 2) + a[3]*pow(n[i], 3));
    }
}


/*!		
	\brief Calcula el tiempo de computo del determinante de una matriz con tamaño introducido por el usuario
	\param n: Tamaño de la matriz introducido por el usuario, sera del que se calcule el tiempo aproximado
    \param a: Coeficientes de la curva
*/
double calcularTiempoEstimadoPolinomico(const double &n, const std::vector <double> &a){
    return a[0] + a[1]*n + a[2]*pow(n, 2) + a[3]*pow(n, 3);
}