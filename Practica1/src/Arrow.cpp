#include "Arrow.h"
Arrow::Arrow(Game* game, Rectangle dims, Vector2D<float> velocity, Texture* text) :
	collisions(game), body(dims), vel(velocity), texture(text)
{
};
Arrow::~Arrow() 
{
	delete texture;
}
void Arrow::update()
{
	body.move(vel);
}
void Arrow::render()
{
	texture->render(body.to_sdl());
}