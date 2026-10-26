#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <fstream>
#include <vector>
#include <format>
// Objetos
#include "Bow.h"
#include "Arrow.h"
#include "Balloon.h"
#include "InfoBar.h"
// #include "rectangle.h"

// Declaraciones anticipadas
class Texture;
class Bow;
class Arrow;
class Balloon;
class InfoBar;
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
	// Tamaño de objetos
	static constexpr int ARROW_WIDTH = 45;
	static constexpr int ARROW_HEIGHT = 22;
	static constexpr int BOW_WIDTH = 50;
	static constexpr int BOW_HEIGHT = 50;
	//
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
	// bools que rompen bucle principal
	bool exit; // Salida mediante cerrar ventana
	bool goal; // Salida mediante terminar objetivo/flechas
	// Manejo de tiempo
	uint64_t startTime, frameTime = 0;
	// Puntos
	int points = 0;
	// Elementos del juego
	Bow* bow = nullptr; // Arco
	std::vector<Arrow*> arrows; // Flechas
	std::vector<Balloon*> balloons; // Globos
	InfoBar* infobar = nullptr; // Barra de informacion para el jugador
	// Variables cambiadas por archivo
	SDL_Color bgColor = SDL_Color(0, 0, 0, 1); // Color del fondo de la ventana
	int maxArrows = 5; // Numero maximo de flechas
	int balloonDelay = 1000; // Tiempo entre globos
	int balloonPoints = 10; // Numero de puntos por globo
public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	// Obtiene el numero de flechas
	int getArrows() const;
	// Ejecuta el bucle principal del juego
	void run();
	// anade una flecha a la escena en la posicion dada como esquina superior izquierda
	void AddArrow(Point2D<float> topleftcorn);
	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect) ;
	// Carga desde archivo
	void loadLevel(int levelNum);
};


inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
#endif // GAME_H
