#pragma once
#ifndef INFOBAR_H
#include "GameObject.h"
#include <string>
// Declaraciones anticipadas
class Game;
// Clase principal
class InfoBar : public GameObject
{
private:
	Rectangle arrows; // Rectangulo de la primera flecha
	TTF_Text* text; // Texto para puntos
	TTF_TextEngine* engine; // Motor
	TTF_Font* font; // Fuente
public:
	InfoBar(Game* game,TTF_TextEngine* e, TTF_Font* f);
	~InfoBar();
	void render() const override;
	bool update(float delta) override;
};
#endif // !INFOBAR_H



