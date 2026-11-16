#include "game.h"
using namespace std;
// Includes
#include <string>
#include <sstream>
#include <algorithm>
#include "GameErrors.h"
#include <SDL3_image/SDL_image.h> // SDL
#include <SDL3_ttf/SDL_textengine.h>
// Objetos
#include "Butterfly.h"
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
constexpr const char* SAVE_ROOT = "../assets/";

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
	TextureSpec{"butterfly.png", 4, 10}
};

// generador de números aleatorios

Game::Game()
	: exit(false), points(0), level(1), randomGen(random_device{}())
{
	// Lee archivo para inicializar valores de archivo si existe el nivel 1
	loadLevel(level);
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw SDLError("SDL_Init: ");

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, &window, &renderer)
		|| !SDL_SetRenderDrawColor(renderer,bgColor.r,bgColor.g,bgColor.b,1))
		throw SDLError("Window or renderer: ");
	// Texto y motor de texto
	if (!TTF_Init()) throw SDLError("Text: ");
	font = TTF_OpenFont("../assets/font/font.ttf", 24);
	if (!font) throw FileNotFoundError("../assets/font/font.ttf");
	engine = TTF_CreateRendererTextEngine(renderer);
	if (!engine) throw SDLError("Engine: ");
	
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
		TTF_CloseFont(font);
		TTF_DestroyRendererTextEngine(engine);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		for (auto& texture : textures) {
			delete texture;
		}
		throw; // relanza la excepción
	}
	// creacion de los objetos del juego
	bow = new Bow(this, Rectangle(Point2D<float>(WINDOW_WIDTH / 15, WINDOW_HEIGHT / 2), BOW_WIDTH, BOW_HEIGHT), maxArrows);
	AddObject(bow); // Lo añade a la lista de objetos
	spawnButterflies();
	infobar = new InfoBar(this,engine,font); // Infobar es un gameobject va externo a la lista
}

