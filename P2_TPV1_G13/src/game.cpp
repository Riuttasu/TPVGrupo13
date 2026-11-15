#include "game.h"
using namespace std;
// Includes
#include <string>
#include <SDL3_image/SDL_image.h> // SDL
// Objetos
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "InfoBar.h"
#include "rectangle.h"
#include "texture.h"
// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	{"arrow.png"},
	TextureSpec{"balloons.png", 7, 6},
};

// generador de números aleatorios

Game::Game()
	: exit(false), goal(false), points(0), randomGen(random_device{}())
{
	// Lee archivo para inicializar valores de archivo si existe el nivel 1
	loadLevel(1);
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, &window, &renderer)
		|| !SDL_SetRenderDrawColor(renderer,bgColor.r,bgColor.g,bgColor.b,1))
		throw "window or renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (...) {
		// liberar la memoria reservada
		window = nullptr;
		renderer = nullptr;
		for (auto& texture : textures) {
			delete texture;
		}
		throw; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// creacion de los objetos del juego
	bow = new Bow(this, Rectangle(Point2D<float>(WINDOW_WIDTH / 15, WINDOW_HEIGHT / 2), BOW_WIDTH, BOW_HEIGHT), maxArrows);
	infobar = new InfoBar(this);
}

Game::~Game()
{
	//  liberar la memoria reservada por la clase
	delete window; window = nullptr;
	delete renderer; renderer = nullptr;
	for (auto& texture : textures) {
		delete texture;
	}
	delete bow; bow = nullptr;
	for (GameObject* g : objects) { delete g; g = nullptr; }
}

void
Game::render() const
{
	SDL_RenderClear(renderer);
	// Delegacion de render a objetos
	bow->render();
	infobar->render();
	for (SceneObject* o : objects) o->render();
	//
	SDL_RenderPresent(renderer);
}

void
Game::update(float delta)
{
	// Delegacion de update a objetos
	bow->update(delta);
	// Iterador para ir borrando los objetos si devuelven false
	for (auto it = objects.begin(); it != objects.end();) {
		if (!(*it)->update(delta)) {
			delete* it; // Destrucción del objeto
			it = objects.erase(it); // Se le quita de la lista
		}
		else ++it; // Si no se tiene que borrar se avanza
	}
	// generacion de globos
	addBalloonLogic(delta);
}
void
Game::addBalloonLogic(float delta)
{
	static float timeLastBalloon = 0; // Static hace que mantenga el valor entre las llamadas
	timeLastBalloon += delta;
	if (timeLastBalloon >= balloonDelay) {
		timeLastBalloon = 0; // Reinicia el timer
		// Variables random del globo a spawnear
		int posX = uniform_int_distribution<int>(WINDOW_WIDTH / 3, WINDOW_WIDTH - 100)(randomGen); // posicion aleatoria entre 1/3 y el fin (con margen)
		int color = uniform_int_distribution<int>(0, 6)(randomGen); // color aleatorio entre 0 y 6
		Vector2D<float> velY(0, balloonSpeed); // Velocidad no aleatoria pero dada por archivo
		//Vector2D<float> velY(0,-uniform_real_distribution<float>(0.076f, 0.101f)(randomGen)); // velocidad aleatoria
		// Mete el globo en el juego
		AddObject(new Balloon(this,Rectangle(Point2D<float>(posX,WINDOW_HEIGHT),BALLOON_WIDTH,BALLOON_HEIGHT),velY,color));
	}
}
void
Game::run()
{
	int level = 1;
	// bucle principal
	while (!exit && !goal) {
		startTime = SDL_GetTicks();
		// Manejo de eventos
		handleEvents();
		// Update con el tiempo por frame que se busca
		update(FRAME_PERIOD);
		// Render
		render();
		// Se calcula el tiempo del frame desde el start y si se ha llegado al frame period que queriamos
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_PERIOD){
			// Si no hace delay por lo que quede para el frame period
			SDL_Delay(FRAME_PERIOD - frameTime);
		}
	}
}

void
Game::handleEvents()
{
	SDL_Event event;
	// quit lo maneja el juego
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
		{
			exit = true;
			break;
		}
		// Delegacion de eventos a objetos
		bow->handleEvent(event);
	}
}
void
Game::AddObject(SceneObject* obj)
{
	objects.push_back(obj);
}
int
Game::getArrows() const
{
	if (bow) return bow->GetArrowNum();
	else return -1;
}
void
Game::addPoints(int delta)
{
	points += delta;
}
SceneObject*
Game::checkCollision(const Rectangle& rect)
{
	// comprueba si hay algún objeto que colisione con el rectangulo dado
	for (SceneObject* o : objects){
		if (o->hit(rect)) {
			return o; // Devuelve un puntero al objeto
		}
	}
	return nullptr; // si no hay colisiones
}
void
Game::loadLevel(int levelNum)
{
	// Busca un archivo con ese nombre en LEVEL_ROOT, si no hay tira exception
	ifstream level(LEVEL_ROOT + to_string(levelNum) + ".txt");
	if (!level) throw runtime_error(std::format("No existe archivo con el nombre {}.txt para cargar nivel en {}",levelNum, LEVEL_ROOT));
	// Abre la lectura de archivo
	istream& in(level);
	// Variables que se van a leer inicializadas a -1 para pillar si no se han modificado
	int arrows = -1, baldelay = -1, r = -1, g = -1, b = -1, balpoints = -1;
	//Lectura de archivo
	string line = "";
	// Lee palabro por palabro hasta quedarse sin archivo
	while (in >> line)
	{
		// Si es un comentario nos dejamos de movidas
		// primer argumento lo he encontrao en cplusplus, dudo que algun animal escriba un comentario de mas de mil caracteres tho
		if (line[0] == '#') { in.ignore(numeric_limits<streamsize>::max(), '\n'); }
		// palabras clave
		else if (line == "arrows") in >> arrows; // flechas
		else if (line == "baldelay") in >> baldelay; // tiempo entre globos
		else if (line == "bgcolor") in >> r >> g >> b; // RGB fondo
		else if (line == "balpoints") in >> balloonPoints; // puntos por globo
		else if (line == "balspeed") in >> balloonSpeed; // velocidad de globos
		else if (line == "butterflies") in >> butterflies; // numero de mariposas
		// Si no es ninguna de ellas, ignora
		else in.ignore(numeric_limits<streamsize>::max(), '\n');
		// si lee una palabra clave que se reconoce y no parsea bien se devuelve exception
		// aqui queria poner un format con linea pero luego recorde que esto no es c# y al buscar me parecia algo mas complicado lo pondre en el txt
		if (in.fail()) throw runtime_error("Lectura de archivo fallada, no se ha podido convertir propiedad por mala conversion");
	}
}
