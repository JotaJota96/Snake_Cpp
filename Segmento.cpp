#include "Segmento.h"

Segmento::Segmento(Direccion d, Coordenada* c, Segmento* ant, Segmento* sig, int col){
    this->proximaDireccion = d;
    this->coordenada = c;
    this->anterior = ant;
    this->siguiente = sig;
    this->color = col;
}
Segmento::~Segmento(){
    delete this->coordenada;
    if (this->siguiente != NULL) this->siguiente->setAnterior(this->anterior);
    if (this->anterior != NULL) this->anterior->setSiguiente(this->siguiente);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Segmento::setProximaDireccion(Direccion d){
    this->proximaDireccion = d;
}
void Segmento::setAnterior(Segmento* s){
    this->anterior = s;
}
void Segmento::setSiguiente(Segmento* s){
    this->siguiente = s;
}
Direccion Segmento::getProximaDireccion(){
    return this->proximaDireccion;
}
Segmento* Segmento::getAnterior(){
    return this->anterior;
}
Segmento* Segmento::getSiguiente(){
    return this->siguiente;
}
Coordenada* Segmento::getCoordenada(){
    return this->coordenada;
}
int Segmento::getColor(){
    return this->color;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Segmento::moverEnCascada(){
    this->coordenada->mover(this->proximaDireccion);
    if (this->siguiente != NULL){
        this->siguiente->moverEnCascada();
    }
    if (this->anterior != NULL){
        this->proximaDireccion = this->anterior->getProximaDireccion();
    }
}











