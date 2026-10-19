#pragma once
#ifndef BALLOON_H
#define BALOOON_H
#include "rectangle.h"
class Balloon
{
private:
	Rectangle body;
	int color;
	Vector2D<float> vel;
public:
	// constructor
	Balloon(float posX, float posY, int color, float velY);

	// no hay que hacer destructor, xq no hay memoria dinámica

	bool Hit(const Rectangle& obj);
};
#endif // !BALLOON_H



