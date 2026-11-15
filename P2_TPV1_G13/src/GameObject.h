#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// Includes
#include "game.h"
// Declaración anticipada
class Game;
// Clase 
class GameObject
{
protected:
	Game* game;
public:
	GameObject(Game* g);
	virtual ~GameObject() = default; // Destructora virtual importante
	virtual void render() const;
	virtual void update(float delta) = 0; // Funcion puramente virtual
};
#endif // !GAMEOBJECT_H


