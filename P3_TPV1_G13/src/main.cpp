//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Practica 2 Grupo 13
// Basada en Plantilla de proyecto con SDL
//
#include <SDL3/SDL.h>
#include "game.h"
using namespace std;
int main(int argc, char* argv[])
{
	try {
		Game().run();
	}
	catch (const exception& e) {
		cout << e.what() << endl; // Lo pone por consola
		return -1;
	}

	return 0;
}
