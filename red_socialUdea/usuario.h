#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "arreglo_dinamico.h"

using std::string;

class usuario
{
private:
    string nombre_usuario;
    long long fecha_nacimiento;
    string _correo;
    string _ruta_foto;
    string _clave;
    string ciudad;
    string pais;
    long long fecha_inscripcion;
    ArregloDinamico<string>album;//
    ArregloDinamico<int>mensaje_enviado;
    ArregloDinamico<int>mensajes_recibidos;
    ArregloDinamico<int>solicitudes_recibidas;
    ArregloDinamico<int>amigos;
public:
    usuario();
    usuario(string nombre, int nacimiento, string correo, string clave,
            string ciudad, string pais, int inscripcion);
    string getnombre_usuario () const;
    string getclave()const;
    long long memoria_extra() const;
};

#endif // USUARIO_H
