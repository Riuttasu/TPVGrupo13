#pragma once
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
// Includes
#include "GameObject.h"
#include "vector2D.h"
// Clase principal
class SceneObject: public GameObject
{
protected:
	Vector2D<float> speed;
public:
	void update() override;
};
#endif // !SCENEOBJECT_H


