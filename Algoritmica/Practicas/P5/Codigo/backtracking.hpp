/*
	Funciones del algoritmo de backtracking
*/
#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <vector>

void backtracking(bool opcion);
void backtrackingNreinas(int n, std::vector<std::vector<int>> &matrizSoluciones);
void backtrackingNreinas_once(int n, std::vector<std::vector<int>> &matrizSoluciones, double &tiempo);

#endif