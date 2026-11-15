#include "Arrow.h"
Arrow::Arrow(Game* g, Rectangle b, Vector2D<float> s) :
	MobileObject(g, b, g->getTexture(Game::TextureName::ARROW), s)
{
};
bool Arrow::update(float delta)
{
	// Movimiento
	MobileObject::update(delta);
	// se saca el rectangulo de la punta de la flecha para comprobar colisiones
	Rectangle tip = Rectangle(Point2D<float>(body.getTopLeftCorner().getX() + (body.getWidth() * 4/5), body.getTopLeftCorner().getY() + (body.getHeight() * 2/3)), body.getWidth()/5, body.getHeight()/3);
	// comprueba si hay colisiones con globos
	game->checkCollision(tip);
	// Si se sale por la izquierda de la pantalla devuelve true para que el game la destruya
	return (body.getTopLeftCorner().getX() < game->WINDOW_WIDTH);
}