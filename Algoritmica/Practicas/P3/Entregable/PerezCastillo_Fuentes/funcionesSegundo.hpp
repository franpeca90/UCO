#include "serietemporal.hpp"

#include <iostream>
#include <fstream>

void metodoSegundo();
void rellenarVectoresEMAX(vector<int> &posiciones, vector<long double>  &eMAXs, SerieTemporal serie);
void realizarSegmentacionEMAX(vector<int> &posiciones, vector<long double>  &eMAXs, SerieTemporal serie, int num_puntos);