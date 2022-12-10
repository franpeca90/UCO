/*
    Cabeceras del determinante recursivo
*/ 
#include <vector>

void determinanteRecursivo();

void tiemposOrdenacionDeterminanteRecursivo(int nMin, int nMax, int incremento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos);
void calculoDeterminanteRecursivo(std::vector<std::vector<double> > matrix, const int tam);
double determinanteRecursivo(std::vector<std::vector<double> > matrix, int tam);
void ajusteFactorial(const std::vector <double> &n, const std::vector<double> &tiemposReales, std::vector<double> &a);
double factorial(const int num);
void calcularTiemposEstimadosFactorial(const std::vector<double> &n, const std::vector<double> &tiemposRales, const std::vector<double> &a, std::vector<double> &tiemposEstimados);
double calcularTiempoEstimadoFactorial(const double &n, const std::vector<double> &a);