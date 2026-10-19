#ifndef UDEABOOK_H
#define UDEABOOK_H

#include <string>
#include "arreglo_dinamico.h"
#include "usuario.h"
#include "mensaje.h"
#include "album.h"

using namespace std;

class udeabook
{
private:
    ArregloDinamico<usuario> usuarios;
    ArregloDinamico<mensaje> mensajes;
    bool* matriz;          // matriz de adyacencia n x n
    int n;                 // cantidad de usuarios
    int actual;            // indice del usuario que inicio sesion (-1 = nadie)


    bool cargar_usuarios(string nombre_archivo);
    bool cargar_amistades(string nombre_archivo);
    bool cargar_solicitudes(string nombre_archivo);
    int amigos_en_comun(int yo, int otro);
    int buscar_usuario(string nombre);
    bool tiene_solicitud(int de, int para);
    void enviar_solicitud_a(int destino);
    void sortear3(int* boletas);
    bool cargar_mensajes(string nombre_archivo);
    long long fecha_actual();
    int primero_desde(ArregloDinamico<int>& rec, long long desde);
    bool cargar_albumes(string nombre_archivo);
    bool cargar_fotos(string nombre_archivo);
    void carrusel(int dueno, album& alb);
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
    void enviar_mensaje();
    void leer_nuevos();
    void buscar_mensajes();
    void guardar_datos();
    void visitar_perfil();
};

#endif // UDEABOOK_H
