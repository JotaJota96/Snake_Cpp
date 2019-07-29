#ifndef SNAKE_H
#define SNAKE_H
#include "Coordenada.h"
#include "Segmento.h"

class Snake{
private:
    Direccion proximaDireccion;
    Segmento* cabeza;
    int       largo;

public:
    Snake(Direccion d, int largo, Coordenada* coordenadaDeCabeza);
    ~Snake();

    void setProximaDireccion(Direccion);
    int  getLargo();

    void mover();
    void comer();
    bool puedeIrHacia(Direccion d);
};

#endif // SNAKE_H
