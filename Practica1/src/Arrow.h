#pragma once
#ifndef ARROW_H
#include "game.h"
#include "rectangle.h"
#include "vector2D.h"
class Arrow
{
private:
	Game* col;
	Rectangle body;
	Vector2D<float> vel;
};
#define ARROW_H
#endif // !ARROW_H


