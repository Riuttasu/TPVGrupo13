#pragma once
#ifndef INFOBAR_H
#include "game.h"
// Declaraciones anticipadas
class Game;
// Clase principal
class InfoBar
{
private:
	const Game* game; // Puntero al game para conseguir dimensiones y estadisticas
	Rectangle arrows; // Rectangulo de la primera flecha
public:
	InfoBar(const Game* game);
	void render();
};
#endif // !INFOBAR_H



