#include "Bow.h"
Bow::Bow(Rectangle dims, const Game* g) :
	body(dims), game(g)
{}
Bow::~Bow()
{
}
void Bow::handleEvent(const SDL_Event& event)
{
	// Si se ha presionado una tecla
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		switch (event.key.key)
		{
		// Movimiento
		case SDLK_DOWN: dirY = 1; break;
		case SDLK_UP: dirY = -1; break;
		// Armar el arco
		case SDLK_LEFT: strung = true; break;
		case SDLK_RIGHT: break;
		default: dirY = 0; break;
		}
	}
	// Si se ha soltado una tecla
	else if (event.type == SDL_EVENT_KEY_UP)
	{
		if (event.key.key == SDLK_DOWN && dirY == 1) dirY = 0;
		else if (event.key.key == SDLK_UP && dirY == -1) dirY = 0;
	}
}
void Bow::update(float delta)
{
	// Movimiento segun el input
	body.move(Vector2D<float>(0.0, dirY * delta * vel));
	// Clamp del movimiento a los bordes de la pantalla
	// Clamp superior
	if (body.getTopLeftCorner().getY() < 0)
	body = Rectangle(Point2D<float>(body.getTopLeftCorner().getX(), 0), body.getWidth(), body.getHeight());
	// Clamp inferior
	else if (body.getTopLeftCorner().getY()+body.getHeight() > game->WINDOW_HEIGHT)
	body = Rectangle(Point2D<float>(body.getTopLeftCorner().getX(), game->WINDOW_HEIGHT - body.getHeight()), body.getWidth(), body.getHeight());
}
void Bow::render()
{
	// Consigue la textura del game
	Texture* texture = game->getTexture(Game::TextureName::BOW);
	// Si la encuentra la hace el render dentro de el cuadrado de sus dimensiones
	if (texture)
	{
		// Los parametros extra y el operador 
		texture->renderFrame(body.to_sdl(),0,strung ? 0 : 1);
	}
}
void Bow::Shoot()
{

}