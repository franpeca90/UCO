#include "serietemporal.hpp"

#include <iostream>
#include <fstream>

void metodoPrimero();
void rellenarVectoresISE(vector<int> &posiciones, vector<long double>  &ISEs, SerieTemporal serie);
void realizarSegmentacionISE(vector<int> &posiciones, vector<long double>  &ISEs, SerieTemporal serie, int num_puntos);