#pragma once
#ifndef CATALOGO_H
#define CATALOGO_H
#include <fstream>
#include "Ejemplar.h"
class Catalogo
{
private:
	Ejemplar* elems;
	size_t numElems;
public:
	Catalogo(istream& file);
	Ejemplar* BuscaEjemplar(int Codigo) const;
	friend void operator<<(ostream& file, const Catalogo& catalog);
};
#endif // !CATALOGO_H



