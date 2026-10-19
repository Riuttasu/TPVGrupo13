#pragma once
#ifndef ARROW_H
#include "game.h"
#include "rectangle.h"
#include "texture.h"
#include "vector2D.h"
class Game; // no se si deberia hacer esto
class Arrow
{
private:
	Game* collisions;
	Rectangle body;
	Vector2D<float> vel;
public:
	// Constructora
	Arrow(Game* game, Rectangle dims, Vector2D<float> velocity);
	// Destructora
	~Arrow();
	void update();
	void render();
};
#define ARROW_H
#endif // !ARROW_H


