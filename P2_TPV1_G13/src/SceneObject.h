#pragma once
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
// Includes
#include "GameObject.h"
#include "rectangle.h"
// Declaraciones anticipadas
class Game;
class Texture;
// Clase principal
class SceneObject: public GameObject
{
protected:
	Rectangle body;
	Texture* texture;
public:
	SceneObject(Game* g, Rectangle b, Texture* t);
	virtual ~SceneObject() = default; // Destructora virtual
	void render() const override;
	virtual bool hit(const Rectangle& c);
};
#endif // !SCENEOBJECT_H


