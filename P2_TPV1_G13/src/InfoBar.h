#pragma once
#ifndef INFOBAR_H
#include "GameObject.h"
// Declaraciones anticipadas
class Game;
// Clase principal
class InfoBar : public GameObject
{
private:
	Rectangle arrows; // Rectangulo de la primera flecha
public:
	InfoBar(Game* game);
	void render() const override;
	bool update(float delta) override;
};
#endif // !INFOBAR_H



