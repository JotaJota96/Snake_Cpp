#include <iostream>
#include <windows.h>
#include <conio.h>
#include<time.h>
using namespace std;

#include "Snake.h"
#include "Coordenada.h"

#define BORDE_SUPERIOR  0
#define BORDE_INFERIOR  19
#define BORDE_IZQUIERDO 0
#define BORDE_DERECHO   35

void mostrarBordes();
//-----------------------------
void GoToXY(Coordenada c);
void OcultarCursor();
void cambiarColor(int color);
int  numeroAleatorioEntre(int a, int b);
////////////////////////////////////////////////////////////////////
int main(){
    srand(time(NULL));
    OcultarCursor();
    mostrarBordes();

    Snake* snk = new Snake(DERECHA, 10, new Coordenada(17,9));
    Segmento* comida = NULL;
    int tecla = 0;

    while (tecla != 27){
        if (kbhit()){
            tecla = getch();

            switch (tecla) {
            case ARRIBA:    snk->cambiarDireccion(ARRIBA);    break;
            case ABAJO:     snk->cambiarDireccion(ABAJO);     break;
            case IZQUIERDA: snk->cambiarDireccion(IZQUIERDA); break;
            case DERECHA:   snk->cambiarDireccion(DERECHA);   break;
            default:        continue;
            }
        }


        if (comida == NULL){
            comida = new Segmento(ARRIBA, new Coordenada(numeroAleatorioEntre(BORDE_IZQUIERDO+1, BORDE_DERECHO-1), numeroAleatorioEntre(BORDE_SUPERIOR+1, BORDE_INFERIOR-1)), NULL, NULL, numeroAleatorioEntre(1,14));
        }

        GoToXY(snk->getCola()->getCoordenada());
        cambiarColor(15);
        printf("%c%c", 32, 32);

        snk->mover();

        for (int i = snk->getLargo(); i > 0; i--){
            GoToXY(snk->getSegmento(i)->getCoordenada());
            cambiarColor(snk->getSegmento(i)->getColor());
            printf("%c%c", 219, 219);
        }

        GoToXY(comida->getCoordenada());
        cambiarColor(comida->getColor());
        printf("%c%c", 177, 177);


        if (Coordenada::relacion(*comida->getCoordenada(), *snk->getSegmento(1)->getCoordenada()) == IGUAL_IGUAL){
            snk->comer(comida);
            comida = NULL;
        }

        Sleep(250);
    }

    GoToXY(Coordenada(0,0));
    cambiarColor(15);
    return 0;
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
void cambiarColor(int color){
    // Necesita #include <windows.h>
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}
int numeroAleatorioEntre(int min, int max){
    return min + rand() % (max +1 - min);
}
////////////////////////////////////////////////////////////////////
void mostrarBordes(){
    cambiarColor(15);
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
