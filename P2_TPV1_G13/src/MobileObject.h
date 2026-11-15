#pragma once
#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H
// Includes
#include "SceneObject.h"
#include "rectangle.h"
// Declaracion anticipada
class Game; 
class Texture;
// Clase principal
class MobileObject : public SceneObject
{
protected:
	Vector2D<float> speed;
public:
	MobileObject(Game* g,Rectangle b, Texture* t, Vector2D<float> s);
	virtual ~MobileObject() = default; // Destructora virtual
	bool update(float delta) override;
};

#endif // !MOBILEOBJECT_H

