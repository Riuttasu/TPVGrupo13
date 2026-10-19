#include "Bow.h"
Bow::Bow(Rectangle dims, const Game* g) :
	body(dims), game(g)
{}
Bow::~Bow()
{
}
void Bow::handleEvent(const SDL_Event& event)
{
	switch (event.key.key)
	{
		case SDLK_DOWN: dirY = 1; break;
		case SDLK_UP: dirY = -1; break;
		default: dirY = 0; break;
	}
}
void Bow::update(float delta)
{
	body.move(Vector2D(0.0f, dirY * delta * vel));
}
void Bow::render()
{
	Texture* texture = game->getTexture(Game::TextureName::BOW);
	if (texture)
	{
		texture->render();
	}
}