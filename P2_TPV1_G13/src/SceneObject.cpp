#include "SceneObject.h"
SceneObject::SceneObject(Game* g, Rectangle b, Texture* t)
	: GameObject(g), body(b), texture(t)
{}
bool SceneObject::hit(const Rectangle& c)
{
	return (c.hasIntersection(body));
}
void SceneObject::render() const 
{
	if (texture)
	{
		texture->render(body.to_sdl());
	}
}