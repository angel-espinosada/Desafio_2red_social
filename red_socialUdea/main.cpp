#include <iostream>
#include "arreglo_dinamico.h"
#include "usuario.h"

using namespace std;

int main() {
    ArregloDinamico<usuario> usuarios;

    usuario u1("angel", 20000412, "annn@mail.com", "1234", "Medellin", "Colombia", 20250110);
    usuario u2("maria", 19990101, "mar@mail.com", "abcd", "Bogota", "Colombia", 20250205);
    usuario u3("pedro", 20010315, "pdr@mail.com", "pass", "Cali", "Colombia", 20250301);

    usuarios.agregar(u1);
    usuarios.agregar(u2);
    usuarios.agregar(u3);

    cout << "Hay " << usuarios.gettamano() << " usuarios" << endl;
    cout << "El usuario 1 es: " << usuarios[0].getnombre_usuario() << endl;
    usuario u("angel", 20000412, "anhg@mail.com", "1234", "Medellin", "Colombia", 20250110);
    cout << u.getnombre_usuario() << endl;
    cout << u.getclave() << endl;

    ArregloDinamico<int> a;
    a.agregar(5);
    a.agregar(7);

    ArregloDinamico<int> c;
    c.agregar(1);
    c = a;
    c[0] = 100;

    cout << a[0] << endl;
    cout << c[0] << endl;
    cout << c.gettamano() << endl;
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
