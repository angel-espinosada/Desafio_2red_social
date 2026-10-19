#include "mensaje.h"


mensaje::mensaje()
{
    emisor = -1;
    receptor = -1;
    fecha = 0;
    leido = false;
}

mensaje::mensaje(int emisor, int receptor, long long fecha, bool leido, string texto)
{
    this->emisor = emisor;
    this->receptor = receptor;
    this->fecha = fecha;
    this->leido = leido;
    this->texto = texto;
}

int mensaje::getemisor() const { return emisor; }
int mensaje::getreceptor() const { return receptor; }
long long mensaje::getfecha() const { return fecha; }
bool mensaje::getleido() const { return leido; }
string mensaje::gettexto() const { return texto; }

void mensaje::marcar_leido()
{
    leido = true;
}

long long mensaje::memoria_extra() const
{
    return texto.capacity();
}
