#include <iostream>
#include <windows.h>
#include <conio.h>
#include<time.h>
using namespace std;

#include "Snake.h"
#include "Coordenada.h"

// ubicacion en coordenada de cada borde
#define BORDE_SUPERIOR  0
#define BORDE_INFERIOR  16
#define BORDE_IZQUIERDO 0
#define BORDE_DERECHO   30

void autopilot(Snake* &snk, Segmento* &comida);
//-----------------------------
void mostrarBordes();
void mostrarGameOver();
void mostrarPuntaje(int p);
void moverSnake(Snake* snk);
void mostrarComida(Segmento* comida);
bool verificarColicionConBordes(Snake* &snk);
bool verificarColicionConSnake(Snake* &snk);
//-----------------------------
void GoToXY(Coordenada c);
void OcultarCursor();
void cambiarColor(int color);
int  numeroAleatorioEntre(int a, int b);

////////////////////////////////////////////////////////////////////
int main(){
    // inicializacion
    srand(time(NULL));
    OcultarCursor();
    mostrarBordes();

    // crea la vibora de largo 5, horizontal, moviendose hacia la derecha
    Snake* snk = new Snake(DERECHA, 5, new Coordenada(13,9));
    // crea una comida en un lugar aleatorio con color aleatorio
    Segmento* comida = new Segmento(ARRIBA, new Coordenada(numeroAleatorioEntre(BORDE_IZQUIERDO+1, BORDE_DERECHO-1), numeroAleatorioEntre(BORDE_SUPERIOR+1, BORDE_INFERIOR-1)), NULL, NULL, numeroAleatorioEntre(1,14));
    int tecla = 0;
    int puntaje = 0;

    mostrarPuntaje(puntaje);

    // mientras no se presione ESC
    while (tecla != 27){
        // si se presiona una tecla
        if (kbhit()){
            tecla = getch(); // captura la tecla presionada
            // cambia la direccion de la vibora
            switch (tecla) {
            case ARRIBA:    snk->cambiarDireccion(ARRIBA);    break;
            case ABAJO:     snk->cambiarDireccion(ABAJO);     break;
            case IZQUIERDA: snk->cambiarDireccion(IZQUIERDA); break;
            case DERECHA:   snk->cambiarDireccion(DERECHA);   break;
            default:        continue;
            }
        }else {
            autopilot(snk, comida);
        }
        moverSnake(snk);
        mostrarComida(comida);

        if (verificarColicionConBordes(snk) || verificarColicionConSnake(snk)){
//        if (verificarColicionConBordes(snk)){
            //mostrarGameOver();
            tecla = 27;
            continue;
        }

        // si la coordenada de la cabeza de la vibora y la comida coinciden, se procede a la alimentacion
        if (Coordenada::relacion(*comida->getCoordenada(), *snk->getSegmento(1)->getCoordenada()) == IGUAL_IGUAL){
            snk->comer(comida);
            // genera una nueva comida
            comida = new Segmento(ARRIBA, new Coordenada(numeroAleatorioEntre(BORDE_IZQUIERDO+1, BORDE_DERECHO-1), numeroAleatorioEntre(BORDE_SUPERIOR+1, BORDE_INFERIOR-1)), NULL, NULL, numeroAleatorioEntre(1,14));
            // actualiza la puntuacion
            mostrarPuntaje(++puntaje);
        }
        // pausa
        //GoToXY(Coordenada(0,BORDE_INFERIOR+1));
        //system("PAUSE");
        Sleep(50);
    }

    GoToXY(Coordenada(0,BORDE_INFERIOR+1));
    cambiarColor(15);
    return 0;
}

