#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <fstream>

#include "algoritmos.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"


using namespace std;



void ordenacionHeapSort(){ //Se usa heapsort

  //====== Variables ======
  double nMax=0.0, nMin=0.0, incremento=0.0;
  double tiemposMedios=0.0;
  double coefDeterminacion=0.0;
  double nTam=0.0;
  int repeticiones=0;
  int opcion;
  // Vector con los tiempos reales y vector con tiempos estimados
  vector <double> tiemposReales, tiemposEstimados;
  // Vector con el tamaño de los vectores (numero de elementos usados en cada vector)
  vector <double> numeroElementos;
  // Vector con los coeficientes que se usaran para el modelo de la regresion y vector con la muestra
  vector <double> coeficientes;

  srand(time(NULL));

  // Introduccion de variables por parte del usuario
  cout << "Introduce el tamaño minimo del vector: ";
  cin >> nMin;
  cout << "Introduce el tamaño maximo del vector: ";
  cin >> nMax;
  cout << "Introduce el numero de veces que se repetira la ordenacion: ";
  cin >> repeticiones;

  // Se llama a la funcion que va a calcular los tiempos de la ordenacion
  tiemposOrdenacionHeapSort(nMin, nMax, repeticiones, tiemposReales, numeroElementos);

  //Se procede a realizar el modelo, esto es calcular los coeficientes de nuestra funcion
  ajusteNlogN(numeroElementos, tiemposReales, coeficientes);

  //Calculamos los tiempos estimados usando el modelo
  calcularTiemposEstimadosNlogN(numeroElementos, coeficientes, tiemposEstimados);

  //Calculamos el coeficiente de determinacion
  coefDeterminacion=calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

  //Volvamos todos nuestros datos en un fichero de texto para ser leido posteriormente por el script
  guardarEnFichero(numeroElementos, tiemposReales, tiemposEstimados);

  //Mostramos los resultados por el terminal
  mostrarResultados(coeficientes, coefDeterminacion);

  //Parte final donde se prueba nuestro modelo para un tamaño determinado del vector
  cout <<endl<< "Desea probar el modelo con un tamaño determinado? [Si=1 , No=0]: ";
  cin >> opcion;

  if(opcion==1){ //Solo si desea probar el modelo

    cout << "Introduce el tamaño de la muestra, introduce 0 si desea dejar de probar el modelo: ";
    cin >> nTam;

    while(nTam!=0){

      cout<<endl<< "Para un tamaño de "<<nTam<<" elementos se tardaria "<<calcularTiempoEstimadoNlogN(nTam,coeficientes)*(1.15740740740740740*pow(10,-11))<<" dia(s) en ordenar el vector"<<endl;

      cout << "Introduce el tamaño de la muestra, introduce 0 si desea dejar de probar el modelo: ";
      cin >> nTam;
    }

  }
}

void tiemposOrdenacionHeapSort(double nMin, double nMax, int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos){
  double tiempoMedio=0;
  int incremento;
  /* Dado que el enunciado no indica que esta funcion reciba el incremento como parametro
  he decidido que es aqui donde el usuario lo introduce para ceñirme lo maximo posible
  al enunciado de la practica. */
  cout << "Introduce el incremento: ";
  cin >> incremento;
  cout << endl << "Realizando las ordenaciones del vector" << endl;

  // Se realiza la ordenacion para diferentes tamaños del vector, diferentes muestras
  for(int i=nMin ; i<=nMax ; i=i+incremento){
    // Se usa una funcion propia para calcular la media de los tiempos
    tiempoMedio=tiempoMedioHeapShort(i, repeticiones);
    // Se guarda el numero de elementos de el vector ordenado
    numeroElementos.push_back(i);
    // Se guarda el tiempo real sucedido al ordenar el vector
    tiemposReales.push_back(tiempoMedio);
  }
}

double tiempoMedioHeapShort(const int &tam,const double &repeticiones){
  /* NOTA: Se usaran funciones propias de C++ para la ordenacion y
  comprobacion del HeapShort */

  //Objeto de la clase Clock que nos permitira cronometrar la ordenacion
  Clock reloj;
  double sumTiempos=0;

  for(int i=0 ; i<repeticiones ; i++){
    /* Cada vez que se vaya a ordenar el vector hay que inicializarlo con
    el tamaño correspondiente */
    vector <int> v(tam);
    // Se rellena el vector aleatoriamente
    rellenarVector(v);
    //Se cronometra la ordenacion
    reloj.start();
    heapSort(v);
    reloj.stop();
    //Se comprueba si el vector esta ordenado
    estaOrdenado(v);
    //Se va guardando la suma de los tiempos para asi calcular la media
    sumTiempos=sumTiempos+reloj.elapsed();
  }
  //Se devuelve el tiempo medio en ordenar ese tamaño del vector
  return sumTiempos/repeticiones;
}

void rellenarVector(vector<int> &v){
  //Rellenado simple de un vector
  for(int i=0 ; i<v.size(); i++){
    v[i]=rand()%(9999999+1);
  }
}

