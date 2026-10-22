#include "Arrow.h"
Arrow::Arrow(Rectangle dims, const Game* g, Vector2D<float> velocity = Vector2D(0.3f, 0.0f)) :
	game(g), body(dims), vel(velocity)
{
};
bool Arrow::update(float delta)
{
	body.move(vel*delta);
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