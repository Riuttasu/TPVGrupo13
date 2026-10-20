#include "Arrow.h"
Arrow::Arrow(Rectangle dims, const Game* g) :
	game(g), body(dims)
{
};
Arrow::~Arrow() 
{

}
void Arrow::update(float delta)
{
	body.move(vel*delta);
}
void Arrow::render() const
{
	Texture* texture = game->getTexture(Game::TextureName::ARROW);
	if (texture)
	{
		texture->render(body.to_sdl());
	}
}