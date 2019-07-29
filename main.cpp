#include <iostream>
#include <windows.h>
//#include <conio.h>
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
    Segmento* s1 = new Segmento(DERECHA, new Coordenada(1,4), NULL, NULL, 1);
    Segmento* s2 = new Segmento(ABAJO, new Coordenada(1,3), s1,   NULL, 2);
    Segmento* s3 = new Segmento(ABAJO, new Coordenada(1,2), s2,   NULL, 3);
    Segmento* s4 = new Segmento(ABAJO, new Coordenada(1,1), s3,   NULL, 4);
    s1->setSiguiente(s2);
    s2->setSiguiente(s3);
    s3->setSiguiente(s4);

    for (int f = 0; f < 10; f++){
        for (Segmento* s = s1; s != NULL; s = s->getSiguiente()){
            GoToXY(s->getCoordenada());
            cambiarColor(s->getColor());
            printf("%c%c", 219, 219);
        }
        Sleep(1000);

        for (Segmento* s = s1; s != NULL; s = s->getSiguiente()){
            GoToXY(s->getCoordenada());
            printf("%c%c", 32, 32);
        }
        s1->moverEnCascada();
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
