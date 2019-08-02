#include "Segmento.h"

Segmento::Segmento(Direccion d, Coordenada* c, Segmento* ant, Segmento* sig, int col){
    this->proximaDireccion = d;
    this->coordenada = c;
    this->anterior = ant;
    this->siguiente = sig;
    this->comidaEnDigesta = NULL;
    this->color = col;
}
Segmento::~Segmento(){
    // libera la memoria y reestablece las conexciones para mantener la coherencia
    delete this->coordenada;
    if (this->siguiente != NULL)       this->siguiente->setAnterior(this->anterior);
    if (this->anterior  != NULL)       this->anterior->setSiguiente(this->siguiente);
    if (this->comidaEnDigesta != NULL) delete comidaEnDigesta;
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
    // actualiza el valor de la coordenada del segmento actual
    this->coordenada->mover(this->proximaDireccion);

    // si el segmento actual no es el ultimo
    if (this->siguiente != NULL){
        // llama a mover al siguiente segmento (recursividad)
        this->siguiente->moverEnCascada();
        // le pasa al siguiente segmento la comida que estaba digiriendo el segmento actual
        this->siguiente->digerirComida(this->comidaEnDigesta);
        this->comidaEnDigesta = NULL;
    }else {
        // si el segmento actual es el ultimo y estaba digiriendo comida
        if (this->comidaEnDigesta != NULL){
            // se realizan las conexiones y define la direccion del nuevo segmento
            this->siguiente = this->comidaEnDigesta;
            this->comidaEnDigesta->setAnterior(this);
            this->comidaEnDigesta->setProximaDireccion(this->proximaDireccion);
            this->comidaEnDigesta = NULL;
            // el segmento recien agregado no se movera hasta la proxima llamada recursiva
        }
    }
    // si el segmento actual no es el primero
    if (this->anterior != NULL){
        // actualiza la proxima direccion de movimiento en base a la del segmento anterior
        this->proximaDireccion = this->anterior->getProximaDireccion();
    }
}
void Segmento::digerirComida(Segmento* s){
    this->comidaEnDigesta = s;
}











