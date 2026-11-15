#pragma once
#ifndef BALLOON_H
#define BALOOON_H
#include "MobileObject.h"
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
// Declaraciones anticipadas
class Game;
// Clase principal
class Balloon : public MobileObject
{
private:
	const int animationTime = 500; // Tiempo de la animacion de explotar, en milisegundos
	int color; // Color del globo 0-6
	bool exploded = false; // para la animación de la explosión del globo
	int animFrame = 0; // para la animación de la explosión del globo
public:
	// constructor
	Balloon(Game* g, Rectangle b, Vector2D<float> velY, int color = 1);

	// no hay que hacer destructor, xq no hay memoria dinámica

	// renderiza el globo en pantalla
	void render() const override;

	// update para el movimiento del globo
	bool update(float delta) override;

	// detector de colisiones
	bool Hit(const Rectangle& obj);
};
#endif // !BALLOON_H



