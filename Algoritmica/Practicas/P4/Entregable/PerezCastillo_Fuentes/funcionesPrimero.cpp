#include <iostream>

#include "serietemporal.hpp"
#include "ClaseTiempo.cpp"

using namespace std;

void algoritmoProgramacionDinamica(SerieTemporal serie, vector<vector<int>>& matrizPuntos, vector<vector<long double>>& matrizErrores, int puntosSerie, int puntosSegmentacion );
void establecerDominantes(SerieTemporal& serie,  vector<vector<int>> matrizPuntos, int puntosSerie, int puntosSegmentacion );

/*!		
	\brief Funcion que realiza el primero metodo para la segmentacion
*/
void metodoPrimero(){
    // Variables para mostrar resultados
    int posicionMaximo;
    long double sumaErrorCuadrado, errorMaximo;
    
    Clock time; // Creacion del objeto que medira el tiempo

    // Abrimos el fichero
    cout << "Introduce el nombre del fichero. Ejemplo: 'BBVA.txt': ";
    char fichero[99];
    cin >> fichero;
    SerieTemporal serie(fichero);


    // Obtenemos el numero de puntos
    int puntosSegmentacion;
    cout << "Introduce el numero de puntos que quedaran en la segmentacion: ";
    cin >> puntosSegmentacion;

    int puntosSerie = serie.numeroPuntosSerieTemporal(); // Usamos una variable para los puntos de la serie


    // Marcamos los puntos indicados como dominantes
    serie.dominantePunto(0, true); // Primer punto
    serie.dominantePunto(puntosSerie - 1, true); // Ultimo punto


    // Inicializacion de las matrices
    vector<vector<int>> matrizPuntos(puntosSerie, vector<int>(puntosSegmentacion));
    vector<vector<long double>> matrizErrores(puntosSerie, vector<long double>(puntosSegmentacion));

    /* NOTA: No incluyo la parte siguiente parte del algoritmo porque entiendo que esto es solo de inicializacion, por ese motivo
    no lo introduzco en ninguna funcion ni calculo el tiempo */

    // Inicializamos las matrices a los casos particulares
    matrizErrores[0][0] = 0.0; // El primero punto de la matriz de errores tiene error 0
    for(int i = 1 ; i<puntosSerie ; i++){ // El resto de valores de la primera columna sera infinito
        matrizErrores[i][0] = 999999999;
    }

    // Inicio del tiempo
    time.start();

    /* Algoritmo de programacion dinamica [ E(n,m) = min { E(j,m-1) + e(Pj, Pn) } ]
                                               m-1 <= j <= n-1                      */
    algoritmoProgramacionDinamica(serie, matrizPuntos, matrizErrores, puntosSerie, puntosSegmentacion);

    // Fin del tiempo      
    time.stop();

    // Establecimiento de puntos dominantes
    establecerDominantes( serie, matrizPuntos, puntosSerie, puntosSegmentacion);

    // Guardamos los puntos dominantes en un fichero y representamos graficamente
    // Mostramos los resultados
    float tiempo = time.elapsed();
    serie.erroresSegmentacion(sumaErrorCuadrado, errorMaximo, posicionMaximo);
    cout << "\nNumero de puntos dominantes: " << serie.contarPuntosDominantes() << endl;
    cout << "ISE = " << sumaErrorCuadrado << endl;
    cout << "errorMaximo = " << errorMaximo << endl;
    cout << "puntoErrorMaximo = " << posicionMaximo << endl;
    cout << "Tiempo = " << tiempo/1000 << endl;

    // Guardamos la segmentacion en un fichero
    char nombre_fichero_segmentacion[] = "segmentacion.txt";
    serie.guardarSegmentacion(nombre_fichero_segmentacion);

    // Se representa en gnuplot ejecutando el script correspondiente para ello

}

void algoritmoProgramacionDinamica(SerieTemporal serie, vector<vector<int>>& matrizPuntos, vector<vector<long double>>& matrizErrores, int puntosSerie, int puntosSegmentacion ){
    // Variables auxiliares
    long double aux_min, aux_actual;
    
    for(int m = 1 ; m<puntosSegmentacion ; m++){
        for(int n = m ; n<puntosSerie ; n++){
            aux_min = 9999999999;
            for(int j = m-1 ; j<n ; j++){ // Para el minimo, oscila en los valores mencionados de j
                aux_actual = matrizErrores[j][m-1] + serie.calcularIseEntreDosPuntos(j,n);
                
                // Ahora tenemos que ver cual es el minimo de los errores
                if(aux_actual < aux_min){
                    aux_min = aux_actual;
                    matrizErrores[n][m] = aux_min;
                    matrizPuntos[n][m] = j;

                }
            }
        }
    }
}


void establecerDominantes(SerieTemporal& serie, vector<vector<int>> matrizPuntos, int puntosSerie, int puntosSegmentacion ){   
    long double aux_pos = matrizPuntos[puntosSerie-1][puntosSegmentacion-1]; // Tomamos la posicion del ultimo punto, este ya ha sido puesto como dominante 
    for(int j = puntosSegmentacion-2 ; j >= 0 ; j--){ // Obtenemos el resto de puntos decrementando el valor j y usando el resultado de la posicion anterior
        serie.dominantePunto(aux_pos, true);
        aux_pos = matrizPuntos[aux_pos][j];
    }
}