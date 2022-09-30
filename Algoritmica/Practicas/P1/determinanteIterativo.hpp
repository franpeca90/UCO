/*
    Cabeceras del determinante iterativo
*/ 
#include <vector>

void determinanteIterativo();
void calculoDeterminanteIterativo(std::vector<std::vector<double>> matrix);
void ajustePolinomico(const std::vector <double> &n, const std::vector <double> &tiemposReales, std::vector <double> &a);
void calcularTiemposEstimadosPolinomico(const std::vector <double> &n, const std::vector <double> &tiemposReales, const std::vector <double> &a, std::vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, const std::vector <double> &a);
void tiemposOrdenacionDeterminanteIterativo(int nMin, int nMax, int incremento, std::vector<double> &tiemposReales, std::vector<double> &numeroElementos);