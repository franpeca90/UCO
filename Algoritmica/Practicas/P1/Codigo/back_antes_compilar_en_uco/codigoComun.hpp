#include <vector>

bool estaOrdenado(const std::vector<int> &v);
double sumatorio(const std::vector<double> &n,const std::vector <double> &t, int expN, int expT);
double calcularCoeficienteDeterminacion(const std::vector<double> &tiemposReales, const std::vector<double> &tiemposEstimados);
void rellenarMatriz(std::vector<vector<double>> &m, int opcion);

// Declaracion de funciones usadas del sistemaEcuaciones.hpp . Si inlucyo el .cpp, da problemas en la compilacion
void inicializarInversa(vector<vector<double>> &inversa);
void trianguloInferior(vector<vector<double>> &A, vector<vector<double>> &inversa);
double productoDiagonal(const vector<vector<double>> &matriz);
void hacerCerosColumna(vector<vector<double>> &A, vector<vector<double>> &inversa, unsigned int x);