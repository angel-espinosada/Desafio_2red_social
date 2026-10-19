#ifndef UDEABOOK_H
#define UDEABOOK_H

#include <string>
#include "arreglo_dinamico.h"
#include "usuario.h"

using namespace std;

class udeabook
{
private:
    ArregloDinamico<usuario> usuarios;
    bool* matriz;          // matriz de adyacencia n x n
    int n;                 // cantidad de usuarios
    int actual;            // indice del usuario que inicio sesion (-1 = nadie)

    // ayudantes internos (solo los usa la clase)
    bool cargar_usuarios(string nombre_archivo);
    bool cargar_amistades(string nombre_archivo);
    bool cargar_solicitudes(string nombre_archivo);
    int amigos_en_comun(int yo, int otro);
    int buscar_usuario(string nombre);
    bool tiene_solicitud(int de, int para);
    void enviar_solicitud_a(int destino);
    void sortear3(int* boletas);

    // no se permite copiar la red: tiene una matriz con new
    udeabook(const udeabook&);
    udeabook& operator=(const udeabook&);

public:
    udeabook();
    ~udeabook();

    bool cargar_datos();
    bool login();
    void mostrar_mejores_amigos();
    void enviar_solicitud();
    void aceptar_solicitud();
    void ver_sugerencias();
    long long memoria_total();
};

#endif // UDEABOOK_H
