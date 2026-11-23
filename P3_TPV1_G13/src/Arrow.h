#pragma once
#ifndef ARROW_H
#include "MobileObject.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "rectangle.h"
#include "vector2D.h"
// Declaraciones anticipadas
class Game; 
class Arrow : public MobileObject
{
private:
	int combo = 1; // Para sumar mas puntos
public:
	// Constructora
	Arrow(Game* g, Rectangle b, Vector2D<float> s = Vector2D(0.3f, 0.0f));
	Arrow(Game* g, std::istream& in);
	// Logica
	bool update(float delta) override;
	void hitLogic(SceneObject* hit);
	// Para guardar en archivo
	void Save(std::ostream& out) const override;
};
#define ARROW_H
#endif // !ARROW_H


