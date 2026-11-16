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
	// actúa normalmente si no ha sido golpeada
	if (!shot) {
		// movimiento
		MobileObject::update(delta);
		// animación de vuelo
		accumulatedTime += delta; // se cuenta el tiempo
		if (accumulatedTime >= animationTime / 10) { // si ha pasado el tiempo de un frame
			accumulatedTime = 0; // se reinicia el contador
			if (animFrame < 9) animFrame++; // si no se ha llegado al ultimo frame se avanza
			else animFrame = 0; // si se ha llegado al ultimo frame se reinicia
		}
		// si la mariposa llega a arriba o abajo, cambia de dirección
		if (body.getTopLeftCorner().getY() + body.getHeight() < 0 || body.getTopLeftCorner().getY() > game->WINDOW_HEIGHT) {
			this->speed = Vector2D<float>(speed.getX(), -speed.getY());
		}
		// de vez en cuando, la mariposa cambia de dirección aleatoriamente
		
	}
	else { // cuando ha sido golpeada, cae hasta salir de la pantalla
		// movimiento
		MobileObject::update(delta);
		// si la mariposa se sale de la pantalla
		if (body.getTopLeftCorner().getY() > game->WINDOW_HEIGHT) {
			return false; // la mariposa ha salido de la pantalla
		}
	}
	return true;
}

bool Butterfly::hit(const Rectangle& obj)
{
	if (!shot && obj.hasIntersection(body)) {
		shot = true;
		return true;
	}
	return false;
}