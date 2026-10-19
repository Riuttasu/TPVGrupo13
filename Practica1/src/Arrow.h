#pragma once
#ifndef ARROW_H
#include "game.h"
#include "rectangle.h"
#include "texture.h"
#include "vector2D.h"
class Arrow
{
private:
	Game* collisions;
	Rectangle body;
	Vector2D<float> vel;
	Texture* texture;
public:
	Arrow(Game* game, Rectangle dims, Vector2D<float> velocity, Texture* text);
	~Arrow();
	void update();
	void render();
};
#define ARROW_H
#endif // !ARROW_H


