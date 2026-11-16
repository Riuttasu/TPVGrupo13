#include "Balloon.h"


// constructor del globo
Balloon::Balloon(Game* g, Rectangle b, Vector2D<float> velY, int color)
	: MobileObject(g,b,g->getTexture(Game::TextureName::BALLOON), velY), color(color)
{
	color = color % 7; // por si se introduce un color fuera de rango
}

// render del globo
void Balloon::render() const{
	// el color del globo depende del color que se le pase al constructor
	// la animación de la explosión time 6 frames (0-5) y solo se renderiza si el globo ha sido estallado
	texture->renderFrame(body.to_sdl(), color, animFrame);
}

// update para el movimiento del globo
bool Balloon::update(float delta){
	// Movimiento
	MobileObject::update(delta);
	// si el globo se sale de la pantalla
	if (body.getTopLeftCorner().getY() + body.getHeight() < 0) {
		return false; // el globo ha salido de la pantalla
	}
	// si el globo es estallado por una flecha y aún no se ha terminado la animación de la explosión
	else if (exploded) {
		// el globo no se mueve
		if (animFrame < 5) {
			animFrame++; // avanza la animación de la explosión
		}
		else {
			return false; // el globo ha terminado la animación de la explosión
		}
	}
	else return true;
}

// detector de colisiones
bool Balloon::hit(const Rectangle& obj)
{
	if (!exploded && obj.hasIntersection(body)){
		exploded = true;
		return true;
	}
	return false;
}