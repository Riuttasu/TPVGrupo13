#include "Balloon.h"


// constructor del globo
Balloon::Balloon(float posX, float posY, int color, float velY, Texture* texture){
	this->body = Rectangle(Point2D<float>(posX, posY), 40, 60);
	this->color = color;
	this->vel = Vector2D<float>(0, -velY); // negativo ya que el globo sube
	this->texture = texture;
}

// render del globo
void Balloon::render() const{
	SDL_FRect destRect;
	destRect.x = body.getTopLeftCorner().getX();
	destRect.y = body.getTopLeftCorner().getY();
	destRect.w = body.getWidth();
	destRect.h = body.getHeight();
	// luego se mirará la animación de la explosión del globo
	texture->renderFrame(destRect, color, 0);
}

// update para el movimiento del globo
bool Balloon::update(float delta){
	if (this->body.getTopLeftCorner().getY() + this->body.getHeight() < 0) {
		return false; // el globo ha salido de la pantalla
	}
	// else if para si el globo es estallado por una flecha
	else {
		// actualiza la posición del globo en base al deltaTime
		this->body.move(this->vel * delta);
		return true;
	}
}

// detector de colisiones
bool Balloon::Hit(const Rectangle& obj)
{
	return false;
}