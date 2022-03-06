#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

#include "slist_imp.hpp"

using namespace std;

int
main(int argc, const char* argv[])
{

    SList<int> lista;
    lista.is_empty();
    cout << "Tamaño: " << lista.size() << endl;
    lista.insert(10);
    cout << "Tamaño: " << lista.size() << endl;
    cout << "Numero: " << lista.current() << endl;
}

