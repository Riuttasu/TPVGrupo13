#include "Balloon.h"


// constructor del globo
Balloon::Balloon(float posX, float posY, int color, float velY, Texture* texture){
	this->body = Rectangle(Point2D<float>(posX, posY), 60, 90);
	this->color = color;
	this->vel = Vector2D<float>(0, -velY); // negativo ya que el globo sube
	this->texture = texture;
}

// render del globo
void Balloon::render() const{
	// el color del globo depende del color que se le pase al constructor
	// la animación de la explosión time 6 frames (0-5) y solo se renderiza si el globo ha sido estallado
	texture->renderFrame(body.to_sdl(), color, animFrame);
}

// update para el movimiento del globo
bool Balloon::update(float delta){
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
	else {
		// actualiza la posición del globo en base al deltaTime
		body.move(vel * delta);
		return true;
	}
}

// detector de colisiones
bool Balloon::Hit(const Rectangle& obj)
{
	if (obj.hasIntersection(body)){
		exploded = true;
		return true;
	}
	return false;
}