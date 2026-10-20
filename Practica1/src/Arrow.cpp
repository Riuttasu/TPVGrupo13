#include "Arrow.h"
Arrow::Arrow(Rectangle dims, const Game* g) :
	game(g), body(dims)
{
};
Arrow::~Arrow() 
{

}
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