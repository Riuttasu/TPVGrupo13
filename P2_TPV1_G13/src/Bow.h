#pragma once
#ifndef BOW_H
#include "game.h"
#include "SceneObject.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
// Declaraciones anticipadas
class Game;
class Bow : public SceneObject
{
private:
	float vel = 1; // Velocidad de movimiento
	int dirY = 0; // Direccion de movimiento, 1 abajo, -1 arriba, 0 quieto
	int numArrows = 5; // Numero de flechas
	bool strung = false; // Si esta armado o no
public:
	// Constructora
	Bow(Game* game, Rectangle b, int a);
	// Getters
	int GetArrowNum() const { return numArrows; };
	// Setters
	void SetArrowNum(int n) { numArrows = n; };
	// Logica
	void handleEvent(const SDL_Event& event);
	bool update(float delta) override;
	void render() const override;
	// Disparo
	void Shoot();
};
#define BOW_H
#endif // !BOW_H


