#pragma once
// Includes
#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>
using namespace std;
// Error generico juego, hereda de logic_error
class GameError : public logic_error
{
public:
	GameError(string what) : logic_error(what) {}
};
// Error de la SDL
class SDLError : public GameError
{
public:
	SDLError(string what) : GameError(what + ":" + SDL_GetError()) {}
};
// Archivo no encontrado
class FileNotFoundError : public GameError
{
public:
	FileNotFoundError(string fileName) : GameError(fileName + " no encontrado") {}
};
// Mal formato de archivo, requiere de linea
class FileFormatError : public GameError
{
public:
	FileFormatError(string what, int line, string filename) : GameError(what + ": linea " + to_string(line) + ", archivo " + filename) {}
};