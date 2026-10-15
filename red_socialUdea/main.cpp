#include <iostream>
using namespace std;

int main() {
    int opcion;

    do {
        cout << "\n***** Ude@Book *****" << endl;
        cout << "1. Administrar amistades" << endl;
        cout << "2. Visitar perfil de un amigo" << endl;
        cout << "3. Ver sugerencias de amistad" << endl;
        cout << "4. Mensajes" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: cout << "Amistades" << endl; break;
        case 2: cout << "Perfil" << endl; break;
        case 3: cout << "Sugerencias" << endl; break;
        case 4: cout << "Mensajes" << endl; break;
        case 0: cout << "Hasta pronto" << endl; break;
        default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
