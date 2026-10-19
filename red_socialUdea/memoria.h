#ifndef MEMORIA_H
#define MEMORIA_H

class memoria
{
private:
    static long long iteraciones;
public:
    memoria();
    static void reiniciar();
    static void contar();
    static long long total();
};

#endif // MEMORIA_H

