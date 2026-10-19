#include "Balloon.h"


// constructor del globo
Balloon::Balloon(float posX, float posY, int color, float velY){
	this->body = Rectangle(Point2D<float>(posX, posY), 40, 60);
	this->color = color;
	this->vel = Vector2D<float>(0, -velY); // negativo ya que el globo sube
}

bool Balloon::Hit(const Rectangle& obj)
{
	return true;
}