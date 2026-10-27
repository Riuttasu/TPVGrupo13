#include "Arrow.h"
Arrow::Arrow(Rectangle dims, Game* g, Vector2D<float> velocity) :
	game(g), body(dims), vel(velocity)
{
};
bool Arrow::update(float delta)
{
	body.move(vel*delta);
	// se saca el rectangulo de la punta de la flecha para comprobar colisiones
	Rectangle tip = Rectangle(Point2D<float>(body.getTopLeftCorner().getX() + (body.getWidth() * 4/5), body.getTopLeftCorner().getY() + (body.getHeight() * 2/3)), body.getWidth()/5, body.getHeight()/3);
	// comprueba si hay colisiones con globos
	game->checkCollision(tip);
	// Si se sale por la izquierda de la pantalla devuelve true para que el game la destruya
	return (body.getTopLeftCorner().getX() < game->WINDOW_WIDTH);
}
void Arrow::render() const
{
	Texture* texture = game->getTexture(Game::TextureName::ARROW);
	if (texture)
	{
		texture->render(body.to_sdl());
	}
}