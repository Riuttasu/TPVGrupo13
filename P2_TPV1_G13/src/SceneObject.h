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
	int pointsHit = 0; // Puntos por ser colisionado
public:
	SceneObject(Game* g, Rectangle b, Texture* t);
	SceneObject(Game* g, std::istream& in, Texture* t); // Constructora por guardado
	virtual ~SceneObject() = default; // Destructora virtual
	void render() const override;
	virtual bool hit(const Rectangle& c);
	virtual void Save(std::ostream& out) const; // Para guardar en archivo
	virtual int getPoints() const { return pointsHit; } // Getter de los puntos por ser colisionado
};
#endif // !SCENEOBJECT_H


