#include <iostream>
//#include <iostream>
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
void GoToXY(int x, int y);
void OcultarCursor();
void cambiarColor(int color);

int main(){

    return 0;
}
////////////////////////////////////////////////////////////////////
void oToXY(int x, int y){		// Coloca el cursor en la ordenada indicada
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = static_cast<short>(x);
    dwPos.Y = static_cast<short>(y);;
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