Game::~Game()
{
	//  liberar la memoria reservada por la clase
	TTF_CloseFont(font);
	TTF_DestroyRendererTextEngine(engine);
	for (auto& texture : textures) {
		delete texture;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete infobar;
	for (SceneObject* g : objects) { delete g; g = nullptr; }
}

void
Game::render() const
{
	SDL_RenderClear(renderer);
	// Delegacion de render a objetos
	infobar->render();
	for (SceneObject* o : objects) o->render();
	//
	SDL_RenderPresent(renderer);
}

void
Game::update(float delta)
{
	// Comprueba el objetivo
	if (points >= goal) nextLevel();
	// Delegacion de update a objetos
	infobar->update(delta);
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
		Vector2D<float> velY(0, -uniform_real_distribution<float>(balloonSpeed-0.1, balloonSpeed+0.1)(randomGen)); 
		// Mete el globo en el juego
		AddObject(new Balloon(this,Rectangle(Point2D<float>(posX,WINDOW_HEIGHT),BALLOON_WIDTH,BALLOON_HEIGHT), velY,color));
	}
}
void
Game::run()
{
	// bucle principal
	while (!exit) {
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
	SDL_Event event; // evento
	while (SDL_PollEvent(&event)) {
		// quit lo maneja el juego
		if (event.type == SDL_EVENT_QUIT)
		{
			exit = true;
			break;
		}
		// Guardado y cargado de partida
		if (event.type == SDL_EVENT_KEY_DOWN && (event.key.mod & SDL_KMOD_CTRL)) {
			if (event.key.key == SDLK_S) saveGame();
			else if (event.key.key == SDLK_O) loadGame();
		}
		// Delegacion de eventos a objetos
		if(bow) bow->handleEvent(event);
	}
}
void
Game::AddObject(SceneObject* obj)
{
	objects.push_back(obj);
}
void
Game::spawnButterflies()
{
	for (int i = 0;i < butterflies;++i)
	{ 
		// Randoms
		Point2D<float> pos(uniform_real_distribution<float>(WINDOW_WIDTH/5, WINDOW_WIDTH-BUTTERFLY_WIDTH)(randomGen), uniform_real_distribution<float>(BUTTERFLY_HEIGHT, WINDOW_HEIGHT-BUTTERFLY_HEIGHT)(randomGen));
		Vector2D<float> vel(uniform_real_distribution<float>(-0.03,0.03)(randomGen),uniform_real_distribution<float>(-0.03, 0.03)(randomGen));
		int type = uniform_int_distribution<int>(0, 4)(randomGen);
		// Añade la mariposa
		AddObject(new Butterfly(this, Rectangle(pos, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT), vel, 3));
	}
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
bool
Game::nextLevel()
{
	if (!ifstream(string(LEVEL_ROOT) + to_string(level + 1) + ".txt"s)) return false; // No existe el siguiente nivel
	// Limpieza de objetos antiguos
	for (SceneObject* o : objects) delete o;
	objects.clear();
	// Carga el nivel
	++level;
	loadLevel(level);
	// Cambia variables a valor inicial
	points = 0;
	if(!SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 1))
	throw SDLError("Renderer");
	// Añade nuevos objetos
	spawnButterflies();
	bow = new Bow(this, Rectangle(Point2D<float>(WINDOW_WIDTH / 15, WINDOW_HEIGHT / 2), BOW_WIDTH, BOW_HEIGHT), maxArrows);
	AddObject(bow); // Lo añade a la lista de objetos
	return true;
}
void
Game::loadLevel(int levelNum)
{
	// Busca un archivo con ese nombre en LEVEL_ROOT, si no hay tira exception
	string filename = LEVEL_ROOT + to_string(levelNum) + ".txt";
	ifstream level(filename);
	if (!level) throw FileNotFoundError(filename);
	// Abre la lectura de archivo
	istream& in(level);
	//Lectura de archivo
	string line = "";
	int linenum = 1;
	// Lee linea por linea hasta quedarse sin archivo
	while (getline(level,line))
	{
		// Si es un comentario nos dejamos de movidas, continue para no sumar la linea dos veces
		if (line.empty() || line[0] == '#') { linenum++; continue; }
		// palabras clave
		istringstream streamline(line);
		string word;
		streamline >> word;
		if (word == "arrows") {
			streamline >> maxArrows;
			if (maxArrows < 0) throw FileFormatError("Numero de flechas fuera de rango", linenum,filename);
		}
		else if (word == "baldelay") {
			streamline >> balloonDelay;
			if (balloonDelay < 0) throw FileFormatError("Delay de globos fuera de rango", linenum,filename);
		}
		else if (word == "bgcolor") {
			int r = -1, g = -1, b = -1;
			streamline >> r >> g >> b;
			if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255) throw FileFormatError("Color de fondo fuera de rango", linenum,filename);
			else bgColor = SDL_Color(r, g, b, 1);
		}
		else if (word == "balpoints") {
			streamline >> balloonPoints;
			if (balloonPoints < 0) throw FileFormatError("Numero de flechas fuera de rango", linenum,filename);
		}
		else if (word == "balspeed") {
			streamline >> balloonSpeed;
			if (balloonSpeed < 0) throw FileFormatError("Velocidad de globos fuera de rango", linenum,filename);
		}
		else if (word == "butterflies") {
			streamline >> butterflies;
			if (butterflies < 0) throw FileFormatError("Numero de mariposas fuera de rango", linenum,filename);
		}
		else if (word == "goal") {
			streamline >> goal;
			if (goal < 0) throw FileFormatError("Goal fuera de rango", linenum, filename);
		}
		// Si se ha parseado algo mal
		if (in.fail()) throw FileFormatError("Mal formato de archivo, conversion fallida", linenum,filename);
		linenum++;
	}
	cout << "Nivel " << levelNum << " cargado, objetivo: " << goal << endl;
}
void
Game::saveGame() const
{
	// ostream crea el archivo si no existe, o lo limpia si si
	ofstream savefile(string(SAVE_ROOT) + "saved.txt");
	if (!savefile.is_open()) throw FileNotFoundError("saved.txt");
	// Encabezado con datos globales
	savefile << level << " " << points << " " << bow->GetArrowNum() << " " << endl;
	savefile << randomGen << endl;
	// Lista sceneobjects
	for (SceneObject* o : objects) {
		o->Save(savefile); savefile << endl;
	}
}
void 
Game::loadGame()
{
	// Abre el archivo
	ifstream savefile(string(SAVE_ROOT) + "saved.txt");
	if (!savefile) throw FileNotFoundError("saved.txt");
	// Variables lectura
	int linenum = 1; string line = "";
	// Variables temporales
	int arrowLoad; Bow* bowLoad = nullptr;
	list<SceneObject*> objLoad; 
	try {
		// Dos primeras lineas siembre debe haber
		if (!(savefile >> level >> points >> arrowLoad)) throw "Error al leer encabezado con parámetros";
		++linenum;
		if (!(savefile >> randomGen)) throw "Error al leer semilla";
		++linenum;
		// Lista de objetos
		getline(savefile, line); // Para quitar \n
		while (getline(savefile, line))
		{
			// palabra clave dice que objeto es
			istringstream streamline(line);
			string obj;
			streamline >> obj;
			// Diferenciación
			if (obj == "Bow") {
				bowLoad = new Bow(this, streamline);
				objLoad.push_back(bowLoad);
			}
			else if (obj == "Arrow") {
				objLoad.push_back(new Arrow(this, streamline));
			}
			else if (obj == "Balloon") {
				objLoad.push_back(new Balloon(this, streamline));
			}
			else if (obj == "Butterfly") {
				objLoad.push_back(new Butterfly(this, streamline));
			}
			else throw "Objeto de tipo desconocido";
			++linenum;
		}
		loadLevel(level);
		// Si todo ha salido bien
		for (SceneObject* o : objects) delete o; // Liberación de memoria antigua
		// Se sobreescribe con la nueva
		objects = objLoad; 
		if (bowLoad) bow = bowLoad; else throw "Falta arco bro";
	}
	catch (const char* w){
		for (SceneObject* o : objLoad) delete o; // Liberación de la memoria
		throw FileFormatError(w, linenum, string(SAVE_ROOT) + "saved.txt");
	}
}
