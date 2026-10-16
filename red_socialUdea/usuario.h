#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "arreglo_dinamico.h"

using namespace std;

class usuario
{
private:
    string nombre_usuario;
    long long fecha_nacimiento;
    string correo;
    string ruta_foto;
    string clave;
    string ciudad;
    string pais;
    ArregloDinamico<string>album;
    ArregloDinamico<int>mensaje_enviado;
    ArregloDinamico<int>mensajes_recibidos;
    ArregloDinamico<string>solicitudes_recibidas;
    ArregloDinamico<int>amigos;
public:
    usuario();
};

#endif // USUARIO_H
