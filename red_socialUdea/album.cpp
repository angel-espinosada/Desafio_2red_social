#include "album.h"
#include "foto.h"

album::album()
{
    privacidad = 0;
}

album::album(string nombre, int privacidad)
{
    this->nombre = nombre;
    this->privacidad = privacidad;
}

string album::getnombre() const { return nombre; }
int album::getprivacidad() const { return privacidad; }

void album::agregar_foto(const foto& f)
{
    fotos.agregar(f);
}

ArregloDinamico<foto>& album::getfotos()
{
    return fotos;
}

long long album::memoria_extra() const
{
    long long m = nombre.capacity();
    m += fotos.getCapacidad() * (long long)sizeof(foto);   // las casas de fotos
    for (int i = 0; i < fotos.gettamano(); i++)
        m += fotos[i].memoria_extra();                     // el nombre de cada foto
    return m;
}
