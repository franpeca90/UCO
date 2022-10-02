/*
    Funciones del determinante recursivo 
*/

#include "determinanteRecursivo.hpp"
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
	\brief Realiza el calculo del determinante recursivo obteniendo un modelo para predecir tiempos para diferentes valores
*/
void determinanteRecursivo() {
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
    tiemposOrdenacionDeterminanteRecursivo(nMin, nMax, incremento, tiemposReales, numeroElementos);

    // Almacenamos los valores en un fichero
    file.open("tiempoReales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposReales.size() ; i++){
        file << numeroElementos[i] << " " << tiemposReales[i] << endl;  
    }
    file.close();

    // Ajustamos una curva polinomica, esto es, obtener los coeficientes de la ecuacion logistica
    ajusteFactorial(numeroElementos, tiemposReales, a);

    // Calculamos los tiempos estimados usando la curva
    calcularTiemposEstimadosFactorial(numeroElementos, tiemposReales, a, tiemposEstimados);

    // Calculamos el coeficiente de determinacion para saber cuan bien se ajusta nuestro modelo a la realidad
    coeficienteDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    // Almacenamos los resultados finales en un fichero
    file.open("datosFinales.txt", ios_base::out);
    for(int i = 0 ; i<tiemposEstimados.size() ; i++){
        file << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << endl;  
    }
    file.close();

    // Mostramos los resultados
    cout << "\nLa curva de ajuste es:   " << a[0] << " + " << a[1] << " * n!" << endl;
    cout << "El coeficiente de determinacion es:    " << coeficienteDeterminacion << endl;
    
    // Representamos graficamente con gnuplot

    // Permitimos al usuario aproximar tiempos para un tamaño introducido por el mismo
    while(flag){
        cout << "\nIntroduce un tamaño de ejemplar para predecir su tiempo. Si no quieres predecir, introduce 0: ";
        cin >> tam;

        if(tam!=0){
            // Calculamos el tiempo aproximado para el tamaño dado por el usuario
            tiempo_aproximado = calcularTiempoEstimadoFactorial(tam, a); // NOTA: segun el guion, los resultados estan en microsegundos

            years = tiempo_aproximado * 3.168808781402895 * pow (10, -14); // Paso de milisegundos a años

            // Esta funcion introduce en el segundo parametro la parte entera y devuelve la parte decimal, correspondiente al primer argumento pasado
            days = modf(years, &years); // La parte entera seran los años, la decimal los dias
            minutes = modf(days*360, &days); // Le paso los dias correspondientes a la parte decimal de los años
            seconds = modf(minutes*1440, &minutes); // Paso de dias a minutos
            seconds = seconds * 60; // Finalmente paso de minutos a segundos

            // Mostramos los resultados
            cout << "\n  --> Para una matriz de orden " << tam << " se tardaria aproximadamente: "
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
	\brief Calcula el tiempo de realizar el determinante de una matriz de forma recursiva para un tamaño de matriz dado
	\param nMin: Tamaño minimo de la matriz
	\param nMax: Tamaño maximo de la matriz
    \param incremento: Aumento de tamaño de la matriz tras realizar una prueba
    \param tiemposReales: Tiempos reales para cada tamaño de matriz
    \param numeroElementos: Son los diferentes tamaños obtenidos
*/
void tiemposOrdenacionDeterminanteRecursivo(int nMin, int nMax, int incremento, vector<double> &tiemposReales, vector<double> &numeroElementos){

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
           
        calculoDeterminanteRecursivo(m, tam); // Calculamos el determinante mediante el metodo recursivo
            
        time.stop(); // Parada de la medicion de tiempo
        
        numeroElementos.push_back(tam); // Guardamos el numero de elementos del vector creado
        tiemposReales.push_back(time.elapsed()); // Guardamos la media de los tiempos reales obtenidos para ese tamaño
    }

}


/*!		
	\brief Realiza el calculo del determinante de forma recursiva de una matriz. Llama a la funcion recursiva 
	\param matrix: Matriz a calcular el determinante
	\param tam: Dimensiones de la matriz
*/
void calculoDeterminanteRecursivo(vector<vector<double>> matrix, const int tam){
    double determinante = determinanteRecursivo(matrix, tam); // Simplemente calculamos el determinante
    //cout << "El determinante de la matriz es: " << determinante << endl;
}


/*!		
	\brief Funcion recursiva del calculo del determinante 
	\param matrix: Matriz a calcular el determinante
	\param tam: Dimensiones de la matriz
*/
double determinanteRecursivo(std::vector<std::vector<double>> matrix, int tam){

    double determinante = 0.0; 
    double aux = 0.0;
    
    vector<vector<double>> menor;

    int c;

    if(tam==2){ // Caso base
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1]; 
    
    } else { //Caso general
        for(int j=0 ; j<tam ; j++){
            menor = vector<vector<double>>(tam-1, vector<double>(tam-1));
            for(int k=1 ; k<tam ; k++){
                c = 0;
                for(int l=0 ; l<tam ; l++){
                    if(l!=j){
                        menor[k-1][c] = matrix[k][l];
                        c++;
                    }
                }
            }

            aux = pow(-1, 2+j)*matrix[0][j]*determinanteRecursivo(menor, tam-1);
            determinante = determinante + aux;
        }

        return determinante;

    }
}


/*!		
	\brief Obtenemos los coeficientes del polinomio que predecira los tiempos para un tamaño de matriz dado
	\param n: Matriz a calcular el determinante
	\param tiemposReales: Dimensiones de la matriz
    \param a: Coeficientes de la curva de forma factorial
*/
void ajusteFactorial(const vector <double> &n, const vector<double> &tiemposReales, vector<double> &a){
    vector<double> z; // Aqui se guarda el resultado de realizar n!, para cada n, lo metemos en esta funcion y tenemos hecho el cambio de variable
    
    // Los tamaños de las matrices son acorde a la ecuacion dada en el documento de practicas
    // Si utilizaramos una ecuacion factorial con mas terminos habria que modificarlo
    vector<vector<double>> A{ { 0, 0}, 
                              { 0, 0} }; // Vector que tiene los coeficientes del sistema de ecuaciones
    vector<vector<double>> B{ {0},
                              {0} }; // Vector que tiene los terminos independientes del sistema de ecuaciones
    vector<vector<double>> X{ {0},
                              {0} }; // Vector que contendras los coeficientes de la ecuacion exponencial

    int tam = 2; // Dimensiones n x n de la matriz A

    // En el ajuste, necesitamos N, sumatorio de X, sumatorio de X^2, sumatorio de y, sumatorio de x*y
    // Donde N es el numero de matrices que han sido operadas, X son los tamaños de los vectores e Y los tiempos reales obtenidos    
    // Realizamos el cambio de variable
    for(int i=0 ; i<n.size() ; i++){
        cout << "El factorial de " << n[i] << " es " << factorial(n[i]) << endl;
        z.push_back(factorial(n[i]));
    }

    // Ahora generamos los distintos sumatorios para resolver el sistema por minimos cuadrados
    A[0][0] = n.size(); // N

    A[0][1] = sumatorio(z, tiemposReales, 1, 0); // Sumatorio de X
    A[1][0] = A[0][1];

    A[1][1] = sumatorio(z, tiemposReales, 2, 0); // Sumatorio de X^2

    B[0][0] = sumatorio(z, tiemposReales, 0, 1); // Sumatorio de Y

    B[1][0] = sumatorio(z, tiemposReales, 1, 1); // Sumatorio de X*Y

    // Resolvemos el sistema de ecuaciones
    resolverSistemaEcuaciones(A, B, tam, X);
 
    // Guardamos los resultados en el vector de coeficientes
    a.push_back(X[0][0]);
    a.push_back(X[1][0]);

}


/*!		
	\brief Funcion que obtiene el factorial de un numero de forma iterativa
	\param n: Numero a calcular su factorial
*/
double factorial(const int num){
    double f = 1;
    for (int i=1 ; i<=num ; i++) {
        f = f * i;
    }
    return f;
}


/*!		
	\brief Obtenemos los tiempos estimados para los mismos tamaños de matriz que antes
	\param n: Vector con los diferentes tamaños de matrices
	\param tiemposReales: Vector con los tiempos reales (No se usa)
	\param tiemposEstimados: Vector que contendra los tiempos estimados
*/
void calcularTiemposEstimadosFactorial(const vector<double> &n, const vector<double> &tiemposRales, const vector<double> &a, vector<double> &tiemposEstimados){
    // La ecuacion a aplicar es: a + b * n!
    for(int i = 0 ; i<n.size() ; i++){
        tiemposEstimados.push_back(a[0] + a[1] * factorial(n[i]));
    }
}


/*!		
	\brief Calcula el tiempo de computo del determinante de una matriz con tamaño introducido por el usuario
	\param n: Tamaño de la matriz introducido por el usuario, sera del que se calcule el tiempo aproximado
    \param a: Coeficientes de la curva
*/
double calcularTiempoEstimadoFactorial(const double &n, const vector<double> &a){
    return a[0] + a[1] * factorial(n);
}