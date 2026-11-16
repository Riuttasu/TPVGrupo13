#include "Arrow.h"
Arrow::Arrow(Game* g, Rectangle b, Vector2D<float> s) :
	MobileObject(g, b, g->getTexture(Game::TextureName::ARROW), s)
{}
Arrow::Arrow(Game* g, std::istream& in)
	: MobileObject(g,in,g->getTexture(Game::TextureName::ARROW))
{
	int c;
	if (!(in >> c)) throw "Error al leer parámetros";
	combo = c;
}
bool Arrow::update(float delta)
{
	// Movimiento
	MobileObject::update(delta);
	// se saca el rectangulo de la punta de la flecha para comprobar colisiones
	Rectangle tip = Rectangle(Point2D<float>(body.getTopLeftCorner().getX() + (body.getWidth() * 4/5), body.getTopLeftCorner().getY() + (body.getHeight() * 2/3)), body.getWidth()/5, body.getHeight()/3);
	// comprueba si hay colisiones
	SceneObject* hit = game->checkCollision(tip);
	if (hit != nullptr) hitLogic(hit);
	// Si se sale por la izquierda de la pantalla devuelve true para que el game la destruya
	return (body.getTopLeftCorner().getX() < game->WINDOW_WIDTH);
}
void Arrow::hitLogic(SceneObject* hit)
{
	// Si es un globo
	if (dynamic_cast<Balloon*>(hit)) {
		game->addPoints(game->getBalPoints() * combo);
		combo++;
	}
	// Si es una mariposa
	else if (dynamic_cast<Butterfly*>(hit)) {
		game->addPoints(-5);
	}
}
void Arrow::Save(std::ostream& out) const
{
	out << "Arrow ";
	MobileObject::Save(out); 
	out << combo << " ";
}