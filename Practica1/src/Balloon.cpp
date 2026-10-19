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
	// luego se mirará la animación de la explosión del globo

	// render del globo normal (color que sea)
	texture->renderFrame(body.to_sdl(), color, 0);
}

// update para el movimiento del globo
bool Balloon::update(float delta){
	if (body.getTopLeftCorner().getY() + body.getHeight() < 0) {
		return false; // el globo ha salido de la pantalla
	}
	// else if para si el globo es estallado por una flecha
	else {
		// actualiza la posición del globo en base al deltaTime
		body.move(vel * delta);
		return true;
	}
}

// detector de colisiones
bool Balloon::Hit(const Rectangle& obj)
{
	return false;
}