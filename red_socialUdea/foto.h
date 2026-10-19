#ifndef FOTO_H
#define FOTO_H

#include <string>
using namespace std;

class foto {
private:
    string nombre;
    int fecha;          // AAAAMMDD
    int tamano;         // en bytes
    int likes;

public:
    foto();
    foto(string nombre, int fecha, int tamano, int likes);

    string getnombre() const;
    int getfecha() const;
    int gettamano() const;
    int getlikes() const;

    void dar_like();
    long long memoria_extra() const;
};


#endif // FOTO_H
