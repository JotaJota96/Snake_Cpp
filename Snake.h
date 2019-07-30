#ifndef SNAKE_H
#define SNAKE_H
#include "Coordenada.h"
#include "Segmento.h"

class Snake{
private:
    Segmento* cabeza;
    int       largo;

public:
    Snake(Direccion d, int largo, Coordenada* coordenadaDeCabeza);
    ~Snake();

    int  getLargo();
    Segmento* getSegmento(int n);

    void cambiarDireccion(Direccion);
    void mover();
    void comer();
};

#endif // SNAKE_H
