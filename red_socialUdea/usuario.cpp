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
