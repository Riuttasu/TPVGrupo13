#pragma once
#ifndef BALLOON_H
#define BALOOON_H
#include "rectangle.h"
#include "texture.h"
class Balloon
{
private:
	Rectangle body;
	int color;
	Vector2D<float> vel;
	Texture* texture;
public:
	// constructor
	Balloon(float posX, float posY, int color, float velY, Texture* texture);

	// no hay que hacer destructor, xq no hay memoria dinámica

	// renderiza el globo en pantalla
	void render() const;

	// update para el movimiento del globo
	bool update(float delta);

	// detector de colisiones
	bool Hit(const Rectangle& obj);
};
#endif // !BALLOON_H



