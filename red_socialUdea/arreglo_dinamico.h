#ifndef ARREGLO_DINAMICO_H
#define ARREGLO_DINAMICO_H

template <typename T>

class ArregloDinamico {
private:
    T* datos;
    int tam;       // Capacidad ocupada
    int cap;       // La capacidad total
    void crecer() {
        T* nuevo = new T[cap * 2];
        for (int i = 0; i < tam; i++)
            nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        cap = cap * 2;
    }

public:

    ArregloDinamico() {
        cap = 4; //Se inicia con 4
        tam = 0;
        datos = new T[cap];
    }


    ~ArregloDinamico() {
        delete[] datos;
    }
    void agregar(const T& elemento) {
        if (tam == cap)          // calle llena?
            crecer();            // mudarse a una del doble
        datos[tam] = elemento;   // ocupar la siguiente casa
        tam++;                   // una casa ocupada mas
    }

    // Cuantos elementos hay
    int tamano() const {
        return tam;
    }
    T& operator[](int i) {
        return datos[i];
    }
};


#endif // ARREGLO_DINAMICO_H
