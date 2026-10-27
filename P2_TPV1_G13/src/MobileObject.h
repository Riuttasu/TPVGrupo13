#pragma once
#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H
// Includes
#include "SceneObject.h"
// Clase principal
class MobileObject : public SceneObject
{
protected:
	Vector2D<float> speed;
public:
	void update() override;
};

#endif // !MOBILEOBJECT_H

