#include "InfoBar.h"

InfoBar::InfoBar(const Game* g) : game(g)
{ 
	arrows = Rectangle(Point2D<float>(game->WINDOW_WIDTH / 15,game->WINDOW_HEIGHT/30), 
		game->ARROW_WIDTH, game->ARROW_HEIGHT/2);
}
void InfoBar::render()
{
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
}