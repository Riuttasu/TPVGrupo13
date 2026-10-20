#pragma once
#ifndef BOW_H
#include "rectangle.h"
#include "texture.h"
#include "game.h"
#include <SDL3/SDL.h>
// Declaraciones anticipadas
class Game;
class Bow
{
private:
	Game* game; // Puntero al juego para conseguir texturas 
	int dirY = 0; // Direccion de movimiento, 1 abajo, -1 arriba, 0 quieto
	Rectangle body; // Rectangulo donde se va a renderizar
	float vel = 20; // Velocidad de movimiento
	int numArrows = 5; // Numero de flechas
	bool strung = false; // Si esta armado o no
public:
	Bow(Rectangle dims, Game* game);
	void handleEvent(const SDL_Event& event);
	void update(float delta);
	void render() const; 
	void Shoot();
};
#define BOW_H
#endif // !BOW_H


