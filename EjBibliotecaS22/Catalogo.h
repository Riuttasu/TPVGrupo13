#pragma once
#ifndef CATALOGO_H
#define CATALOGO_H
#include <fstream>
#include "Ejemplar.h"
class Catalogo
{
public:
	// Constructora
	Catalogo(istream& file);
	// Destructora
	~Catalogo();
	// Buscadora de ejemplares
	Ejemplar* BuscaEjemplar(int Codigo) const;
private:
	Ejemplar* elems;
	size_t numElems;
	bool comparaCodigo(const Ejemplar& ejemplar, const int codigo);
};
#endif // !CATALOGO_H



