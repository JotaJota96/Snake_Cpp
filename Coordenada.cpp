#include "Coordenada.h"


Coordenada::Coordenada(){
    this->x = 0;
    this->y = 0;
}
Coordenada::Coordenada(int x, int y){
    this->x = x*2;
    this->y = y;
}
Coordenada::Coordenada(Coordenada* c){
    this->x = c->getX();
    this->y = c->getY();
}
Coordenada::~Coordenada(){

}


/////////////////////////////////////////////////////////////////////////////////////////////
RelacionDeCoordenadas Coordenada::relacion(Coordenada &c1, Coordenada &c2){
    // no encontre otra manera mas corta de realizar la doble comparacion
    if (c1.getX() <  c2.getX() && c1.getY() <  c2.getY()) return MENOR_MENOR;
    if (c1.getX() <  c2.getX() && c1.getY() == c2.getY()) return MENOR_IGUAL;
    if (c1.getX() <  c2.getX() && c1.getY() >  c2.getY()) return MENOR_MAYOR;
    if (c1.getX() == c2.getX() && c1.getY() <  c2.getY()) return IGUAL_MENOR;
    if (c1.getX() == c2.getX() && c1.getY() == c2.getY()) return IGUAL_IGUAL;
    if (c1.getX() == c2.getX() && c1.getY() >  c2.getY()) return IGUAL_MAYOR;
    if (c1.getX() >  c2.getX() && c1.getY() <  c2.getY()) return MAYOR_MENOR;
    if (c1.getX() >  c2.getX() && c1.getY() == c2.getY()) return MAYOR_IGUAL;
    if (c1.getX() >  c2.getX() && c1.getY() >  c2.getY()) return MAYOR_MAYOR;
    return IGUAL_IGUAL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
int Coordenada::getX(){
    return this->x;
}
int Coordenada::getY(){
    return this->y;
}
void Coordenada::setX(int x){
    this->x = x*2;
}
void Coordenada::setY(int y){
    this->y = y;

}

/////////////////////////////////////////////////////////////////////////////////////////////
void Coordenada::mover(Direccion d){
    switch (d) {
    case ARRIBA:    this->up();    break;
    case ABAJO:     this->down();  break;
    case IZQUIERDA: this->left();  break;
    case DERECHA:   this->right(); break;
    }
}
void Coordenada::moverOpuesto(Direccion d){
    switch (d) {
    case ARRIBA:    this->down();  break;
    case ABAJO:     this->up();    break;
    case IZQUIERDA: this->right(); break;
    case DERECHA:   this->left();  break;
    }
}
void Coordenada::down(){
    y++;
}
void Coordenada::up(){
    y--;
}
void Coordenada::left(){
    x-= 2;
}
void Coordenada::right(){
    x+= 2;
}
