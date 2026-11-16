#include "Butterfly.h"

// constructor de la mariposa
Butterfly::Butterfly(Game* g, Rectangle b, Vector2D<float> velY, int type)
	: MobileObject(g, b, g->getTexture(Game::TextureName::BUTTERFLY), velY), type(type)
{
	type = type % 4; // por si se introduce un tipo fuera de rango
}

// render de la mariposa
void Butterfly::render() const {
	// la animación de vuelo time 10 frames (0-9)
	// hay 4 tipos de mariposa, que vienen determinados por el parámetro type que se le pasa al constructor
	texture->renderFrame(body.to_sdl(), type, animFrame);
}

// update de la mariposa
bool Butterfly::update(float delta) {
	// movimiento
	MobileObject::update(delta);
	if (!shot) {
		// si la mariposa llega a arriba o abajo, cambia de dirección
		if (body.getTopLeftCorner().getY() + body.getHeight() < 0 || body.getTopLeftCorner().getY() > game->WINDOW_HEIGHT) {
			this->speed = Vector2D<float>(speed.getX(), -speed.getY());
		}
		// animación de vuelo
	}
	return true;
}