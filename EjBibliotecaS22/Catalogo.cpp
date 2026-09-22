#include "Catalogo.h"
Catalogo::Catalogo(istream& file)
{
	using namespace Ejemplar;
	// Siguiendo la estructura que se da en el ejemplo
	// Se lee el codigo
	int codigo = 0;
	file >> codigo;
	// Se lee el caracter del tipo y se le asigna el tipo correspondiente
	char c = '.'; file >> c;
	Ejemplar::TIPO tipo;
	if (c == 'L') tipo = Ejemplar::TIPO::Libro;
	else if (c == 'A') tipo = Audiovisual;
	else if (c == 'J') tipo = Juego;
	// Si el caracter no es válido o no se reconoce de los tres posibles
	else tipo = DESCONOCIDO;
	// Nombre del ejemplar es todo hasta el final de linea
	getline(file, nombre);
}