void autopilot(Snake* &snk, Segmento* &comida){
    // Dependiendo de la ubicacion de la comida respecto a la cabeza
    // se dirige hacia la direccion mas cercana
    switch (Coordenada::relacion(*comida->getCoordenada(), *snk->getCabeza()->getCoordenada())) {
    case MENOR_MENOR: // la comida esta arriba a la izquierda
        if (abs(snk->getCabeza()->getCoordenada()->getX() - comida->getCoordenada()->getX()) < abs(snk->getCabeza()->getCoordenada()->getY() - comida->getCoordenada()->getY())){
            snk->cambiarDireccion(IZQUIERDA);
        }else{
            snk->cambiarDireccion(ARRIBA);
        }
        break;
    case MENOR_MAYOR: // la comida esta abajo a la izquierda
        if (abs(snk->getCabeza()->getCoordenada()->getX() - comida->getCoordenada()->getX()) < abs(snk->getCabeza()->getCoordenada()->getY() - comida->getCoordenada()->getY())){
            snk->cambiarDireccion(IZQUIERDA);
        }else{
            snk->cambiarDireccion(ABAJO);
        }
        break;
    case MAYOR_MENOR: // la comida esta arriba a la derecha
        if (abs(snk->getCabeza()->getCoordenada()->getX() - comida->getCoordenada()->getX()) < abs(snk->getCabeza()->getCoordenada()->getY() - comida->getCoordenada()->getY())){
            snk->cambiarDireccion(DERECHA);
        }else{
            snk->cambiarDireccion(ARRIBA);
        }
        break;
    case MAYOR_MAYOR: // la comida esta abajo a la derecha
        if (abs(snk->getCabeza()->getCoordenada()->getX() - comida->getCoordenada()->getX()) < abs(snk->getCabeza()->getCoordenada()->getY() - comida->getCoordenada()->getY())){
            snk->cambiarDireccion(DERECHA);
        }else{
            snk->cambiarDireccion(ABAJO);
        }
        break;
    // Si esta a la altura tanto horizontal o vertical
    case MENOR_IGUAL:
        snk->cambiarDireccion(IZQUIERDA);
        break;
    case MAYOR_IGUAL:
        snk->cambiarDireccion(DERECHA);
        break;
    case IGUAL_MENOR:
        snk->cambiarDireccion(ARRIBA);
        break;
    case IGUAL_MAYOR:
        snk->cambiarDireccion(ABAJO);
        break;
    // Esta comiendo
    case IGUAL_IGUAL:
        break;
    }

    // segun la direccion, verifica si mantener la nueva direccion implica chocar contra un borde
    switch (snk->getCabeza()->getProximaDireccion()) {
    case ARRIBA:
        if (snk->getCabeza()->getCoordenada()->getY() == BORDE_SUPERIOR+1){
            if ((BORDE_DERECHO-BORDE_IZQUIERDO)/2 - (snk->getCabeza()->getCoordenada()->getX() /2) < 0){
                snk->cambiarDireccion(IZQUIERDA);
            }else{
                snk->cambiarDireccion(DERECHA);
            }
        }
        break;
    case ABAJO:
        if (snk->getCabeza()->getCoordenada()->getY() == BORDE_INFERIOR-1){
            if ((BORDE_DERECHO-BORDE_IZQUIERDO)/2 - (snk->getCabeza()->getCoordenada()->getX() /2) < 0){
                snk->cambiarDireccion(IZQUIERDA);
            }else{
                snk->cambiarDireccion(DERECHA);
            }
        }
        break;
    case IZQUIERDA:
        if (snk->getCabeza()->getCoordenada()->getX()/2 == BORDE_IZQUIERDO+1){
            if ((BORDE_INFERIOR-BORDE_SUPERIOR)/2 - snk->getCabeza()->getCoordenada()->getY() < 0){
                snk->cambiarDireccion(ARRIBA);
            }else{
                snk->cambiarDireccion(ABAJO);
            }
        }
        break;
    case DERECHA:
        if (snk->getCabeza()->getCoordenada()->getX()/2 == BORDE_DERECHO-1){
            if ((BORDE_INFERIOR-BORDE_SUPERIOR)/2 - snk->getCabeza()->getCoordenada()->getY() < 0){
                snk->cambiarDireccion(ARRIBA);
            }else{
                snk->cambiarDireccion(ABAJO);
            }
        }
        break;
    }

    // si esta por chocar contra si misma, se dirige hacia donde haya mas espacio
    Coordenada* aux = new Coordenada(snk->getCabeza()->getCoordenada());
    aux->mover(snk->getDireccion());
    for (int i = 4; i <= snk->getLargo(); i++){
        if (Coordenada::relacion(*aux, *snk->getSegmento(i)->getCoordenada()) == IGUAL_IGUAL){
            Coordenada* c1 = NULL;
            Coordenada* c2 = NULL;
            Coordenada* borrar = NULL;
            aux->moverOpuesto(snk->getDireccion());

            switch (snk->getDireccion()) {
            case ARRIBA:
            case ABAJO:
                for (int i = 2; i <= snk->getLargo(); i++){
                    if (Coordenada::relacion(*snk->getSegmento(i)->getCoordenada(), *aux) == MENOR_IGUAL){
                        if (c1 != NULL){
                            if (Coordenada::relacion(*c1, *snk->getSegmento(i)->getCoordenada()) != MAYOR_IGUAL){
                                continue;
                            }
                        }
                        c1 = snk->getSegmento(i)->getCoordenada();
                    }
                }
                for (int i = 2; i <= snk->getLargo(); i++){
                    if (Coordenada::relacion(*snk->getSegmento(i)->getCoordenada(), *aux) == MAYOR_IGUAL){
                        if (c2 != NULL){
                            if (Coordenada::relacion(*c2, *snk->getSegmento(i)->getCoordenada()) != MAYOR_IGUAL){
                                continue;
                            }
                        }
                        c2 = snk->getSegmento(i)->getCoordenada();
                    }
                }

                if (c1 == NULL){
                    c1 = new Coordenada(BORDE_IZQUIERDO, aux->getY());
                    borrar = c1;
                }
                if (c2 == NULL){
                    c2 = new Coordenada(BORDE_DERECHO, aux->getY());
                    borrar = c2;
                }

                if (Coordenada::distancia(*c1, *aux) < Coordenada::distancia(*c2, *aux)){
                    snk->cambiarDireccion(DERECHA);
                }else{
                    snk->cambiarDireccion(IZQUIERDA);
                }

                if (borrar != NULL) delete borrar;
                break;
            case IZQUIERDA:
            case DERECHA:
                for (int i = 2; i <= snk->getLargo(); i++){
                    if (Coordenada::relacion(*snk->getSegmento(i)->getCoordenada(), *aux) == IGUAL_MENOR){
                        if (c1 != NULL){
                            if (Coordenada::relacion(*c1, *snk->getSegmento(i)->getCoordenada()) != IGUAL_MAYOR){
                                continue;
                            }
                        }
                        c1 = snk->getSegmento(i)->getCoordenada();
                    }
                }
                for (int i = 2; i <= snk->getLargo(); i++){
                    if (Coordenada::relacion(*snk->getSegmento(i)->getCoordenada(), *aux) == IGUAL_MAYOR){
                        if (c2 != NULL){
                            if (Coordenada::relacion(*c2, *snk->getSegmento(i)->getCoordenada()) != IGUAL_MENOR){
                                continue;
                            }
                        }
                        c2 = snk->getSegmento(i)->getCoordenada();
                    }
                }

                if (c1 == NULL){
                    c1 = new Coordenada(BORDE_INFERIOR, aux->getX()/2);
                    borrar = c1;
                }
                if (c2 == NULL){
                    c2 = new Coordenada(BORDE_SUPERIOR, aux->getX()/2);
                    borrar = c2;
                }

                if (Coordenada::distancia(*c1, *aux) < Coordenada::distancia(*c2, *aux)){
                    snk->cambiarDireccion(ABAJO);
                }else{
                    snk->cambiarDireccion(ARRIBA);
                }

                if (borrar != NULL) delete borrar;
                break;
            }
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////
void mostrarBordes(){
    cambiarColor(14);
    //bordes horizontales
    for (int i = BORDE_IZQUIERDO; i <= BORDE_DERECHO; i++){
        GoToXY(Coordenada(i, BORDE_SUPERIOR));
        printf("%c%c", 219, 219);
        GoToXY(Coordenada(i, BORDE_INFERIOR));
        printf("%c%c", 219, 219);
    }
    // bordes verticales
    for (int i = BORDE_SUPERIOR; i <= BORDE_INFERIOR; i++){
        GoToXY(Coordenada(BORDE_IZQUIERDO, i));
        printf("%c%c", 219, 219);
        GoToXY(Coordenada(BORDE_DERECHO, i));
        printf("%c%c", 219, 219);
    }
}
void mostrarGameOver(){
    // muestra un cartel del estilo:
    //  #############
    //  ##GAME#OVER##
    //  #############

    //define las coordenadas de referencia para dibujar el cartel
    int x = (BORDE_IZQUIERDO+BORDE_DERECHO)/2 - 3;
    int y = (BORDE_SUPERIOR+BORDE_INFERIOR)/2 - 1;
    cambiarColor(79); // color de fondo rojo con letras blancas
    GoToXY(Coordenada(x, y  ));     printf("             ");
    GoToXY(Coordenada(x, y+1));     printf("  GAME OVER  ");
    GoToXY(Coordenada(x, y+2));     printf("             ");
}
void mostrarPuntaje(int p){
    // coloca el cursor arriba a la derecha del campo de juego y muestra la puntuacion
    GoToXY(Coordenada(BORDE_DERECHO+1, BORDE_SUPERIOR));
    printf("Puntuacion: %d", p);
}
void moverSnake(Snake* snk){
    // posiciona el cursor en el ultimo segmento de la vibora y lo borra
    GoToXY(snk->getCola()->getCoordenada());
    cambiarColor(15);
    printf("%c%c", 32, 32);

    // avanza la vibora
    snk->mover();

    // recorre todos los segmentos colocando el cursor y cambiando el color para cada uno
    for (int i = snk->getLargo(); i > 0; i--){
        GoToXY(snk->getSegmento(i)->getCoordenada());
        cambiarColor(snk->getSegmento(i)->getColor());
        printf("%c%c", 219, 219);
    }
}
void mostrarComida(Segmento* comida){
    // relocaliza el cursor, cambia el color y escribe los caracteres de comida
    GoToXY(comida->getCoordenada());
    cambiarColor(comida->getColor());
    printf("%c%c", 177, 177);
}
bool verificarColicionConBordes(Snake* &snk){
    // verifica las coordenadas de la cabeza respecto al borde dependiendo dependiendo de la direccion del movimiento
    switch (snk->getDireccion()) {
    case ARRIBA:    return BORDE_SUPERIOR  == snk->getCabeza()->getCoordenada()->getY();
    case ABAJO:     return BORDE_INFERIOR  == snk->getCabeza()->getCoordenada()->getY();
    case IZQUIERDA: return BORDE_IZQUIERDO == snk->getCabeza()->getCoordenada()->getX() /2;
    case DERECHA:   return BORDE_DERECHO   == snk->getCabeza()->getCoordenada()->getX() /2;
    }
}
bool verificarColicionConSnake(Snake* &snk){
    for (int i = 2; i <= snk->getLargo(); i++){
        if (Coordenada::relacion(*snk->getCabeza()->getCoordenada(), *snk->getSegmento(i)->getCoordenada()) == IGUAL_IGUAL){
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////
void GoToXY(Coordenada c){		// Coloca el cursor en la ordenada indicada
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = static_cast<short>(c.getX());
    dwPos.Y = static_cast<short>(c.getY());;
    SetConsoleCursorPosition(hCon, dwPos);
}
void OcultarCursor(){			// Oculta el cursor
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}
void cambiarColor(int color){   // Cambia el color de escritura en consola
    // Necesita #include <windows.h>
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}
int numeroAleatorioEntre(int min, int max){ // Genera un numero aleatorio entre los pasados por parametro inclusive
    return min + rand() % (max +1 - min);
}
