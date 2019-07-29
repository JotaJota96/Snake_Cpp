#ifndef COORDENADA_H
#define COORDENADA_H

/* Esta clase esta pensada para representar posiciones en la consola tratandola como una cuadricula
 * Para que la cuadricula sea perfecta (basada en cuadrados), al mover horizontalmente se incremente en 2 el valor X
 * Esto es asi porque los caracteres en consola tienen de ancho la mitad del alto
 */

enum Direccion {ARRIBA    = 72,
                ABAJO     = 80,
                IZQUIERDA = 77,
                DERECHA   = 75};


class Coordenada{
private:
    int x;
    int y;
public:
    Coordenada();
    Coordenada(int x, int y);
    Coordenada(Coordenada*);
    ~Coordenada();

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    void mover(Direccion d);
    void down();
    void up();
    void left();
    void right();
};

#endif // COORDENADA_H
