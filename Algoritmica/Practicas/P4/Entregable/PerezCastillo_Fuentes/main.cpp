#include <iostream>

using namespace std; 

void metodoPrimero();

int main() {
    int opcion = 1;
    
    while(opcion == 1 || opcion == 2){
        cout << "\n\n|> Inicio del programa\n";
        cout << "\n   [1] Primer metodo \n   [2] Segundo metodo (No implementado) \n   [Cual quier otra cosa] Para salir del programa\n";
        
        cout << "\nIntroduce el número de la opción que deseas realizar: ";
        cin >> opcion;
    
        switch (opcion){
            case 1:
                cout << "\nSe ha seleccionado el metodo 1\n" << endl;
                metodoPrimero();
            break;
        //---------
            case 2:
                cout << "\nEste método no está implementado, reiniciando el programa...\n" << endl;
                //metodoSegundo();

            break;
        //---------
            default: 
                cout << "Finalizando el programa..." << endl;
            break;
        }
    }

    return 0;
}