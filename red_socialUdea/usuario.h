#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "arreglo_dinamico.h"
#include "album.h"

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
    ArregloDinamico<album>albumes;//
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
    void agregar_amigo(int indice);
    ArregloDinamico<int>& getamigos();
    void agregar_solicitud(int indice);
    ArregloDinamico<int>& getsolicitudes();
    void agregar_enviado(int indice);
    void agregar_recibido(int indice);
    ArregloDinamico<int>& getrecibidos();
    void agregar_album(const album& a);
    ArregloDinamico<album>& getalbumes();
};

#endif // USUARIO_H
