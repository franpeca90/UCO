#include "funcionesPrimero.hpp"
#include "funcionesSegundo.hpp"

#include "punto.cpp"
#include "recta.cpp"
#include "serietemporal.cpp"

#include <iostream>

using namespace std; 

int main() {
    cout << endl;
   
    vector<int> vect;
    vect = {10, 20, 30, 40, 50, 60, 70};

    for(int i = 0 ; i<vect.size() ; i++){
        cout << "vect[" << i << "]: " << vect[i] << endl;
    }

    cout << "\n\n BORRANDO\n\n" << endl;

    // Quiero borrar el 30
    int k = 2;

    vector<int>::iterator it_1 = vect.begin() + (k);

    vect.erase(it_1);

    for(int i = 0 ; i<vect.size() ; i++){
        cout << "vect[" << i << "]: " << vect[i] << endl;
    }

    return 0;
}