#include "MobileObject.h"
MobileObject::MobileObject(Game* g, Rectangle b, Texture* t, Vector2D<float> s)
	: SceneObject(g,b,t), speed(s)
{}
MobileObject::MobileObject(Game* g, std::istream& in, Texture* t)
	: SceneObject(g, in, t)
{
	float x, y;
	if (!(in >> x >> y)) throw "Error al leer parámetros";
	speed = Vector2D<float>(x, y);
}
bool MobileObject::update(float delta)
{
	body.move(speed * delta);
	// No tiene condicion de destruirse
	return false;
}
void MobileObject::Save(std::ostream& out) const
{
	SceneObject::Save(out);
	out << speed.getX() << " " << speed.getY() << " ";
}