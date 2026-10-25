#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "vector2D.h"

#include <random> // para generar valores aleatorios

using namespace std;

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
random_device semilla; // número aleatorio del hardware
mt19937_64 randomGen(semilla()); // generador de números aleatorios

Game::Game()
	: exit(false), goal(false)
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
	bow = new Bow(Rectangle(Point2D<float>(WINDOW_WIDTH / 15, WINDOW_HEIGHT / 2), 50, 50), this, maxArrows);
}

Game::~Game()
{
	//  liberar la memoria reservada por la clase
	window = nullptr;
	renderer = nullptr;
	for (auto& texture : textures) {
		delete texture;
	}
	delete bow;
	for (Arrow* a : arrows) delete a;
	for (Balloon* b : balloons) delete b;
}

void
Game::render() const
{
	SDL_RenderClear(renderer);
	// Delegacion de render a objetos
	bow->render();
	for (Arrow* a : arrows) a->render();
	for (Balloon* b : balloons) b->render();
	//
	SDL_RenderPresent(renderer);
}

void
Game::update(float delta)
{
	// Delegacion de update a objetos
	bow->update(delta);

	for (int i = 0; i < arrows.size(); i++) {
		if (!arrows[i]->update(delta)) {
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
		}
	}

	for (int i = 0; i < balloons.size(); i++) {
		if (!balloons[i]->update(delta)) {
			delete balloons[i];
			balloons.erase(balloons.begin() + i);
		}
	}

	// cuando todo esta en su sitio se comprueba si hay colisiones entre flechas y globos

	// generacion de globos a velocidad constante
	static float timeLastBalloon = 0;
	timeLastBalloon += delta;
	if (timeLastBalloon >= balloonDelay) {
		timeLastBalloon = 0;
		int posX = uniform_int_distribution<int>(WINDOW_WIDTH / 3, WINDOW_WIDTH - 100)(randomGen); // posicion aleatoria entre 1/3 y el fin (con margen)
		int color = uniform_int_distribution<int>(0, 6)(randomGen); // color aleatorio entre 0 y 6
		float velY = uniform_real_distribution<float>(0.076f, 0.101f)(randomGen); // velocidad aleatoria entre 8 y 10
		balloons.push_back(new Balloon(posX, WINDOW_HEIGHT, color, velY, getTexture(TextureName::BALLOON)));
	}
}

void
Game::run()
{
	// bucle principal
	while (!exit && !goal) {
		// Start del frame
		startTime = SDL_GetTicks();
		// Manejo de eventos
		handleEvents();
		// Update con el tiempo por frame que se busca
		update(FRAME_PERIOD);
		// Render
		render();
		// Se calcula el tiempo del frame desde el start y si se ha llegado al frame period que queriamos
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_PERIOD)
			// Si no hace delay por lo que quede para el frame period
			SDL_Delay(FRAME_PERIOD - frameTime);
		// Condicion de game over
		// 0 flechas, empty de arrows es para dejar que la ultima flecha haga su trayectoria
		if (bow->GetArrowNum() <= 0 && arrows.empty()) goal = true;
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
Game::AddArrow(Point2D<float> topleftcorn)
{
	arrows.push_back(new Arrow(Rectangle(topleftcorn, 45, 22), this));
}
bool
Game::checkCollision(const Rectangle& rect)
{
	// comprueba si hay algún globo que colisione con el rectángulo dado
	for (const auto& balloon : balloons) {
		if (balloon->Hit(rect)) {
			return true;
		}
	}
	return false; // si no hay colisiones
}
void
Game::loadLevel(int levelNum)
{
	// Busca un archivo con ese nombre en LEVEL_ROOT, si no hay tira exception
	fstream level(LEVEL_ROOT + to_string(levelNum) + ".txt");
	if (!level) throw runtime_error(std::format("No existe archivo con el nombre {}.txt para cargar nivel en {}",levelNum, LEVEL_ROOT));
	// Abre la lectura de archivo
	istream& in(level);
	// Variables que se van a leer inicializadas a -1 para pillar si no se han modificado
	int arrows = -1;
	int baldelay = -1;
	int r = -1, g = -1, b = -1;
	//Lectura de archivo
	string line = "";
	int lineNum = 0;
	// Lee palabro por palabro hasta quedarse sin archivo
	while (in >> line)
	{
		// Si es un comentario nos dejamos de movidas
		// primer argumento lo he encontrao en cplusplus, dudo que algun animal escriba un comentario de mas de mil caracteres tho
		if (line[0] == '#') { in.ignore(numeric_limits<streamsize>::max(), '\n'); }
		// palabras clave
		else if (line == "arrows") {
			in >> arrows;
		}
		else if (line == "baldelay") {
			in >> baldelay;
		}
		else if (line == "bgcolor") {
			in >> r >> g >> b;
		}
		// Si no es ninguna de ellas, ignora
		else in.ignore(numeric_limits<streamsize>::max(), '\n');
		// si lee una palabra clave que se reconoce y no parsea bien se devuelve exception
		// aqui queria poner un format con linea pero luego recorde que esto no es c# y al buscar me parecia algo mas complicado lo pondre en el txt
		if (in.fail()) throw runtime_error("Lectura de archivo fallada, no se ha podido convertir propiedad por mala conversion");
	}
	// Pone las variables configurables que se han modificado, checkea si son valores validos despues ( si es -1 ajo y agua ) 
	if (arrows != -1) {
		if (arrows < -1) throw runtime_error(format("Lectura de archivo fallada, propiedad con valor fuera de rango, {}, propiedad numero flechas", arrows));
		maxArrows = arrows;
	}
	if (baldelay != -1) {
		if (baldelay < -1) throw runtime_error(format("Lectura de archivo fallada, propiedad con valor fuera de rango, {}, propiedad delay globos", baldelay));
		balloonDelay = baldelay;
	}
	if (r != -1 || g != -1 || b != -1) {
		if (r < -1 || r > 255 || g < -1 || g > 255 || b < -1 || b > 255) 
			throw runtime_error(format("Lectura de archivo fallada, propiedad con valor fuera de rango, ({},{},{}), propiedad color fondo", r, g,b));
		bgColor = SDL_Color(r,g,b,1);
	}
}
