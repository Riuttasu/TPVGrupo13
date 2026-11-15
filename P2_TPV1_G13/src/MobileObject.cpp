#include "MobileObject.h"
MobileObject::MobileObject(Game* g, Rectangle b, Texture* t, Vector2D<float> s)
	: SceneObject(g,b,t), speed(s)
{}
bool MobileObject::update(float delta)
{
	body.move(speed * delta);
	// No tiene condicion de destruirse
	return false;
}