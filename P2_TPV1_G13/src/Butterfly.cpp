#include "Butterfly.h"

// constructor de la mariposa
Butterfly::Butterfly(Game* g, Rectangle b, Vector2D<float> velY, int type)
	: MobileObject(g, b, g->getTexture(Game::TextureName::BUTTERFLY), velY), type(type)
{
	this->type = type % 4; // por si se introduce un tipo fuera de rango
}
Butterfly::Butterfly(Game* g, std::istream& in)
	: MobileObject(g,in, g->getTexture(Game::TextureName::BUTTERFLY))
{
	int c, a, t; bool s;
	if (!(in >> c >> s >> a >> t)) throw "Error al leer parámetros";
	type = c; shot = s; animFrame = a; accumulatedTime = t;
}
// render de la mariposa
void Butterfly::render() const {
	// la animación de vuelo time 10 frames (0-9)
	// hay 4 tipos de mariposa, que vienen determinados por el parámetro type que se le pasa al constructor
	texture->renderFrame(body.to_sdl(), type, animFrame);
}

// update de la mariposa
bool Butterfly::update(float delta) {
	if (!shot) { // actúa normalmente si no ha sido golpeada
		// movimiento
		MobileObject::update(delta);
		// animación de vuelo
		accumulatedTime += delta; // se cuenta el tiempo
		if (accumulatedTime >= animationTime / 10) { // si ha pasado el tiempo de un frame
			accumulatedTime = 0; // se reinicia el contador
			if (animFrame == 0 || animFrame == 9) {
				frameChange = -frameChange; // si se ha llegado al ultimo frame se invierte la dirección de la animación
				animFrame += frameChange; // se avanza en la nueva dirección
			}
			else {
				animFrame += frameChange; // si no se ha llegado al ultimo frame se avanza
			}
		}
		// si la mariposa llega a arriba o abajo, cambia de dirección
		if (body.getTopLeftCorner().getY() < 0 || body.getTopLeftCorner().getY() + body.getHeight() > game->WINDOW_HEIGHT) {
			this->speed = Vector2D<float>(speed.getX(), -speed.getY());
		}
		// de vez en cuando, la mariposa cambia de dirección aleatoriamente
		randomTimer += delta;
		if (randomTimer >= 5000) { // cada 5s
			randomTimer = 0;
			if (game->randomInt(0, 100) < 40) { // 40% de probabilidad cada 5s
				this->speed = Vector2D<float>(speed.getX(), -speed.getY());
			}
		}
	}
	else { // cuando ha sido golpeada, cae hasta salir de la pantalla
		this->speed = Vector2D<float>(0, 0.2f); // se asegura que la mariposa caiga hacia abajo
		MobileObject::update(delta); // movimiento
		// si la mariposa se sale de la pantalla
		if (body.getTopLeftCorner().getY() > game->WINDOW_HEIGHT) {
			return false; // la mariposa ha salido de la pantalla
		}
	}
	return true;
}

bool Butterfly::hit(const Rectangle& obj)
{
	if (!shot && obj.hasIntersection(body)) {
		shot = true;
		return true;
	}
	return false;
}
void Butterfly::Save(std::ostream& out) const
{
	out << "Butterfly ";
	MobileObject::Save(out);
	out << type << " " << shot << " " << animFrame << " " << accumulatedTime << "";
}