/* NOTA:Se podria haber pues las lineas con las funciones de ordenacion en la funcion
llamante para asi no tener en cuenta el tiempo (aunque infimo) que se tarda en llamar a
esta funcion, por lo que realmente en los tiempos se esta tomando el tiempo en llamar
a la funcion mas el tiempo de ordenar. He puesto estas lineas aqui porque el propio
enunciado de la practica especifica que se debe de realizar la ordenacion en esta funcion */

bool heapSort(vector <int> &v){
  // Se procede a llamar a una funcion propia de C++ para el HeapShort
  make_heap(v.begin(), v.end());
  sort_heap(v.begin(), v.end());
  return true;
}

bool estaOrdenado(const vector <int> &v){
  //Funcion de C++ que indica si un vector se encuentra ordenado o no
  return is_sorted(v.begin(), v.end());
}

void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){
  //Matrices que contendra los datos para el calculo de los coeficientes
  vector<vector <double>> A(2, vector<double> (2, 0));
  vector<vector <double>> B(2, vector<double> (1, 0));
  vector<vector <double>> X(2, vector<double> (1, 0));
  //Vector que contendra el cambio de variable z=n·Log(n)
  vector<double> nLogN;

  //Se realiza el cambio de variable realizando la multiplicacion
  for(int i=0 ; i<n.size() ; i++){
    nLogN.push_back(n[i]*log(n[i]));
  }

  //Se rellenan las matrices
  for(int i=0 ; i< A.size() ; i++){
    for(int j=0 ; j < A[i].size() ; j++){
      A[i][j]=sumatorio(nLogN, tiemposReales, i+j, 0); //0 por el exponente
    }
  }

  for(int i=0 ; i < B.size() ; i++){
    B[i][0]=sumatorio(nLogN, tiemposReales, i, 1);
  }
  /* Dado el sistema de ecuaciones de la practica, el primer elemento
  corresponde al sumatorio total de las n */
  A[0][0]=nLogN.size();

  //Llamamos a la funcion dada para la resolucion del sistema
  resolverSistemaEcuaciones(A, B, 2, X);

  /* La funcion guardara en X los coeficientes de nuestro modelo por
  lo que solo falta guardarlos en nuestro vector de coeficientes */
  for(int i=0 ; i < X.size() ; i++){
    a.push_back(X[i][0]);
  }


}

double sumatorio(const vector <double> &n,const  vector <double> &t, double expN, double expT){
  double sumatorio=0;
  for(int i=0 ; i<n.size() ; i++){
    sumatorio = sumatorio + (pow(n[i],expN) * pow(t[i],expT));
  }
  return sumatorio;
}

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &a, vector <double> &tiemposEstimados){
  for(int i=0 ; i<n.size() ; i++){
    //Realizamos la evaluacion del valor en nuestro modelo para obtener el tiempo estimado para ese tamaño del vector
    tiemposEstimados.push_back(a[0]+a[1]*(n[i]*log(n[i])));
  }
}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
  double mediaReal=0.0, mediaEstimada=0.0, varianzaReal=0.0, varianzaEstimada=0.0;
  double aux=0.0; //Variable auxiliar para realizar los calculos estadisticos
  //Calculamos la media de los tiempos reales
  for(int i=0 ; i<tiemposReales.size() ; i++){
    aux=aux+tiemposReales[i];
  }
  mediaReal=aux/tiemposReales.size();

  aux=0.0;
  //Calculamos la media de los tiempos generados por nuestro modelo
  for(int i=0 ; i<tiemposEstimados.size() ; i++){
    aux=aux+tiemposEstimados[i];
  }
  mediaEstimada=aux/tiemposEstimados.size();

  aux=0.0;
  //Calculamos la varianza de los tiempos reales
  for(int i=0 ; i<tiemposReales.size() ; i++){
    aux=aux+((tiemposReales[i]-mediaReal)*(tiemposReales[i]-mediaReal));
  }
  varianzaReal=aux/tiemposReales.size();

  aux=0.0;
  //Calculamos la varianza de los tiempos generados por nuestro modelo
  for(int i=0 ; i<tiemposEstimados.size() ; i++){
    aux=aux+((tiemposEstimados[i]-mediaEstimada)*(tiemposEstimados[i]-mediaEstimada));
  }
  varianzaEstimada=aux/tiemposEstimados.size();

  //Finalmente devolvemos el coeficiente de determinacion
  return varianzaEstimada/varianzaReal;
}

void guardarEnFichero(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
  //Se guarda todos los datos directamente en un solo fichero
  ofstream f("Datos.txt");
  for(int i=0 ; i<n.size() ; i++){
    f<<n[i]<<"\t"<<tiemposReales[i]<<"\t"<<tiemposEstimados[i]<<"\n";
  }
  f.close();
}

void mostrarResultados(const vector <double> a, const double coefDeterminacion){
  cout <<endl<< "El modelo creado es: " << endl;
  cout << "    t(n) = " <<a[0]<<"+"<<a[1]<<"*nlog(n)"<<endl;
  cout <<endl<< "Este modelo tiene un coeficiente de determinacion de: "<<coefDeterminacion<<endl;
}

double calcularTiempoEstimadoNlogN(const double &n, vector <double> &a){
  return a[0]*a[1]*n*log(n);
}


