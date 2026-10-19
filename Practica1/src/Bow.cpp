#include "Bow.h"
Bow::Bow(const Rectangle& dims, const Texture* text, float velocity, int numarrow, bool arm)
	: body(dims), texture(text), vel(velocity), numArrows(numarrow), strung(arm)
{}
Bow::~Bow()
{
}
void handleEvent(const SDL_Event& event)
{

}
void update()
{

}
void Bow::render()
{
	texture->render(body.to_sdl());
}