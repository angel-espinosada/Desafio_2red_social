#include <iostream>
#include "arreglo_dinamico.h"

using namespace std;

int main() {

    ArregloDinamico<int> a;
    a.agregar(5);
    a.agregar(7);

    ArregloDinamico<int> c;
    c.agregar(1);       // c ya tiene su propia calle
    c = a;              // aqui se usa operator=
    c[0] = 100;

    cout << a[0] << endl;          // debe seguir en 5
    cout << c[0] << endl;          // debe ser 100
    cout << c.gettamano() << endl; // debe ser 2
    int opcion;
    //  Iniciar sesion
    string usuario, clave;
    cout << "===== Iniciar sesion =====" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Clave: ";
    cin >> clave;

    if (usuario != "angel" || clave != "1234") {
        cout << "Usuario o clave incorrectos" << endl;
        return 0;
    }
    cout << "Bienvenido, " << usuario << endl;
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
