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
	MobileObject(Game* g,Rectangle b, Texture* t, float v);
	virtual ~MobileObject() = default;
	void update(float delta) override;
};

#endif // !MOBILEOBJECT_H

