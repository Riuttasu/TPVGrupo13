#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
// Objetos
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
// #include "rectangle.h"

// Declaraciones anticipadas
class Texture;
class Bow;
class Arrow;
class Balloon;
/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Número de actualizaciones por segundo
	static constexpr int FRAME_RATE = 30;
	// Periodo entre actualizaciones en milisegundos
	static constexpr int FRAME_PERIOD = 1000 / FRAME_RATE;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;

	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOON,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update(float delta);
	void handleEvents();

	bool exit;
	// Manejo de tiempo
	uint64_t startTime, frameTime = 0;

	// Elementos del juego
	Bow* bow; // Arco
	std::vector<Arrow*> arrows; // Flechas
	std::vector<Balloon*> balloons; // Globos
public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();
	// anade una flecha a la escena en la posicion dada como esquina superior izquierda
	void AddArrow(Point2D<float> topleftcorn);
	// Comprueba si hay algún objeto colocado en ese rectángulo
	// bool checkCollision(const Rectangle& rect);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