// ==================================


void determinanteIterativo(){

  //====== Variables ======
  double nMax=0.0, nMin=0.0, incremento=0.0;
  double tiempo=0.0;
  double coefDeterminacion=0.0;
  int opcion;
  // Vector con los tiempos reales y vector con tiempos estimados
  vector <double> tiemposReales, tiemposEstimados;
  // Vector con el tamaño de los vectores (numero de elementos usados en cada vector)
  vector <double> tamMatriz;
  // Vector con los coeficientes que se usaran para el modelo de la regresion y vector con la muestra
  vector <double> coeficientes;

  srand(time(NULL));

  // Introduccion de variables por parte del usuario
  cout << "Introduce el tamaño minimo: ";
  cin >> nMin;
  cout << "Introduce el tamaño maximo: ";
  cin >> nMax;
  cout << "Introduce un incremento: ";
  cin >> incremento;
  // Se pregunta al usuario como se va a rellenar la matriz
  cout << "[1] Rellenado manual | [2] Rellenado automatico: ";
  cin >> opcion;

  for(int i=nMin ; i<=nMax ; i=i+incremento){
    // Se usa una funcion propia para calcular la media de los tiempos
    tiempo=calculoDeterminanteIterativo(i, opcion);
    // Se guarda el numero de elementos de el vector ordenado
    tamMatriz.push_back(i);
    // Se guarda el tiempo real sucedido al ordenar el vector
    tiemposReales.push_back(tiempo);
  }

  //Se procede a obtener los coeficientes con los datos calculados
  ajustePolinomico(tamMatriz, tiemposReales, coeficientes);

  //Se calculan una serie de tiempos estimados para posteriores datos estadisticos
  calcularTiemposEstimadosPolinomico(tamMatriz, tiemposReales, coeficientes, tiemposEstimados);

  //Se utiliza la funcion del calculo del coeficiente de determinacion
  coefDeterminacion=calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

  //Volvamos todos nuestros datos en un fichero de texto para ser leido posteriormente por el script
  guardarEnFichero(tamMatriz, tiemposReales, tiemposEstimados);

  //Mostramos los resultados por el terminal
  cout <<endl<< "El modelo creado es: " << endl;

  cout << "    t(n) = " <<coeficientes[0]<<"+"<<coeficientes[1]<<"*n"<<coeficientes[2]<<"*n^2"<<coeficientes[3]<<"*n^3"<<endl;
  cout <<endl<< "Este modelo tiene un coeficiente de determinacion de: "<<coefDeterminacion<<endl;
}


double calculoDeterminanteIterativo(int tam,int opcion){
  Clock reloj;
  double determinante=0;
  //Se crea una matriz cuadrada con los vectores de la STL
  vector <vector<double>> matriz(tam, vector<double>(tam,0));
  //Matrices que nos permitiran realizar el calculo del determinante
  vector <vector<double>> inversa(matriz.size(), vector<double>(matriz.size()));

  //Segun la opcion se toma una forma de rellenado u otra
  if(opcion==1){
    for(int i=0 ; i<tam ; i++){
      for(int j=0 ; j<tam ; j++){
        cout<<"Introduce el elemento ["<<i<<"]"<<"["<<j<<"]: ";
        cin >> matriz[i][j];
      }
    }
  }

  if(opcion==2){
    for(int i=0 ; i<tam ; i++){
      for(int j=0 ; j<tam ; j++){
        matriz[i][j]=(0.95) + (rand()/(RAND_MAX/(1.05-0.95)));
      }
    }
  }

  //Se usan las funciones facilitadas en la practica
  reloj.start();
  inicializarInversa(inversa);
  trianguloInferior(matriz,inversa);
  determinante = productoDiagonal(matriz);
  reloj.stop();
  //Se devuelve el tiempo que se ha tardado en calcular el determinante
  return reloj.elapsed();
}


void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){
  vector<vector<double>> A (4, vector<double> (4));
  vector<vector<double>> B (4, vector<double> (1));
  vector<vector<double>> X (4, vector<double> (1));


  //Se rellenan las matrices
  for(int i=0 ; i< A.size() ; i++){
    for(int j=0 ; j < A[i].size() ; j++){
      A[i][j]=sumatorio(n, tiemposReales, i+j, 0); //0 por el exponente
    }
  }

  for(int i=0 ; i < B.size() ; i++){
    B[i][0]=sumatorio(n, tiemposReales, i, 1);
  }

  A[0][0]=n.size();

  //Se llama a la funcion dada en la practica para resolver el sistema de ecuaciones
  resolverSistemaEcuaciones(A,B,4,X);

  //Guardamos los coeficientes del modelo en el vector de coeficientes
  for(int i=0 ; i<4 ; i++){
    cout <<endl<<"Coeficiente: "<<X[i][0]<< endl;
    a.push_back(X[i][0]);
  }
}


void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados){
  for(int i=0 ; i<n.size() ; i++){
    tiemposEstimados.push_back( a[0] + a[1]*n[i] + a[2]*pow(n[i],2) + a[3]*pow(n[i],3) );
  }
}


// ==================================
