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

    //constructor copia
    ArregloDinamico(const ArregloDinamico& otro) {
        tam = otro.tam;
        cap = otro.cap;
        datos = new T[cap];              // pedir casas propias
        for (int i = 0; i < tam; i++)
            datos[i] = otro.datos[i];    // Accion de copiar
    }

    // Asignacion c = a
    ArregloDinamico& operator=(const ArregloDinamico& otro) {
        if (this != &otro) {
            delete[] datos;
            tam = otro.tam;
            cap = otro.cap;
            datos = new T[cap];
            for (int i = 0; i < tam; i++)
                datos[i] = otro.datos[i];
        }
        return *this;
    }

    ~ArregloDinamico() {
        delete[] datos;
    }
    void agregar(const T& elemento) {
        if (tam == cap)
            crecer();
        datos[tam] = elemento;
        tam++;
    }

    // Cuantos elementos hay
    int gettamano() const {
        return tam;
    }
    int getCapacidad() const { return cap; }
    T& operator[](int i) {
        return datos[i];
    }
};


#endif // ARREGLO_DINAMICO_H
