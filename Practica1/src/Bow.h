#pragma once
#ifndef BOW_H
#include "rectangle.h"
#include "texture.h"
#include <SDL3/SDL.h>
class Bow
{
private:
	enum dir
	{
		DOWN, UP, STILL
	};
	Rectangle body;
	const Texture* texture;
	float vel;
	int numArrows;
	bool strung;
public:
	Bow();
	Bow(const Rectangle& dims,const Texture* text, float velocity, int numarrow, bool arm);
	~Bow();
	void handleEvent(const SDL_Event& event);
	void update();
	void render(); 
};
#define BOW_H
#endif // !BOW_H


