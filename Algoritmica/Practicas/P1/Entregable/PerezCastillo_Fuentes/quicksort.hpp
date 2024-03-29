/*
    Cabeceras de las funciones de quicksort
*/ 
#include <vector>

void ordenacionQuickSort();
void rellenarVector(std::vector<int> &v);
void tiemposOrdenacionQuickSort(int nMin, int nMax, int repeticiones, int incremento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos);
void ajusteNlogN(const std::vector <double> &numeroElementos, const std::vector <double> &tiemposReales, std::vector<double> &a);
void calcularTiemposEstimadosNlogN(const std::vector<double> &numeroElementos, const std::vector<double> &a, std::vector<double> &tiemposEstimados);
double calcularTiempoEstimadoNlogN(const double &n, std::vector<double> &a);