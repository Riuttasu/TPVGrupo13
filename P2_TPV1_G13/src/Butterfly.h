#pragma once
#ifndef BUTTERFLY_H
#define BUTTERFLY_H
#include "MobileObject.h"
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
// Declaraciones anticipadas
class Game;
// Clase principal

class Butterfly : public MobileObject
{
private:
	int type; // tipo de mariposa 0-3
	bool shot = false; // si ha sido golpeada caerá
	const int animationTime = 1000; // tiempo de la animación de vuelo, en milisegundos
	int animFrame = 0; // para la animación de vuelo
	int frameChange = -1; // positivo o negativo, para que la animación vaya hacia adelante o hacia atrás
	float accumulatedTime = 0; // tiempo que ha pasado para la animación de vuelo
	float randomTimer = 0; // tiempo en el que puede cambiar de dirección
public:
	//constructor
	Butterfly(Game* g, Rectangle b, Vector2D<float> velY, int type);
	Butterfly(Game* g, std::istream& in);
	// no hay que hacer destructor, xq no hay memoria dinámica

	// renderiza a la mariposa en pantalla
	void render() const override;

	// update para el movimiento de la mariposa
	bool update(float delta) override;

	// detector de colisiones
	bool hit(const Rectangle& obj) override;

	// Para guardar en archivo
	void Save(std::ostream& out) const override;
};

#endif // !BUTTERFLY_H

