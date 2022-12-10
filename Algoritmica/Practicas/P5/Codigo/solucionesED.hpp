#ifndef _solucionesED_HPP_
#define _solucionesED_HPP_

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>

class EDsoluciones{
	private:
		int _n; // Numero de reinas
		std::vector <std::vector <int>> _matriz; // Matriz con las soluciones

	public:
		EDsoluciones(int nReinas){ // Constructor
			setN(nReinas);
		}

		int getN(){ // Getter
			return _n;
		}

		void setN(int nReinas){ // Setter
			_n=nReinas;
		}

		int getElementoMatriz(int i, int j){ // Getter de las soluciones
			return _matriz[i][j];
		}

		void insertarEstructura(std::vector <int> v){ // Setter de las soluciones
			_matriz.push_back(v);
		}

		void mostrarSolucion(){
			for(int i=0 ; i <getSizeEstructura(); i++){
				  std::cout<<"[";
					for(int j=0; j < getN(); j++){
						if(j == getN()-1){
							std::cout << getElementoEstructura(i, j);
						}
						else{
							std::cout << getElementoEstructura(i, j)  << ", ";
						}
					}
					std::cout<<"]"<< std::endl;
			}

		}

};

#endif