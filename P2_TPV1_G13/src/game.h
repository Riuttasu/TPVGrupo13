#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <array>
#include <fstream>
#include <list>
#include <format>
#include <random> // para generar valores aleatorios
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
// Objetos

// Declaraciones anticipadas
class GameObject;
class SceneObject;
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
	static constexpr int ARROW_WIDTH = 45, ARROW_HEIGHT = 22;
	static constexpr int BOW_WIDTH = 50, BOW_HEIGHT = 50;
	static constexpr int BALLOON_WIDTH = 60, BALLOON_HEIGHT = 90;
	static constexpr int BUTTERFLY_WIDTH = 32, BUTTERFLY_HEIGHT = 32;
	// ints aleatorios
	int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(randomGen); }
	//
	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOON,
		BUTTERFLY,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;
	TTF_Font* font;
	TTF_TextEngine* engine;
	// Bucle principal
	void render() const;
	void update(float delta);
	void handleEvents();
	int level;
	// spawn de globos
	void addBalloonLogic(float delta);
	// bools que rompen bucle principal
	bool exit; // Salida mediante cerrar ventana
	// Manejo de tiempo
	uint64_t startTime, frameTime = 0;
	// Generador de aleatorios
	std::mt19937_64 randomGen; 
	// Puntos
	int points = 0;
	// Elementos del juego
	Bow* bow = nullptr; // Arco
	GameObject* infobar = nullptr;
	std::list<SceneObject*> objects; // Lista polimorfica de objetos
	// Variables cambiadas por archivo
	SDL_Color bgColor = SDL_Color(0, 0, 0, 1); // Color del fondo de la ventana
	int maxArrows = 5; // Numero maximo de flechas
	int balloonDelay = 1000; // Tiempo entre globos
	int balloonPoints = 10; // Numero de puntos por globo
	float balloonSpeed = 0.03f; // Velocidad globos
	int butterflies = 0; // Numero mariposas 
	int goal = 0; // Puntos a los que llegar
public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	// Obtiene el numero de flechas
	int getArrows() const;
	// Añade puntos
	void addPoints(int delta);
	int getBalPoints() const { return balloonPoints; }
	int getPoints() const { return points; }
	// Ejecuta el bucle principal del juego
	void run();
	// anade una flecha a la escena en la posicion dada como esquina superior izquierda
	void AddObject(SceneObject* obj);
	void spawnButterflies(); // Spawnea el número de mariposas dadas por el nivel 
	// Comprueba si hay algún objeto colocado en ese rectángulo
	SceneObject* checkCollision(const Rectangle& rect) ;
	// Niveles
	bool nextLevel(); // Comprueba si hay siguiente nivel, si hay, lo carga
	void loadLevel(int levelNum); // Cargar nivel de archivo
	// Guardar y cargar partida
	void saveGame() const; // Guardar partida
	void loadGame(); // Cargar partida

};


inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
#endif // GAME_H
