#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// Includes
#include "game.h"
// Clase 
class GameObject
{
protected:
	Game* game;
public:
	virtual void render() const;
	virtual void update();
};
#endif // !GAMEOBJECT_H


