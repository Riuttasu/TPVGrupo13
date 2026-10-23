#include "Bow.h"
Bow::Bow(Rectangle dims, Game* g, int arrows) :
	body(dims), game(g), numArrows(arrows)
{}
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
		case SDLK_LEFT: 
			if (numArrows>0) strung = true; 
			break;
		// Disparar el arco
		case SDLK_RIGHT:
			if (strung && numArrows > 0) Shoot();
			break;
		default: break;
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
void Bow::render() const
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
	if (game)
	{
		// Llama al add arrow de game para que aparezca una flecha
		// TopleftCorner - parte width del arco para que salga desde el medio 
		game->AddArrow(body.getTopLeftCorner()+Point2D<float>(0,body.getHeight()/4));
		// Desarma el arco
		strung = false;
		// Quita una flecha del total
		--numArrows;
	}
}