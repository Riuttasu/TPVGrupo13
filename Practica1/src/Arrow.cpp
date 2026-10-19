#include "Arrow.h"
Arrow::Arrow(Game* game, Rectangle dims, Vector2D<float> velocity) :
	collisions(game), body(dims), vel(velocity)
{
};
Arrow::~Arrow() 
{
}
void Arrow::update()
{
	body.move(vel);
}
void Arrow::render()
{
}