#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
using namespace std;

class mensaje {
private:
    int emisor;
    int receptor;
    long long fecha;
    bool leido;
    string texto;

public:
    mensaje();
    mensaje(int emisor, int receptor, long long fecha, bool leido, string texto);

    int getemisor() const;
    int getreceptor() const;
    long long getfecha() const;
    bool getleido() const;
    string gettexto() const;

    void marcar_leido();
    long long memoria_extra() const;
};

#endif // MENSAJE_H
