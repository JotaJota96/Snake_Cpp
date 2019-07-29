#include "Coordenada.h"


Coordenada::Coordenada(){
    this->x = 0;
    this->y = 0;
}
Coordenada::Coordenada(int x, int y){
    if (x % 2 != 0){
        this->x = x-1;
    }else {
        this->x = x;
    }
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
void Coordenada::setX(int x){    if (x % 2 != 0){
        this->x = x-1;
    }else {
        this->x = x;
    }
}
void Coordenada::setY(int y){
    this->y = y;

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
