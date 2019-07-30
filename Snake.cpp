#include "Snake.h"

Snake::Snake(Direccion d, int l, Coordenada* coordenadaDeCabeza){
    this->cabeza = new Segmento(d, coordenadaDeCabeza, NULL, NULL, 15);
    Segmento* segAux = cabeza;
    Coordenada* corAux;

    for (int i = 1; i < l; i++){
        corAux = new Coordenada(segAux->getCoordenada());
        corAux->moverOpuesto(d);
        segAux->setSiguiente(new Segmento(d, corAux, segAux, NULL, i));
        segAux = segAux->getSiguiente();
    }

    this->largo = l;
}
Snake::~Snake(){
    Segmento* borrar;
    while (cabeza->getSiguiente() != NULL){
        borrar = cabeza->getSiguiente();
        cabeza->setSiguiente(borrar->getSiguiente());
        delete borrar;
    }
    delete this->cabeza;
}





/////////////////////////////////////////////////////////////////////////////////////////////
int Snake::getLargo(){
    return  this->largo;
}
Segmento* Snake::getSegmento(int n){
    Segmento* s = this->cabeza;
    for (int i = 1; i < n && s->getSiguiente() != NULL; i++){
        s = s->getSiguiente();
    }
    return s;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Snake::cambiarDireccion(Direccion d){
    switch (d) {
    case ARRIBA:    if (cabeza->getSiguiente()->getProximaDireccion() == ABAJO)     return; break;
    case ABAJO:     if (cabeza->getSiguiente()->getProximaDireccion() == ARRIBA)    return; break;
    case IZQUIERDA: if (cabeza->getSiguiente()->getProximaDireccion() == DERECHA)   return; break;
    case DERECHA:   if (cabeza->getSiguiente()->getProximaDireccion() == IZQUIERDA) return; break;
    }
    this->cabeza->setProximaDireccion(d);
}
void Snake::mover(){
    cabeza->moverEnCascada();
}
void Snake::comer(){

}
