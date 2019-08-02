#ifndef SNAKE_H
#define SNAKE_H
#include "Coordenada.h"
#include "Segmento.h"

class Snake{
private:
    Segmento* cabeza;
    Segmento* cola;
    int       largo;
public:
    Snake(Direccion d, int largo, Coordenada* coordenadaDeCabeza);
    ~Snake();

    int  getLargo();
    Segmento* getSegmento(int n);
    Segmento* getCabeza();
    Segmento* getCola();
    Direccion getDireccion();

    void cambiarDireccion(Direccion);
    void mover();
    void comer(Segmento* s);
};

#endif // SNAKE_H
