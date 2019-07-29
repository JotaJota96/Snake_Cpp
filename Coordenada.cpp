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



void Coordenada::mover(Direccion d){
    switch (d) {
    case ARRIBA:    this->up();    break;
    case ABAJO:     this->down();  break;
    case IZQUIERDA: this->left();  break;
    case DERECHA:   this->right(); break;
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
