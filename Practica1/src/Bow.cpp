#include "Bow.h"
Bow::Bow(Rectangle dims, const Game* g) :
	body(dims), game(g)
{}
Bow::~Bow()
{
}
void Bow::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		switch (event.key.key)
		{
		case SDLK_DOWN: dirY = 1; break;
		case SDLK_UP: dirY = -1; break;
		case SDLK_LEFT: strung = true; break;
		case SDLK_RIGHT: break;
		default: dirY = 0; break;
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP)
	{
		dirY = 0;
	}
}
void Bow::update(float delta)
{
	body.move(Vector2D<float>(0.0, dirY * delta * vel));
}
void Bow::render()
{
	Texture* texture = game->getTexture(Game::TextureName::BOW);
	if (texture)
	{
		texture->render(body.to_sdl());
	}
}