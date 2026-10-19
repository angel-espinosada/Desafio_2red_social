#include "usuario.h"

usuario::usuario() {}

usuario::usuario(string nombre, int nacimiento, string correo, string clave, string ciudad,
                 string pais, int inscripcion)
{
    nombre_usuario = nombre;
    fecha_nacimiento=nacimiento;
    _correo=correo;
    _clave=clave;
    this->ciudad=ciudad;
    this->pais=pais;
    fecha_inscripcion=inscripcion;

}

string usuario::getnombre_usuario()const {
        return nombre_usuario;
}

string usuario::getclave() const
{
    return _clave;
}

long long usuario::memoria_extra() const
{
    long long m = 0;
    m += nombre_usuario.capacity() + _correo.capacity() + _ruta_foto.capacity();
    m += _clave.capacity() + ciudad.capacity() + pais.capacity();
    m += mensaje_enviado.getCapacidad() * sizeof(int);
    m += mensajes_recibidos.getCapacidad() * sizeof(int);
    m += solicitudes_recibidas.getCapacidad() * sizeof(int);
    m += amigos.getCapacidad() * sizeof(int);
    return m;
}

void usuario::agregar_amigo(int indice)
{
    amigos.agregar(indice);
}

ArregloDinamico<int> &usuario::getamigos()
{
    return amigos;
}

void usuario::agregar_solicitud(int indice)
{
    solicitudes_recibidas.agregar(indice);
}

ArregloDinamico<int> &usuario::getsolicitudes()
{
    return solicitudes_recibidas;
}
