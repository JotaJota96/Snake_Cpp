#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "Coordenada.h"

enum Direccion {ARRIBA    = 72,
                ABAJO     = 80,
                IZQUIERDA = 77,
                DERECHA   = 75};

class Segmento{
private:
    Direccion   proximaDireccion;
    Segmento*   anterior;
    Segmento*   siguiente;
    Coordenada* coordenada;
public:
    Segmento(Direccion* d, Coordenada* c, Segmento* ant, Segmento* sig);
    ~Segmento();

    void setProximaDireccion(Direccion d);
    void setAnterior(Segmento* s);
    void setSiguiente(Segmento* s);
    Direccion   getProximaDireccion();
    Segmento*   getAnterior();
    Segmento*   getSiguiente();
    Coordenada* getCoordenada();

    void mover();
};

#endif // SEGMENTO_H
