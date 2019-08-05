#ifndef COORDENADA_H
#define COORDENADA_H
#include "math.h"

/* Esta clase esta pensada para representar posiciones en la consola tratandola como una cuadricula
 * Para que la cuadricula sea perfecta (basada en cuadrados), al mover horizontalmente se incremente en 2 el valor X
 * Esto es asi porque los caracteres en consola tienen de ancho la mitad del alto
 */

// Posibles movimientos
enum Direccion {ARRIBA    = 72,
                ABAJO     = 80,
                IZQUIERDA = 75,
                DERECHA   = 77};

// Resultados de comparacion de coordenadas
// El valor obtenido representa la relacion primero en el eje X y luego en el eje Y
enum RelacionDeCoordenadas {MENOR_MENOR,
                            MENOR_IGUAL,
                            MENOR_MAYOR,
                            IGUAL_MENOR,
                            IGUAL_IGUAL,
                            IGUAL_MAYOR,
                            MAYOR_MENOR,
                            MAYOR_IGUAL,
                            MAYOR_MAYOR};

class Coordenada{
private:
    int x;
    int y;
public:
    Coordenada();
    Coordenada(int x, int y);
    Coordenada(Coordenada*);
    ~Coordenada();

    static RelacionDeCoordenadas relacion(Coordenada &c1, Coordenada &c2);
    static float                 distancia(Coordenada &c1, Coordenada &c2);

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    void mover(Direccion d);
    void moverOpuesto(Direccion d);
    void down();
    void up();
    void left();
    void right();
};

#endif // COORDENADA_H
