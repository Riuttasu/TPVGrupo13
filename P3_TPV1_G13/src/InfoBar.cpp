#include "InfoBar.h"

InfoBar::InfoBar(Game* g,TTF_TextEngine* e, TTF_Font* f) : GameObject(g), engine(e), font (f)
{ 
	arrows = Rectangle(Point2D<float>(game->WINDOW_WIDTH / 15,game->WINDOW_HEIGHT/30), 
		game->ARROW_WIDTH, game->ARROW_HEIGHT/2);
	text = TTF_CreateText(engine, font, "0", 0);
}
InfoBar::~InfoBar()
{
	TTF_DestroyText(text);
}
void InfoBar::render() const 
{
	// Flechas
	Texture* arrowTexture = game->getTexture(Game::TextureName::ARROW);
	if (arrowTexture)
	{
		for (int i = 0;i < game->getArrows();++i)
		{
			// Creacion del rectangulo donde estara la flecha
			Point2D<float> arrowTopLeft = arrows.getTopLeftCorner() + Point2D<float>(i*arrows.getWidth(),0);
			Rectangle arrowRect = Rectangle(arrowTopLeft,arrows.getWidth(),arrows.getHeight());
			// Render
			arrowTexture->renderFrame(arrowRect.to_sdl(), 0, 0,90.0);
		}
	}
	// Texto
	TTF_DrawRendererText(text, game->WINDOW_WIDTH - 40, 0);
}
bool InfoBar::update(float delta) { 
	TTF_SetTextString(text, std::to_string(game->getPoints()).c_str(), 0);
	return false; 
}