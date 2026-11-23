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
	const int animationTime = 500; // tiempo de la animacion de explotar, en milisegundos
	int color; // color del globo 0-6
	bool exploded = false; // para la animación de la explosión del globo
	int animFrame = 0; // para la animación de la explosión del globo
	float accumulatedTime = 0; // tiempo que ha pasado para la animación de la explosión del globo
public:
	// constructor
	Balloon(Game* g, Rectangle b, Vector2D<float> velY, int color);
	Balloon(Game* g, std::istream& in);
	// no hay que hacer destructor, xq no hay memoria dinámica

	// renderiza el globo en pantalla
	void render() const override;

	// update para el movimiento del globo
	bool update(float delta) override;

	// detector de colisiones
	bool hit(const Rectangle& obj) override;

	void Save(std::ostream& out) const override; 
};
#endif // !BALLOON_H



