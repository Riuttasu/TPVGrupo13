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
	bool Hit(const Rectangle& obj);
};
#endif // !BALLOON_H



