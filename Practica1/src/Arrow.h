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
	const Game* game;
	Rectangle body;
	Vector2D<float> vel = Vector2D(3.0f,0.0f);
public:
	// Constructora
	Arrow(Rectangle dims, const Game* g);
	// Destructora
	~Arrow();
	void update(float delta);
	void render();
};
#define ARROW_H
#endif // !ARROW_H


