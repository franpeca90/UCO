#include "funcionesPrimero.hpp"

#include <iostream>

using namespace std;

/*!		
	\brief Funcion que realiza el primero metodo para la segmentacion
*/
void metodoPrimero(){

    int posicionMaximo;
    long double sumaErrorCuadrado, errorMaximo; // Variables de la segmentacion
    
    long double eMax = 0.0; // Error maximo que se tomara para calcular la serie segmentada
    cout << "Introduce el eMax: ";
    cin >> eMax;

    // --> 1. Marcamos el primer y ultimo punto como dominantes
    // Leemos el fichero con la serie temporal
    char fichero[] = "BBVA.txt";
    SerieTemporal serie(fichero);

    // Marcamos los puntos indicados como dominantes
    serie.dominantePunto(0, true); // Primer punto
    serie.dominantePunto(serie.numeroPuntosSerieTemporal() - 1, true);


    // --> 2. Repetimos de forma recursiva
    recursivaPrimero(&serie, 0, serie.numeroPuntosSerieTemporal() - 1,eMax);


    // --> 3. Guardamos los puntos dominantes en un fichero y representamos graficamente
    // Mostramos los resultados
    serie.erroresSegmentacion(sumaErrorCuadrado, errorMaximo, posicionMaximo);
    cout << "\nNumero de puntos dominantes: " << serie.contarPuntosDominantes() << endl;
    cout << "ISE = " << sumaErrorCuadrado << endl;
    cout << "errorMaximo = " << errorMaximo << endl;
    cout << "puntoErrorMaximo = " << posicionMaximo << endl;

    // Guardamos la segmentacion en un fichero
    char nombre_fichero_segmentacion[] = "BBVA_segmentado.txt";
    serie.guardarSegmentacion(nombre_fichero_segmentacion);

    // Se representa en gnuplot ejecutando el script correspondiente para ello

}

/*!		
	\brief Funcion recursiva que va formando los puntos dominantes de la segmentacion. Usa el punto de mayor error
	\param serie: Serie temporal la cual segmentar
    \param puntoIzquierda: Posicion izquierda del intervalo
    \param puntoDerecha: Posicion derecha del intervalo
    \param eMax: Error maximo, se usa para compararlo con el error dado por la segmentacion actual
*/
void recursivaPrimero(SerieTemporal *serie, int puntoIzquierda, int puntoDerecha, double eMax){
    // Calculamos el error maximo del intervalo
    int posicion;
    long double error = serie->calcularEmaxEntreDosPuntos(puntoIzquierda, puntoDerecha, posicion);
    // Vemos si el error es es superior
    if (error > eMax){
        // Lo marcamos como dominante
        serie->dominantePunto(posicion, true); // Primer punto
        // Aplicamos recursividad
        // Por izquierda
        recursivaPrimero(serie, puntoIzquierda, posicion, eMax);
        // Por derecha
        recursivaPrimero(serie, posicion, puntoDerecha, eMax);
    }
    // Si no lo es, no lo marcamos como dominante, ya es parte de la solucion
}
