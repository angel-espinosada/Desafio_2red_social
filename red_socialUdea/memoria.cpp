#include "memoria.h"

memoria::memoria() {}
long long memoria::iteraciones = 0;

void memoria::reiniciar() { iteraciones = 0; }
void memoria::contar()    { iteraciones++; }
long long memoria::total() { return iteraciones; }
