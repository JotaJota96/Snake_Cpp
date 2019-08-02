#include "Snake.h"

Snake::Snake(Direccion d, int l, Coordenada* coordenadaDeCabeza){
    // crea el primer segmento
    this->cabeza = new Segmento(d, coordenadaDeCabeza, NULL, NULL, 15);
    this->cola = cabeza;

    // crea y conecta los siguientes segmentos
    Coordenada* corAux;
    for (int i = 1; i < l; i++){
        corAux = new Coordenada(this->cola->getCoordenada());
        corAux->moverOpuesto(d);
        this->cola->setSiguiente(new Segmento(d, corAux, this->cola, NULL, i));
        this->cola = this->cola->getSiguiente();
    }

    this->largo = l;
}
Snake::~Snake(){
    // mientras hayan dos o mas segmentos, se borra el ultimo
    while (this->cola->getAnterior() != NULL){
        this->cola = this->cola->getAnterior();
        delete this->cola->getSiguiente();
    }
    delete this->cola;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int Snake::getLargo(){
    return  this->largo;
}
Segmento* Snake::getSegmento(int n){
    Segmento* s = this->cabeza;
    // retorna el segmento en la ubicacion indicada o el ultimo
    for (int i = 1; i < n && s->getSiguiente() != NULL; i++){
        s = s->getSiguiente();
    }
    return s;
}
Segmento* Snake::getCabeza(){
    return this->cabeza;
}
Segmento* Snake::getCola(){
    return this->cola;
}
Direccion Snake::getDireccion(){
    return this->cabeza->getProximaDireccion();
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Snake::cambiarDireccion(Direccion d){
    // cambia la direccion si y solo si no es opuesta a la direccion actual
    switch (d) {
    case ARRIBA:    if (cabeza->getSiguiente()->getProximaDireccion() == ABAJO)     return; break;
    case ABAJO:     if (cabeza->getSiguiente()->getProximaDireccion() == ARRIBA)    return; break;
    case IZQUIERDA: if (cabeza->getSiguiente()->getProximaDireccion() == DERECHA)   return; break;
    case DERECHA:   if (cabeza->getSiguiente()->getProximaDireccion() == IZQUIERDA) return; break;
    }
    this->cabeza->setProximaDireccion(d);
}
void Snake::mover(){
    // manda a mover todos los segmentos
    this->cabeza->moverEnCascada();
    // si la cola tiene un segmento siguiente, ya no es cola porque termino la digestion de una comida
    if (this->cola->getSiguiente() != NULL){
        // actualiza el largo y la nueva cola
        this->largo++;
        this->cola = this->cola->getSiguiente();
    }
}
void Snake::comer(Segmento* s){
    this->cabeza->digerirComida(s);
}












