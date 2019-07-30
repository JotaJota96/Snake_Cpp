#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

#include "Snake.h"
#include "Coordenada.h"

Coordenada* c = new Coordenada(10,10);
Snake* snake;

void mostrarBordes();
void mostrarSnake();
//-----------------------------
void GoToXY(Coordenada c);
void OcultarCursor();
void cambiarColor(int color);

////////////////////////////////////////////////////////////////////
int main(){
    // codigo de prueba

    OcultarCursor();
    int largo = 5;
    Snake* snk = new Snake(ABAJO, largo, new Coordenada(5,5));
    int tecla;

    while (true){
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

        for (int i = 1; i <= largo; i++){
            GoToXY(snk->getSegmento(i)->getCoordenada());
            printf("%c%c", 32, 32);
        }
        snk->mover();

        for (int i = 1; i <= largo; i++){
            GoToXY(snk->getSegmento(i)->getCoordenada());
            cambiarColor(snk->getSegmento(i)->getColor());
            printf("%c%c", 219, 219);
        }
        Sleep(500);
    }


    GoToXY(Coordenada(0,15));
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
