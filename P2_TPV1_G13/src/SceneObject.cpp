#include "SceneObject.h"
#include "GameErrors.h"
SceneObject::SceneObject(Game* g, Rectangle b, Texture* t)
	: GameObject(g), body(b), texture(t)
{}
SceneObject::SceneObject(Game* g, std::istream& in, Texture* t)
	: GameObject(g), texture(t)
{
	float x, y; int h, w;
	if (!(in >> x >> y >> h >> w)) throw "Error al leer parámetros sceneobject";
	body = Rectangle(Point2D<float>(x, y), h, w);
}
bool SceneObject::hit(const Rectangle& c)
{
	return false;
}
void SceneObject::render() const 
{
	if (texture)
	{
		texture->render(body.to_sdl());
	}
}
void SceneObject::Save(std::ostream& out) const
{
	out << body.getTopLeftCorner().getX() << " " << body.getTopLeftCorner().getY() << " " << body.getWidth() << " " << body.getHeight() << " ";
}