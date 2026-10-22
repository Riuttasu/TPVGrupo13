#pragma once
#ifndef ARROW_H
#include "game.h"
#include "rectangle.h"
#include "texture.h"
#include "vector2D.h"
// Declaraciones anticipadas
class Game; 
class Arrow
{
private:
	// Puntero al juego
	const Game* game;
	// Cuerpo en el que va a ser renderizado
	Rectangle body;
	// Velocidad
	Vector2D<float> vel;
public:
	// Getters
	Rectangle GetDims() const { return body; };
	// Constructora
	Arrow(Rectangle dims, const Game* g, Vector2D<float> velocity = Vector2D(0.3f, 0.0f));
	// Logica
	bool update(float delta);
	void render() const;
};
#define ARROW_H
#endif // !ARROW_H


