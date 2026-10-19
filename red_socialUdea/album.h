#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "arreglo_dinamico.h"
#include "foto.h"
using namespace std;

class album {
private:
    string nombre;
    int privacidad;               // 0 publico, 1 amigos, 2 privado
    ArregloDinamico<foto> fotos;  // el album es dueno de sus fotos

public:
    album();
    album(string nombre, int privacidad);

    string getnombre() const;
    int getprivacidad() const;
    void agregar_foto(const foto& f);
    ArregloDinamico<foto>& getfotos();

    long long memoria_extra() const;
};
#endif // ALBUM_H
