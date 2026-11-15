#include "MobileObject.h"
void MobileObject::update(float delta)
{
	body.move(speed * delta);
}