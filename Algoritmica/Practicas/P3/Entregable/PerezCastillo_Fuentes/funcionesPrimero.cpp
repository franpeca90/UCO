#include "funcionesPrimero.hpp"

#include <iostream>

using namespace std;

/*!		
	\brief Funcion que realiza el primero metodo para la segmentacion
*/
void metodoPrimero(){

    // Variables para realizar la segmentacion 
    vector<int> posiciones;
    vector<long double> ISEs;
    
    // Variables para mostrar resultados
    int posicionMaximo;
    long double sumaErrorCuadrado, errorMaximo;


    // --> 1. Abrimos el fichero
    // Leemos el fichero con la serie temporal
    cout << "Introduce el nombre del fichero. Ejemplo: 'BBVA.txt': ";
    char fichero[99];
    cin >> fichero;
    SerieTemporal serie(fichero);

    // Obtenemos el numero de puntos
    int num_puntos;
    cout << "Introduce el numero de puntos que quedaran en la segmentacion: ";
    cin >> num_puntos;


    // --> 2. Recorremos la serie y guardamos la posicion de los puntos y el error ISE de cada uno
    rellenarVectoresISE(posiciones, ISEs, serie);

    // --> 3. Borramos el menor de la serie y recalculamos el error
    realizarSegmentacionISE(posiciones, ISEs, serie, num_puntos);


    // --> 4. Hacemos puntos dominantes aquellos restantes tras la eliminacion
    for(int l=0 ; l<posiciones.size() ; l++){
        serie.dominantePunto(posiciones[l], true); //
    }

    // --> 5. Guardamos los puntos dominantes en un fichero y representamos graficamente
    // Mostramos los resultados
    serie.erroresSegmentacion(sumaErrorCuadrado, errorMaximo, posicionMaximo);
    cout << "\nNumero de puntos dominantes: " << serie.contarPuntosDominantes() << endl;
    cout << "ISE = " << sumaErrorCuadrado << endl;
    cout << "errorMaximo = " << errorMaximo << endl;
    cout << "puntoErrorMaximo = " << posicionMaximo << endl;


    // --> 6. Guardamos la segmentacion en un fichero
    char nombre_fichero_segmentacion[] = "segmentacion.txt";
    serie.guardarSegmentacion(nombre_fichero_segmentacion);


    // Se representa en gnuplot ejecutando el script correspondiente para ello

}


void rellenarVectoresISE(vector<int> &posiciones, vector<long double>  &ISEs, SerieTemporal serie){
    long double aux_error;
    int nPuntosSerie; // Este es el total de puntos de me serie
    nPuntosSerie = serie.numeroPuntosSerieTemporal();
  
    for(int i=0 ; i<nPuntosSerie ; i++){
        posiciones.push_back(i); // Introducimos la posicion del elemento en el vector de posiciones

        // Calculamos el error del punto i, para el punto inicial y final daremos un error muy alto, dado que siempre son puntos dominantes

        if (i==0 || i==nPuntosSerie-1) {
            aux_error = 99999; // Valor alto para los dos casos comentados
        } else {
            aux_error = serie.calcularIseEntreDosPuntos(i-1, i+1); // Calculamos el ISE de mi punto usando los dos puntos que hay a su lado                       
        }

        ISEs.push_back(aux_error); // Guardamos el error de la posicion i
    }
    

}


void realizarSegmentacionISE(vector<int> &posiciones, vector<long double>  &ISEs, SerieTemporal serie, int num_puntos){
    int nPuntosSerie = serie.numeroPuntosSerieTemporal();

    // Variable auxiliares o que guardan temporalmente informacion
    long double aux_menor;
    int pos_menor;

    for(int j=0 ; j<nPuntosSerie-num_puntos ; j++){

            // Busco el que tiene menor ISE de mi vector
            aux_menor = 99999; 
            for(int k=0 ; k<posiciones.size() ; k++){
                if(aux_menor > ISEs[k]) {
                    aux_menor = ISEs[k];
                    pos_menor = k;
                }
            }

            // Creo los iteradores que apuntan a ese elemento
            vector<int>::iterator it_1 = posiciones.begin() + (pos_menor); // Necesario para obtener un iterador para borrar con erase
            vector<long double>::iterator it_2 = ISEs.begin() + (pos_menor);

            // Elimino el elemento de ambos vectores
            posiciones.erase(it_1);
            ISEs.erase(it_2); 

            // Recalculo el error de los puntos izquierdo y derecho que estan al lado de este punto
            // El punto anterior k se elimina, el k+1 pasa a ser k y el k-1 sigue siendo k-1
            
            if(pos_menor-1 != 0){
                ISEs[pos_menor-1] = serie.calcularIseEntreDosPuntos(posiciones[pos_menor-2], posiciones[pos_menor]);
            }
            
            if(pos_menor != posiciones.size()-1){
                ISEs[pos_menor] = serie.calcularIseEntreDosPuntos(posiciones[pos_menor-1], posiciones[pos_menor+1]);
            }
    }
}