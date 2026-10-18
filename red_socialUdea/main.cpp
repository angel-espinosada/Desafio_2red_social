#include <iostream>
#include "arreglo_dinamico.h"
#include "usuario.h"
#include <fstream>
#include <sstream>
#include <string>
#include "memoria.h"

using namespace std;

bool cargarUsuarios(string nombrearchivo, ArregloDinamico<usuario>& usuarios) {
    ifstream archivo(nombrearchivo);
    if (!archivo) {
        cout << "No se pudo abrir " << nombrearchivo << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {

        if (linea.empty()) continue;
        memoria::contar();
        stringstream ss(linea);
        string nombre, nac, correo, clave, ciudad, pais, insc;
        getline(ss, nombre, ';');
        getline(ss, nac,    ';');
        getline(ss, correo, ';');
        getline(ss, clave,  ';');
        getline(ss, ciudad, ';');
        getline(ss, pais,   ';');
        getline(ss, insc,   ';');
        usuario u(nombre, stoi(nac), correo, clave, ciudad, pais, stoi(insc));
        usuarios.agregar(u);
    }
    archivo.close();
    return true;
}

int login(ArregloDinamico<usuario>& usuarios) {
    string nombre, clave;
    cout << "===== Iniciar sesion =====" << endl;
    cout << "Usuario: ";
    cin >> nombre;
    cout << "Clave: ";
    cin >> clave;

    for (int i = 0; i < usuarios.gettamano(); i++) {
         memoria::contar();
        if (usuarios[i].getnombre_usuario() == nombre && usuarios[i].getclave() == clave)
            return i;
    }
    return -1;
}

//memeoria
long long memoriaTotal(ArregloDinamico<usuario>& usuarios) {
    long long m = sizeof(usuarios);
    m += usuarios.getCapacidad() * sizeof(usuario);
    for (int i = 0; i < usuarios.gettamano(); i++)
        m += usuarios[i].memoria_extra();
    return m;
}
int main() {

    ArregloDinamico<usuario> usuarios;
    if (!cargarUsuarios("usuarios.txt", usuarios))

        return 0;
        cout << "Usuarios cargados: " << usuarios.gettamano() << endl;
        cout << "[Iteraciones carga: " << memoria::total() << "]" << endl;
        memoria::reiniciar();

        memoria::reiniciar();
        int actual = login(usuarios);
        if (actual == -1) {
            cout << "Usuario o clave incorrectos" << endl;
            return 0;
    }





    cout << "Bienvenido, " << usuarios[actual].getnombre_usuario() << endl;
    cout << "[Iteraciones login: " << memoria::total() << "]" << endl;
    cout << "[Memoria: " << memoriaTotal(usuarios) << " bytes]" << endl;
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
