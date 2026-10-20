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
	: exit(false)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, &window, &renderer))
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
	bow = new Bow(Rectangle(Point2D<float>(WINDOW_WIDTH / 15, WINDOW_HEIGHT / 2), 50, 50), this);
	balloons.push_back(new Balloon(WINDOW_WIDTH / 2, WINDOW_HEIGHT, 1, 10, getTexture(TextureName::BALLOON)));
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

	// generacion de globos a velocidad constante
	static float timeLastBalloon = 0;
	timeLastBalloon += delta;
	if (timeLastBalloon >= 7.0f) {
		timeLastBalloon = 0;
		int posX = uniform_int_distribution<int>(WINDOW_WIDTH / 3, WINDOW_WIDTH - 100)(randomGen); // posicion aleatoria entre 1/3 y el fin (con margen)
		int color = uniform_int_distribution<int>(0, 6)(randomGen); // color aleatorio entre 0 y 6
		float velY = uniform_real_distribution<float>(7.6f, 10.1f)(randomGen); // velocidad aleatoria entre 8 y 10
		balloons.push_back(new Balloon(posX, WINDOW_HEIGHT, color, velY, getTexture(TextureName::BALLOON)));
	}
}

void
Game::run()
{
	while (!exit) {
		handleEvents();
		// TODO: implementar bucle del juego
		update(0.01f);
		render();
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
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
// bool
// Game::checkCollision(const Rectangle& rect)
// {
//	// TODO
//	return false;
// }
