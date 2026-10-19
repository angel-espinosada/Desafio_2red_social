#include <iostream>
#include "arreglo_dinamico.h"
#include "usuario.h"
#include <fstream>
#include <sstream>
#include <string>
#include "memoria.h"
#include <ctime>
#include "udeabook.h"
using namespace std;




void mostrar_metricas(udeabook& red)
{
    cout << "[Iteraciones: " << memoria::total() << "]" << endl;
    cout << "[Memoria: " << red.memoria_total() << " bytes]" << endl;
}


void menu_amistades(udeabook& red)
{
    int op;
    cout << "\n--- Amistades ---" << endl;
    cout << "1. Enviar solicitud" << endl;
    cout << "2. Aceptar solicitud" << endl;
    cout << "Opcion: ";
    cin >> op;

    memoria::reiniciar();
    if (op == 1)
        red.enviar_solicitud();
    else if (op == 2)
        red.aceptar_solicitud();
    else {
        cout << "Opcion invalida" << endl;
        return;
    }
    mostrar_metricas(red);
}

int main() {

    srand(time(0));
    udeabook red;                          // toda la red social en un objeto

    memoria::reiniciar();
    if (!red.cargar_datos()) {
        system("pause");
        return 0;
    }
    mostrar_metricas(red);

    memoria::reiniciar();
    while (!red.login()) {
        cout << "Intenta de nuevo\n" << endl;
        memoria::reiniciar();
    }
    mostrar_metricas(red);

    memoria::reiniciar();
    red.mostrar_mejores_amigos();
    mostrar_metricas(red);

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
        case 1: cout << "Amistades" << endl;
            menu_amistades(red);
            break;
        case 2: cout << "Perfil" << endl; break;
        case 3: {cout << "Sugerencias" << endl;
            memoria::reiniciar();
            red.ver_sugerencias();
            mostrar_metricas(red);
        }
            break;
        case 4: cout << "Mensajes" << endl; break;
        case 0: cout << "Hasta pronto" << endl; break;
        default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);

    return 0;
}
