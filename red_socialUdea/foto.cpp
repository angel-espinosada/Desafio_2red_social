#include "foto.h"

foto::foto()
{
    fecha = 0;
    tamano = 0;
    likes = 0;
}

foto::foto(string nombre, int fecha, int tamano, int likes)
{
    this->nombre = nombre;
    this->fecha = fecha;
    this->tamano = tamano;
    this->likes = likes;
}

string foto::getnombre() const { return nombre; }
int foto::getfecha() const { return fecha; }
int foto::gettamano() const { return tamano; }
int foto::getlikes() const { return likes; }

void foto::dar_like()
{
    likes++;
}

long long foto::memoria_extra() const
{
    return nombre.capacity();
}
