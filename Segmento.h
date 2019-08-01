#ifndef SEGMENTO_H
#define SEGMENTO_H
#include <iostream>
#include "Coordenada.h"

class Segmento{
private:
    Direccion   proximaDireccion;
    Segmento*   anterior;
    Segmento*   siguiente;
    Coordenada* coordenada;
    int         color;
    Segmento* comidaEnDigesta; // la comida que se está digiriendo
public:
    Segmento(Direccion d, Coordenada* c, Segmento* ant, Segmento* sig, int color);
    ~Segmento();

    void setProximaDireccion(Direccion d);
    void setAnterior(Segmento* s);
    void setSiguiente(Segmento* s);
    Direccion   getProximaDireccion();
    Segmento*   getAnterior();
    Segmento*   getSiguiente();
    Coordenada* getCoordenada();
    int         getColor();

    void moverEnCascada();
    void digerirComida(Segmento* s);
};

#endif // SEGMENTO_H
